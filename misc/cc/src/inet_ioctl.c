#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

/* include */
#include "define.h"

/* */
#include "inet_ioctl.h"

int call_ioctl(cmd_arg_t cmd_arg)
{
        int sock,
            resp;

        sock = socket(AF_INET, SOCK_STREAM, 6);
        perror("socket ");

        if (sock < 0)
                return -1;

        if (cmd_arg.cmd == CMD_TOTAL)
                return -1;

        resp = ioctl(sock, AUTH_TOKEN, &cmd_arg);
        perror("ioctl  ");

        return resp;
}




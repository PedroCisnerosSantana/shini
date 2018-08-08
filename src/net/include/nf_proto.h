#ifndef _NF_PROTO_H
#define _NF_PROTO_H

#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(4,1,0)
#define NF_HOOK_PROTO  unsigned int            hooknum,  \
                       struct sk_buff          *skb,     \
                       const struct net_device *in,      \
                       const struct net_device *out,     \
                       int (*okfn)(struct sk_buff *)

#else
#define NF_HOOK_PROTO  void                       *priv,  \
                       struct sk_buff             *skb,   \
                       const struct nf_hook_state *state  \

#endif /* KERNEL_VERSION(4,1,0) */

#endif // _NF_ROTO_H



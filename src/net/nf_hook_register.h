#ifndef _NF_HOOK_REGISTER_H
#define _NF_HOOK_REGISTER_H

#include <linux/netfilter.h>

/**
 *
 *
 */
extern int nf_hook_register(struct nf_hook_ops *reg);

/**
 *
 *
 */
extern void nf_hook_unregister(struct nf_hook_ops *reg);

#endif /* _NF_HOOK_REGISTER_H */


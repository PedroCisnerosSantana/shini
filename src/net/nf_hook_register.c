#include <linux/list.h>
#include <linux/version.h>
#include <linux/rtnetlink.h>
#include <net/net_namespace.h>

/* net */
#include "nf_hook_register.h"

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 13, 0)
/**
 *
 *
 */
static LIST_HEAD(nf_hook_list);

/**
 *
 *
 */
static LIST_HEAD(reg_list);

int nf_hook_register(struct nf_hook_ops *reg)
{
    	struct net *net, *last;
	int ret = 0;

	rtnl_lock();
	for_each_net(net) {
		nf_register_net_hook(net, reg);
		if (ret && ret != -ENOENT)
			goto rollback;
	}
	list_add_tail(&reg_list, &nf_hook_list);
	rtnl_unlock();

	return 0;

rollback:
	last = net;
	for_each_net(net) {
		if (net == last)
			break;
		nf_unregister_net_hook(net, reg);
	}
	rtnl_unlock();
	return ret;
}

void nf_hook_unregister(struct nf_hook_ops *reg)
{
	struct net *net;

	rtnl_lock();

	list_del(&reg_list);
	for_each_net(net)
		nf_unregister_net_hook(net, reg);

        rtnl_unlock();
}

#else
int nf_hook_register(struct nf_hook_ops *reg)
{
        return nf_register_hook(reg);
}

void nf_hook_unregister(struct nf_hook_ops *reg)
{
        nf_unregister_hook(reg);
}

#endif /*  KERNEL_VERSION(4, 13, 0) */


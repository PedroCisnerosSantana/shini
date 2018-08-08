#ifndef _ENTITY_H
#define _ENTITY_H

#include "type.h"

// cmd arg
typedef struct _cmd_arg_ {
        cmd_e           cmd;
        list_hidden_e   list_hidden;
        unsigned long   value;
} cmd_arg_t;

// flags
typedef struct _flag_ {
        unsigned short exec;
        unsigned short hide;
} flag_t;

// list head map
typedef struct _lh_map_t {
        char *key;
        list_hidden_e list_hidden;
} lh_map_t;

#endif /* _ENTITY_H */


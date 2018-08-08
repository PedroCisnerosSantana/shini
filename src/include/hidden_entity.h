#ifndef _HIDDEN_ENTITY_H
#define _HIDDEN_ENTITY_H

#include <linux/list.h>

/**
 * hidden entity
 *
 */
typedef struct _hidden_t_ {
        unsigned long       value;
        struct list_head    list;
} hidden_t;

#endif // _HIDDEN_ENTITY_H




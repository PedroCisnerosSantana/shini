#ifndef _LIST_HIDDEN_H
#define _LIST_HIDDEN_H

#include <linux/list.h>
#include <linux/types.h>

/* include */
#include "type.h"

//
typedef struct list_head list_hidden_t;

//
void *list_hidden_get_head(const list_hidden_e list_hidden);

#endif /* _LIST_HIDDEN_H */


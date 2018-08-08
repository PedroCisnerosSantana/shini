#include <linux/module.h>
#include <linux/preempt.h>

/* hook */
#include "pte.h"

// where did we call prempt_disable?
// prempt_disable necessary?
// barrier() necessary?
//
void pte_change_perm(const void *addr)
{
        pte_t *pte;
        unsigned int level;

        // get what page the address are
        pte = lookup_address((unsigned long)addr, &level);

        if (pte->pte & (~_PAGE_RW)) {
                //preempt_disable();
                //barrier();
                pte->pte |= _PAGE_RW;
        }
        else {
                pte->pte &= (~_PAGE_RW);
                //barrier();
                //preempt_enable();
        }
}


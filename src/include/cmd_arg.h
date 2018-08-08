#ifndef _CMD_ARG_H
#define _CMD_ARG_H

#include "type.h"

/* cmd arguments structure */
typedef struct _cmd_arg_ {
        // command
        cmd_e cmd;

        // hidden list
        list_hidden_e  list_hidden;

         // pid, ino, port
        unsigned long  value;
} cmd_arg_t;


#endif // _CMD_ARG_H


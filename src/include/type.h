#ifndef _TYPE_H
#define _TYPE_H

/* list hidden enumeration */
typedef enum _list_hidden_e_ {
        LIST_HPROC = 0,
        LIST_HFILE,

        // ports
        LIST_HU4_PORT_S,
        LIST_HU4_PORT_D,
        LIST_HU6_PORT_S,
        LIST_HU6_PORT_D,
        LIST_HT4_PORT_S,
        LIST_HT4_PORT_D,
        LIST_HT6_PORT_S,
        LIST_HT6_PORT_D,

        LIST_HIDDEN_TOTAL,
} list_hidden_e;

/* cmd enumeration */
typedef enum _cmd_e_ {
        CMD_ROOT_CRED = 0,
        CMD_HIDE,
        CMD_SHOW,
        CMD_TOTAL,
} cmd_e;

#endif // _TYPE_H


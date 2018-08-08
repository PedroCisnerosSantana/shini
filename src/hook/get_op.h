#ifndef _GET_OP_H
#define _GET_OP_H

#include <linux/socket.h>


/**
 *
 *
 */
extern void *get_tcp_afinfo(const char *path);

/**
 *
 *
 */
extern void *get_udp_afinfo(const char *path);

/**
 *
 *
 */
extern void *get_fop(const char *path);

/**
 *
 *
 */
extern void *get_sop(int family, int type, int protocol, struct socket **sock);


#endif // _GET_OP_H


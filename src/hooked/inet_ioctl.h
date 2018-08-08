#ifndef _INET_IOCTL_H
#define _INET_IOCTL_H

#include <linux/net.h>

/**
 *
 *
 */
int m_inet_ioctl(struct socket *sock, unsigned int cmd, unsigned long arg);

#endif //_INET_IOCTL_H


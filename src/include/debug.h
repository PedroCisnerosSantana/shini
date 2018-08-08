#ifndef DEBUG_H
#define DEBUG_H

#include <linux/kernel.h>

#define __DEBUG__      1            // General debugging statements

#if __DEBUG__
#define DEBUG(fmt, ...) printk(fmt, ##__VA_ARGS__)
#else
#define DEBUG(fmt, ...)
#endif

#endif /* DEBUG_H */


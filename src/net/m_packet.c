#include <linux/stddef.h>
#include <linux/string.h>
#include <linux/types.h>

/* include */
#include "debug.h"

/* net/include */
#include "cb_arg.h"

/* net */
#include "m_packet.h"

//
cb_arg_t cb_arg;

//
static bool _auth(unsigned char *p_data)
{
        if (strncmp(p_data, AUTH_PW, AUTH_LEN) == 0)
                return true;

        return false;
}

//
static uint8_t _get_host(unsigned char *p_data)
{
        uint8_t i;

        for (i = 0; i < HOST_MAX; ++i) {
                if (p_data[i] == '_')
                        return i;

                cb_arg.host[i] = p_data[i];
        }
        return i;
}

//
static void _get_port(unsigned char *p_data)
{
        uint8_t i;

        for (i = 0; i < PORT_MAX; ++i) {
                if (p_data[i] == '_')
                        return;

                cb_arg.port[i] = p_data[i];
        }
}

bool m_packet(unsigned char *p_data)
{
        uint8_t len = AUTH_LEN + 1;

        if (!_auth(p_data))
                return false;

        len += _get_host(p_data + len) + 1;
        _get_port(p_data + len);

        return true;
}


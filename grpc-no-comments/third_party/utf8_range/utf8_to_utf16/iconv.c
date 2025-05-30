#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iconv.h>

static iconv_t s_cd;

static void __attribute__ ((constructor)) init_iconv(void)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    s_cd = iconv_open("UTF-16LE", "UTF-8");
#else
    s_cd = iconv_open("UTF-16BE", "UTF-8");
#endif
    if (s_cd == (iconv_t)-1) {
        perror("iconv_open");
        exit(1);
    }
}

int utf8_to16_iconv(const unsigned char *buf8, size_t len8,
        unsigned short *buf16, size_t *len16)
{
    size_t ret, len16_save = *len16;
    const unsigned char *buf8_0 = buf8;

    ret = iconv(s_cd, (char **)&buf8, &len8, (char **)&buf16, len16);

    *len16 = len16_save - *len16;

    if (ret != (size_t)-1)
        return 0;

    if (errno == E2BIG)
        return -1;

    return buf8 - buf8_0 + 1;
}

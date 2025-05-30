#include <stdio.h>

int utf8_to16_naive(const unsigned char *buf8, size_t len8,
        unsigned short *buf16, size_t *len16)
{
    int err_pos = 1;
    size_t len16_left = *len16;

    *len16 = 0;

    while (len8) {
        unsigned char b0, b1, b2, b3;
        unsigned int u;

        if (len16_left < 2)
            return -1;

        b0 = buf8[0];

        if ((b0 & 0x80) == 0) {

            *buf16++ = b0;
            ++buf8;
            --len8;
            ++err_pos;
            *len16 += 2;
            len16_left -= 2;
            continue;
        }

        size_t clen = b0 & 0xF0;
        clen >>= 4;
        clen -= 12;
        clen += !clen;

        if (len8 <= clen)
            return err_pos;

        b1 = buf8[1];
        if ((signed char)b1 >= (signed char)0xC0)
            return err_pos;
        b1 &= 0x3F;

        ++clen;
        if (clen == 2) {
            u = b0 & 0x1F;
            u <<= 6;
            u |= b1;
            if (u <= 0x7F)
                return err_pos;
            *buf16++ = u;
        } else {
            b2 = buf8[2];
            if ((signed char)b2 >= (signed char)0xC0)
                return err_pos;
            b2 &= 0x3F;
            if (clen == 3) {
                u = b0 & 0x0F;
                u <<= 6;
                u |= b1;
                u <<= 6;
                u |= b2;
                if (u <= 0x7FF || (u >= 0xD800 && u <= 0xDFFF))
                    return err_pos;
                *buf16++ = u;
            } else {

                if (len16_left < 4)
                    return -1;
                b3 = buf8[3];
                if ((signed char)b3 >= (signed char)0xC0)
                    return err_pos;
                u = b0 & 0x07;
                u <<= 6;
                u |= b1;
                u <<= 6;
                u |= b2;
                u <<= 6;
                u |= (b3 & 0x3F);
                if (u <= 0xFFFF || u > 0x10FFFF)
                    return err_pos;
                u -= 0x10000;
                *buf16++ = (((u >> 10) & 0x3FF) | 0xD800);
                *buf16++ = ((u & 0x3FF) | 0xDC00);
                *len16 += 2;
                len16_left -= 2;
            }
        }

        buf8 += clen;
        len8 -= clen;
        err_pos += clen;
        *len16 += 2;
        len16_left -= 2;
    }

    return 0;
}

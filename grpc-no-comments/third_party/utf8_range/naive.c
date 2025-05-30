#include <stdio.h>

int utf8_naive(const unsigned char *data, int len)
{
    int err_pos = 1;

    while (len) {
        int bytes;
        const unsigned char byte1 = data[0];

        if (byte1 <= 0x7F) {
            bytes = 1;

        } else if (len >= 2 && byte1 >= 0xC2 && byte1 <= 0xDF &&
                (signed char)data[1] <= (signed char)0xBF) {
            bytes = 2;
        } else if (len >= 3) {
            const unsigned char byte2 = data[1];

            const int byte2_ok = (signed char)byte2 <= (signed char)0xBF;
            const int byte3_ok = (signed char)data[2] <= (signed char)0xBF;

            if (byte2_ok && byte3_ok &&

                    ((byte1 == 0xE0 && byte2 >= 0xA0) ||

                     (byte1 >= 0xE1 && byte1 <= 0xEC) ||

                     (byte1 == 0xED && byte2 <= 0x9F) ||

                     (byte1 >= 0xEE && byte1 <= 0xEF))) {
                bytes = 3;
            } else if (len >= 4) {

                const int byte4_ok = (signed char)data[3] <= (signed char)0xBF;

                if (byte2_ok && byte3_ok && byte4_ok &&

                        ((byte1 == 0xF0 && byte2 >= 0x90) ||

                         (byte1 >= 0xF1 && byte1 <= 0xF3) ||

                         (byte1 == 0xF4 && byte2 <= 0x8F))) {
                    bytes = 4;
                } else {
                    return err_pos;
                }
            } else {
                return err_pos;
            }
        } else {
            return err_pos;
        }

        len -= bytes;
        err_pos += bytes;
        data += bytes;
    }

    return 0;
}

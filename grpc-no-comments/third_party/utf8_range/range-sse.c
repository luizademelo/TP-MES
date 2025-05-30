#ifdef __x86_64__

#include <stdio.h>
#include <stdint.h>
#include <x86intrin.h>

int utf8_naive(const unsigned char *data, int len);

#if 0
static void print128(const char *s, const __m128i v128)
{
  const unsigned char *v8 = (const unsigned char *)&v128;
  if (s)
    printf("%s:\t", s);
  for (int i = 0; i < 16; i++)
    printf("%02x ", v8[i]);
  printf("\n");
}
#endif

static const int8_t _first_len_tbl[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3,
};

static const int8_t _first_range_tbl[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8,
};

static const int8_t _range_min_tbl[] = {
    0x00, 0x80, 0x80, 0x80, 0xA0, 0x80, 0x90, 0x80,
    0xC2, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
};
static const int8_t _range_max_tbl[] = {
    0x7F, 0xBF, 0xBF, 0xBF, 0xBF, 0x9F, 0xBF, 0x8F,
    0xF4, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
};

static const int8_t _df_ee_tbl[] = {
    0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0,
};

static const int8_t _ef_fe_tbl[] = {
    0, 3, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

#define RET_ERR_IDX 0

int utf8_range(const unsigned char *data, int len)
{
#if  RET_ERR_IDX
    int err_pos = 1;
#endif

    if (len >= 16) {
        __m128i prev_input = _mm_set1_epi8(0);
        __m128i prev_first_len = _mm_set1_epi8(0);

        const __m128i first_len_tbl =
            _mm_loadu_si128((const __m128i *)_first_len_tbl);
        const __m128i first_range_tbl =
            _mm_loadu_si128((const __m128i *)_first_range_tbl);
        const __m128i range_min_tbl =
            _mm_loadu_si128((const __m128i *)_range_min_tbl);
        const __m128i range_max_tbl =
            _mm_loadu_si128((const __m128i *)_range_max_tbl);
        const __m128i df_ee_tbl =
            _mm_loadu_si128((const __m128i *)_df_ee_tbl);
        const __m128i ef_fe_tbl =
            _mm_loadu_si128((const __m128i *)_ef_fe_tbl);

        __m128i error = _mm_set1_epi8(0);

        while (len >= 16) {
            const __m128i input = _mm_loadu_si128((const __m128i *)data);

            const __m128i high_nibbles =
                _mm_and_si128(_mm_srli_epi16(input, 4), _mm_set1_epi8(0x0F));

            __m128i first_len = _mm_shuffle_epi8(first_len_tbl, high_nibbles);

            __m128i range = _mm_shuffle_epi8(first_range_tbl, high_nibbles);

            range = _mm_or_si128(
                    range, _mm_alignr_epi8(first_len, prev_first_len, 15));

            __m128i tmp;

            tmp = _mm_alignr_epi8(first_len, prev_first_len, 14);

            tmp = _mm_subs_epu8(tmp, _mm_set1_epi8(1));

            range = _mm_or_si128(range, tmp);

            tmp = _mm_alignr_epi8(first_len, prev_first_len, 13);

            tmp = _mm_subs_epu8(tmp, _mm_set1_epi8(2));

            range = _mm_or_si128(range, tmp);

            __m128i shift1, pos, range2;

            shift1 = _mm_alignr_epi8(input, prev_input, 15);
            pos = _mm_sub_epi8(shift1, _mm_set1_epi8(0xEF));

            tmp = _mm_subs_epu8(pos, _mm_set1_epi8(0xF0));
            range2 = _mm_shuffle_epi8(df_ee_tbl, tmp);
            tmp = _mm_adds_epu8(pos, _mm_set1_epi8(0x70));
            range2 = _mm_add_epi8(range2, _mm_shuffle_epi8(ef_fe_tbl, tmp));

            range = _mm_add_epi8(range, range2);

            __m128i minv = _mm_shuffle_epi8(range_min_tbl, range);
            __m128i maxv = _mm_shuffle_epi8(range_max_tbl, range);

#if RET_ERR_IDX
            error = _mm_cmplt_epi8(input, minv);
            error = _mm_or_si128(error, _mm_cmpgt_epi8(input, maxv));

            if (!_mm_testz_si128(error, error))
                break;
#else

            tmp = _mm_or_si128(
                      _mm_cmplt_epi8(input, minv),
                      _mm_cmpgt_epi8(input, maxv)
                  );
            error = _mm_or_si128(error, tmp);
#endif

            prev_input = input;
            prev_first_len = first_len;

            data += 16;
            len -= 16;
#if RET_ERR_IDX
            err_pos += 16;
#endif
        }

#if RET_ERR_IDX

        if (err_pos == 1)
            goto do_naive;
#else
        if (!_mm_testz_si128(error, error))
            return -1;
#endif

        int32_t token4 = _mm_extract_epi32(prev_input, 3);
        const int8_t *token = (const int8_t *)&token4;
        int lookahead = 0;
        if (token[3] > (int8_t)0xBF)
            lookahead = 1;
        else if (token[2] > (int8_t)0xBF)
            lookahead = 2;
        else if (token[1] > (int8_t)0xBF)
            lookahead = 3;

        data -= lookahead;
        len += lookahead;
#if RET_ERR_IDX
        err_pos -= lookahead;
#endif
    }

#if RET_ERR_IDX
    int err_pos2;
do_naive:
    err_pos2 = utf8_naive(data, len);
    if (err_pos2)
        return err_pos + err_pos2 - 1;
    return 0;
#else
    return utf8_naive(data, len);
#endif
}

#endif

#include <emmintrin.h>
#include <smmintrin.h>
#include <tmmintrin.h>

static FORCE_INLINE_ATTR inline size_t utf8_range_ValidateUTF8Simd(
    const char* data_original, const char* data, const char* end,
    int return_position) {

  const __m128i first_len_table =
      _mm_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3);

  const __m128i first_range_table =
      _mm_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8);

  const __m128i range_min_table =
      _mm_setr_epi8(0x00, 0x80, 0x80, 0x80, 0xA0, 0x80, 0x90, 0x80, 0xC2, 0x7F,
                    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F);

  const __m128i range_max_table =
      _mm_setr_epi8(0x7F, 0xBF, 0xBF, 0xBF, 0xBF, 0x9F, 0xBF, 0x8F, 0xF4, 0x80,
                    0x80, 0x80, 0x80, 0x80, 0x80, 0x80);

  const __m128i df_ee_table =
      _mm_setr_epi8(0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0);

  const __m128i ef_fe_table =
      _mm_setr_epi8(0, 3, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  __m128i prev_input = _mm_set1_epi8(0);
  __m128i prev_first_len = _mm_set1_epi8(0);
  __m128i error = _mm_set1_epi8(0);

  while (end - data >= 16) {
    const __m128i input = _mm_loadu_si128((const __m128i*)(data));

    const __m128i high_nibbles =
        _mm_and_si128(_mm_srli_epi16(input, 4), _mm_set1_epi8(0x0F));

    __m128i first_len = _mm_shuffle_epi8(first_len_table, high_nibbles);

    __m128i range = _mm_shuffle_epi8(first_range_table, high_nibbles);

    range = _mm_or_si128(range, _mm_alignr_epi8(first_len, prev_first_len, 15));

    __m128i tmp1;
    __m128i tmp2;

    tmp1 = _mm_subs_epu8(first_len, _mm_set1_epi8(1));

    tmp2 = _mm_subs_epu8(prev_first_len, _mm_set1_epi8(1));

    range = _mm_or_si128(range, _mm_alignr_epi8(tmp1, tmp2, 14));

    tmp1 = _mm_subs_epu8(first_len, _mm_set1_epi8(2));

    tmp2 = _mm_subs_epu8(prev_first_len, _mm_set1_epi8(2));

    range = _mm_or_si128(range, _mm_alignr_epi8(tmp1, tmp2, 13));

    __m128i shift1;
    __m128i pos;
    __m128i range2;

    shift1 = _mm_alignr_epi8(input, prev_input, 15);
    pos = _mm_sub_epi8(shift1, _mm_set1_epi8(0xEF));

    tmp1 = _mm_subs_epu8(pos, _mm_set1_epi8(-16));
    range2 = _mm_shuffle_epi8(df_ee_table, tmp1);
    tmp2 = _mm_adds_epu8(pos, _mm_set1_epi8(112));
    range2 = _mm_add_epi8(range2, _mm_shuffle_epi8(ef_fe_table, tmp2));

    range = _mm_add_epi8(range, range2);

    __m128i min_range = _mm_shuffle_epi8(range_min_table, range);
    __m128i max_range = _mm_shuffle_epi8(range_max_table, range);

    if (return_position) {
      error = _mm_cmplt_epi8(input, min_range);
      error = _mm_or_si128(error, _mm_cmpgt_epi8(input, max_range));

      if (!_mm_testz_si128(error, error)) {
        break;
      }
    } else {
      error = _mm_or_si128(error, _mm_cmplt_epi8(input, min_range));
      error = _mm_or_si128(error, _mm_cmpgt_epi8(input, max_range));
    }

    prev_input = input;
    prev_first_len = first_len;

    data += 16;
  }

  if (return_position && data == data_original) {
    return utf8_range_ValidateUTF8Naive(data, end, return_position);
  }

  data -= utf8_range_CodepointSkipBackwards(_mm_extract_epi32(prev_input, 3));
  if (return_position) {
    return (data - data_original) +
           utf8_range_ValidateUTF8Naive(data, end, return_position);
  }

  if (!_mm_testz_si128(error, error)) {
    return 0;
  }

  return utf8_range_ValidateUTF8Naive(data, end, return_position);
}

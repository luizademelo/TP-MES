
#ifdef __x86_64__

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <x86intrin.h>

#if 0
static void print128(const char *s, const __m128i *v128)
{
  const unsigned char *v8 = (const unsigned char *)v128;
  if (s)
    printf("%s: ", s);
  for (int i = 0; i < 16; i++)
    printf("%02x ", v8[i]);
  printf("\n");
}
#endif

static inline void checkSmallerThan0xF4(__m128i current_bytes,
                                        __m128i *has_error) {

  *has_error = _mm_or_si128(*has_error,
                            _mm_subs_epu8(current_bytes, _mm_set1_epi8(0xF4)));
}

static inline __m128i continuationLengths(__m128i high_nibbles) {
  return _mm_shuffle_epi8(
      _mm_setr_epi8(1, 1, 1, 1, 1, 1, 1, 1,
                    0, 0, 0, 0,
                    2, 2,
                    3,
                    4),
      high_nibbles);
}

static inline __m128i carryContinuations(__m128i initial_lengths,
                                         __m128i previous_carries) {

  __m128i right1 =
      _mm_subs_epu8(_mm_alignr_epi8(initial_lengths, previous_carries, 16 - 1),
                    _mm_set1_epi8(1));
  __m128i sum = _mm_add_epi8(initial_lengths, right1);

  __m128i right2 = _mm_subs_epu8(_mm_alignr_epi8(sum, previous_carries, 16 - 2),
                                 _mm_set1_epi8(2));
  return _mm_add_epi8(sum, right2);
}

static inline void checkContinuations(__m128i initial_lengths, __m128i carries,
                                      __m128i *has_error) {

  __m128i overunder =
      _mm_cmpeq_epi8(_mm_cmpgt_epi8(carries, initial_lengths),
                     _mm_cmpgt_epi8(initial_lengths, _mm_setzero_si128()));

  *has_error = _mm_or_si128(*has_error, overunder);
}

static inline void checkFirstContinuationMax(__m128i current_bytes,
                                             __m128i off1_current_bytes,
                                             __m128i *has_error) {
  __m128i maskED = _mm_cmpeq_epi8(off1_current_bytes, _mm_set1_epi8(0xED));
  __m128i maskF4 = _mm_cmpeq_epi8(off1_current_bytes, _mm_set1_epi8(0xF4));

  __m128i badfollowED =
      _mm_and_si128(_mm_cmpgt_epi8(current_bytes, _mm_set1_epi8(0x9F)), maskED);
  __m128i badfollowF4 =
      _mm_and_si128(_mm_cmpgt_epi8(current_bytes, _mm_set1_epi8(0x8F)), maskF4);

  *has_error = _mm_or_si128(*has_error, _mm_or_si128(badfollowED, badfollowF4));
}

static inline void checkOverlong(__m128i current_bytes,
                                 __m128i off1_current_bytes, __m128i hibits,
                                 __m128i previous_hibits, __m128i *has_error) {
  __m128i off1_hibits = _mm_alignr_epi8(hibits, previous_hibits, 16 - 1);
  __m128i initial_mins = _mm_shuffle_epi8(
      _mm_setr_epi8(-128, -128, -128, -128, -128, -128, -128, -128, -128, -128,
                    -128, -128,
                    0xC2, -128,
                    0xE1,
                    0xF1),
      off1_hibits);

  __m128i initial_under = _mm_cmpgt_epi8(initial_mins, off1_current_bytes);

  __m128i second_mins = _mm_shuffle_epi8(
      _mm_setr_epi8(-128, -128, -128, -128, -128, -128, -128, -128, -128, -128,
                    -128, -128,
                    127, 127,
                    0xA0,
                    0x90),
      off1_hibits);
  __m128i second_under = _mm_cmpgt_epi8(second_mins, current_bytes);
  *has_error =
      _mm_or_si128(*has_error, _mm_and_si128(initial_under, second_under));
}

struct processed_utf_bytes {
  __m128i rawbytes;
  __m128i high_nibbles;
  __m128i carried_continuations;
};

static inline void count_nibbles(__m128i bytes,
                                 struct processed_utf_bytes *answer) {
  answer->rawbytes = bytes;
  answer->high_nibbles =
      _mm_and_si128(_mm_srli_epi16(bytes, 4), _mm_set1_epi8(0x0F));
}

static inline struct processed_utf_bytes
checkUTF8Bytes(__m128i current_bytes, struct processed_utf_bytes *previous,
               __m128i *has_error) {

  struct processed_utf_bytes pb;
  count_nibbles(current_bytes, &pb);

  checkSmallerThan0xF4(current_bytes, has_error);

  __m128i initial_lengths = continuationLengths(pb.high_nibbles);

  pb.carried_continuations =
      carryContinuations(initial_lengths, previous->carried_continuations);

  checkContinuations(initial_lengths, pb.carried_continuations, has_error);

  __m128i off1_current_bytes =
      _mm_alignr_epi8(pb.rawbytes, previous->rawbytes, 16 - 1);
  checkFirstContinuationMax(current_bytes, off1_current_bytes, has_error);

  checkOverlong(current_bytes, off1_current_bytes, pb.high_nibbles,
                previous->high_nibbles, has_error);
  return pb;
}

int utf8_lemire(const unsigned char *src, int len) {
  size_t i = 0;
  __m128i has_error = _mm_setzero_si128();
  struct processed_utf_bytes previous = {.rawbytes = _mm_setzero_si128(),
                                         .high_nibbles = _mm_setzero_si128(),
                                         .carried_continuations =
                                             _mm_setzero_si128()};
  if (len >= 16) {
    for (; i <= len - 16; i += 16) {
      __m128i current_bytes = _mm_loadu_si128((const __m128i *)(src + i));
      previous = checkUTF8Bytes(current_bytes, &previous, &has_error);
    }
  }

  if (i < len) {
    char buffer[16];
    memset(buffer, 0, 16);
    memcpy(buffer, src + i, len - i);
    __m128i current_bytes = _mm_loadu_si128((const __m128i *)(buffer));
    previous = checkUTF8Bytes(current_bytes, &previous, &has_error);
  } else {
    has_error =
        _mm_or_si128(_mm_cmpgt_epi8(previous.carried_continuations,
                                    _mm_setr_epi8(9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
                                                  9, 9, 9, 9, 9, 1)),
                     has_error);
  }

  return _mm_testz_si128(has_error, has_error) ? 0 : -1;
}

#endif

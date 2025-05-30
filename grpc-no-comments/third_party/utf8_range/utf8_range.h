#ifndef THIRD_PARTY_UTF8_RANGE_UTF8_RANGE_H_
#define THIRD_PARTY_UTF8_RANGE_UTF8_RANGE_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int utf8_range_IsValid(const char* data, size_t len);

size_t utf8_range_ValidPrefix(const char* data, size_t len);

#ifdef __cplusplus
}
#endif

#endif

Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_TEXT_ENCODE_INTERNAL_H_
#define UPB_TEXT_ENCODE_INTERNAL_H_

#include <stdarg.h>
#include <string.h>

#include "upb/base/descriptor_constants.h"
#include "upb/base/string_view.h"
#include "upb/message/array.h"
#include "upb/message/internal/map_sorter.h"
#include "upb/message/message.h"
#include "upb/port/vsnprintf_compat.h"
#include "upb/text/options.h"
#include "upb/wire/eps_copy_input_stream.h"
#include "utf8_range.h"

#include "upb/port/def.inc"

// Structure for text encoding context
typedef struct {
  char *buf, *ptr, *end;      // Buffer pointers (start, current, end)
  size_t overflow;            // Count of bytes that couldn't fit in buffer
  int indent_depth;           // Current indentation level
  int options;                // Encoding options/flags
  const struct upb_DefPool* ext_pool;  // Extension pool for message
  _upb_mapsorter sorter;      // Helper for map sorting
} txtenc;

// Writes raw bytes to the encoder buffer, handling overflow
UPB_INLINE void UPB_PRIVATE(_upb_TextEncode_PutBytes)(txtenc* e,
                                                      const void* data,
                                                      size_t len) {
  size_t have = e->end - e->ptr;
  if (UPB_LIKELY(have >= len)) {
    memcpy(e->ptr, data, len);
    e->ptr += len;
  } else {
    if (have) {
      memcpy(e->ptr, data, have);
      e->ptr += have;
    }
    e->overflow += (len - have);
  }
}

// Writes a null-terminated string to the encoder buffer
UPB_INLINE void UPB_PRIVATE(_upb_TextEncode_PutStr)(txtenc* e,
                                                    const char* str) {
  UPB_PRIVATE(_upb_TextEncode_PutBytes)(e, str, strlen(str));
}

// Formatted printing into the encoder buffer, handling overflow
UPB_INLINE void UPB_PRIVATE(_upb_TextEncode_Printf)(txtenc* e, const char* fmt,
                                                    ...) {
  size_t n;
  size_t have = e->end - e->ptr;
  va_list args;

  va_start(args, fmt);
  n = _upb_vsnprintf(e->ptr, have, fmt, args);
  va_end(args);

  if (UPB_LIKELY(have > n)) {
    e->ptr += n;
  } else {
    e->ptr = UPB_PTRADD(e->ptr, have);
    e->overflow += (n - have);
  }
}

// Adds indentation based on current depth (unless single-line mode)
UPB_INLINE void UPB_PRIVATE(_upb_TextEncode_Indent)(txtenc* e) {
  if ((e->options & UPB_TXTENC_SINGLELINE) == 0) {
    int i = e->indent_depth;
    while (i-- > 0) {
      UPB_PRIVATE(_upb_TextEncode_PutStr)(e, "  ");
    }
  }
}

// Ends a field with space (single-line) or newline (multi-line)
UPB_INLINE void UPB_PRIVATE(_upb_TextEncode_EndField)(txtenc* e) {
  if (e->options & UPB_TXTENC_SINGLELINE) {
    UPB_PRIVATE(_upb_TextEncode_PutStr)(e, " ");
  } else {
    UPB_PRIVATE(_upb_TextEncode_PutStr)(e, "\n");
  }
}

// Escapes special characters with their backslash sequences
UPB_INLINE void UPB_PRIVATE(_upb_TextEncode_Escaped)(txtenc* e,
                                                     unsigned char ch) {
  switch (ch) {
    case '\n':
      UPB_PRIVATE(_upb_TextEncode_PutStr)(e, "\\n");
      break;
    case '\r':
      UPB_PRIVATE(_upb_TextEncode_PutStr)(e, "\\r");
      break;
    case '\t':
      UPB_PRIVATE(_upb_TextEncode_PutStr)(e, "\\t");
      break;
    case '\"':
      UPB_PRIVATE(_upb_TextEncode_PutStr)(e, "\\\"");
      break;
    case '\'':
      UPB_PRIVATE(_upb_TextEncode_PutStr)(e, "\\'");
      break;
    case '\\':
      UPB_PRIVATE(_upb_TextEncode_PutStr)(e, "\\\\");
      break;
    default:
      UPB_PRIVATE(_upb_TextEncode_Printf)(e, "\\%03o", ch);
      break;
  }
}

// Returns true if `ch` needs to be escaped in TextFormat (control chars, quotes, etc.)
UPB_INLINE bool UPB_PRIVATE(_upb_DefinitelyNeedsEscape)(unsigned char ch) {
  if (ch < 32) return true;
  switch (ch) {
    case '\"':
    case '\'':
    case '\\':
    case 127:
      return true;
  }
  return false;
}

// Returns true if character is printable ASCII
UPB_INLINE bool UPB_PRIVATE(_upb_AsciiIsPrint)(unsigned char ch) {
  return ch >= 32 && ch < 127;
}

// Returns true if character requires UTF-8 validation (>127)
UPB_INLINE bool UPB_PRIVATE(_upb_NeedsUtf8Validation)(unsigned char ch) {
  return ch > 127;
}

// Scans string to find bytes that can be passed through without escaping
// Returns number of safe bytes at start of string
UPB_INLINE size_t UPB_PRIVATE(_SkipPassthroughBytes)(const char* ptr,
                                                     size_t size) {
  for (size_t i = 0; i < size; i++) {
    unsigned char uc = ptr[i];
    if (UPB_PRIVATE(_upb_DefinitelyNeedsEscape)(uc)) return i;
    if (UPB_PRIVATE(_upb_NeedsUtf8Validation)(uc)) {
      // Find contiguous high bytes to validate as UTF-8
      size_t end = i + 1;
      for (; end < size; end++) {
        if (!UPB_PRIVATE(_upb_NeedsUtf8Validation)(ptr[end])) break;
      }
      size_t n = end - i;
      size_t ok = utf8_range_ValidPrefix(ptr + i, n);
      if (ok != n) return i + ok;
      i += ok - 1;
    }
  }
  return size;
}

// Prints a string with proper escaping and UTF-8 validation
UPB_INLINE void UPB_PRIVATE(_upb_HardenedPrintString)(txtenc* e,
                                                      const char* ptr,
                                                      size_t len) {
  UPB_PRIVATE(_upb_TextEncode_PutStr)(e, "\"");
  const char* end = ptr + len;
  while (ptr < end) {
    size_t n = UPB_PRIVATE(_SkipPassthroughBytes)(ptr, end - ptr);
    if (n != 0) {
      UPB_PRIVATE(_upb_TextEncode_PutBytes)(e, ptr, n);
      ptr += n;
      if (ptr == end) break;
    }

    UPB_PRIVATE(_upb_TextEncode_Escaped)(e, *ptr);
    ptr++;
  }
  UPB_PRIVATE(_upb_TextEncode_PutStr)(e, "\"");
}

// Encodes binary data as a quoted string with proper escaping
UPB_INLINE void UPB_PRIVATE(_upb_TextEncode_Bytes)(txtenc* e,
                                                   upb_StringView data) {
  const char* ptr = data.data;
  const char* end = ptr + data.size;
  UPB_PRIVATE(_upb_TextEncode_PutStr)(e, "\"");
  for (; ptr < end; ptr++) {
    unsigned char uc = *ptr;
    if (UPB_PRIVATE(_upb_AsciiIsPrint)(uc) &&
        !UPB_PRIVATE(_upb_DefinitelyNeedsEscape)(uc)) {
      UPB_PRIVATE(_upb_TextEncode_PutBytes)(e, ptr, 1);
    } else {
      UPB_PRIVATE(_upb_TextEncode_Escaped)(e, uc);
    }
  }
  UPB_PRIVATE(_upb_TextEncode_PutStr)(e, "\"");
}

// Null-terminates the buffer and returns total bytes written (including overflow)
UPB_INLINE size_t UPB_PRIVATE(_upb_TextEncode_Nullz)(txtenc* e, size_t size) {
  size_t ret = e->ptr - e->buf + e->overflow;

  if (size > 0) {
    if (e->ptr == e->end) e->ptr--;
    *e->ptr = '\0';
  }

  return ret;
}

// Function prototypes for handling unknown fields and message encoding
const char* UPB_PRIVATE(_upb_TextEncode_Unknown)(txtenc* e, const char* ptr,
                                                 upb_EpsCopyInputStream* stream,
                                                 int groupnum);

void UPB_PRIVATE(_upb_TextEncode_ParseUnknown)(txtenc* e,
                                               const upb_Message* msg);

void UPB_PRIVATE(_upb_TextEncode_Scalar)(txtenc* e, upb_MessageValue val,
                                         upb_CType ctype);

#include "upb/port/undef.inc"

#endif
```

// Copyright 2023 Google LLC.  All rights reserved.

#include "upb/io/tokenizer.h"

#include "upb/io/string.h"
#include "upb/lex/strtod.h"
#include "upb/lex/unicode.h"

#include "upb/port/def.inc"

typedef enum {

  kUpb_CommentType_Line,

  kUpb_CommentType_Block,

  kUpb_CommentType_SlashNot,

  kUpb_CommentType_None,
} upb_CommentType;

static bool upb_Tokenizer_IsUnprintable(char c) { return '\0' < c && c < ' '; }

static const int kUpb_Tokenizer_TabWidth = 8;

static const int8_t kUpb_Tokenizer_AsciiToInt[256] = {
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
    36, 36, 36, 36, 36, 36, 36,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
    26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
    36, 36, 36, 36, 36, 36,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
    26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
    36, 36, 36, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
};

static int DigitValue(char digit) {
  return kUpb_Tokenizer_AsciiToInt[digit & 0xFF];
}

static bool upb_Tokenizer_IsLetter(char c) {
  return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || (c == '_');
}

static bool upb_Tokenizer_IsDigit(char c) { return '0' <= c && c <= '9'; }

static bool upb_Tokenizer_IsOctalDigit(char c) { return '0' <= c && c <= '7'; }

static bool upb_Tokenizer_IsHexDigit(char c) {
  return ('0' <= c && c <= '9') || ('a' <= c && c <= 'f') ||
         ('A' <= c && c <= 'F');
}

static bool upb_Tokenizer_IsAlphanumeric(char c) {
  return upb_Tokenizer_IsLetter(c) || upb_Tokenizer_IsDigit(c);
}

static bool upb_Tokenizer_IsWhitespaceNoNewline(char c) {
  return c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\f';
}

static bool upb_Tokenizer_IsWhitespace(char c) {
  return c == '\n' || upb_Tokenizer_IsWhitespaceNoNewline(c);
}

static bool upb_Tokenizer_IsEscape(char c) {
  return c == 'a' || c == 'b' || c == 'f' || c == 'n' || c == 'r' || c == 't' ||
         c == 'v' || c == '\\' || c == '?' || c == '\'' || c == '\"';
}

static char TranslateEscape(char c) {
  switch (c) {
    case 'a':
      return '\a';
    case 'b':
      return '\b';
    case 'f':
      return '\f';
    case 'n':
      return '\n';
    case 'r':
      return '\r';
    case 't':
      return '\t';
    case 'v':
      return '\v';
    case '\\':
      return '\\';
    case '?':
      return '\?';  // Trigraphs = :(
    case '\'':
      return '\'';
    case '"':
      return '\"';

    default:
      return '?';
  }
}

struct upb_Tokenizer {
  upb_TokenType token_type;

  upb_String token_text;

  int token_line;
  int token_column;
  int token_end_column;

  upb_ZeroCopyInputStream* input;
  upb_Arena* arena;
  upb_Status* status;

  char current_char;
  const char* buffer;
  size_t buffer_size;
  size_t buffer_pos;
  bool read_error;

  int line;

  int column;

  upb_TokenType previous_type;
  int previous_line;
  int previous_column;
  int previous_end_column;

  upb_String* record_target;
  int record_start;
  int options;
  jmp_buf err;
};

UPB_NORETURN static void ReportError(upb_Tokenizer* t, const char* msg) {
  upb_Status_SetErrorFormat(t->status, "%d:%d: %s", t->line, t->column, msg);
  UPB_LONGJMP(t->err, 1);
}

UPB_NORETURN UPB_PRINTF(2, 3) static void ReportErrorFormat(upb_Tokenizer* t,
                                                            const char* fmt,
                                                            ...) {
  va_list args;
  va_start(args, fmt);
  char msg[128];
  vsnprintf(msg, sizeof(msg), fmt, args);
  ReportError(t, msg);
}

static void Refresh(upb_Tokenizer* t) {
  if (t->read_error) {
    t->current_char = '\0';
    return;
  }

  if (t->record_target != NULL && t->record_start < t->buffer_size) {
    upb_String_Append(t->record_target, t->buffer + t->record_start,
                      t->buffer_size - t->record_start);
    t->record_start = 0;
  }

  t->buffer = NULL;
  t->buffer_pos = 0;

  upb_Status status;
  const void* data =
      upb_ZeroCopyInputStream_Next(t->input, &t->buffer_size, &status);

  if (t->buffer_size > 0) {
    t->buffer = data;
    t->current_char = t->buffer[0];
  } else {

    t->buffer_size = 0;
    t->read_error = true;
    t->current_char = '\0';
  }
}

static void NextChar(upb_Tokenizer* t) {

  if (t->current_char == '\n') {
    t->line++;
    t->column = 0;
  } else if (t->current_char == '\t') {
    t->column += kUpb_Tokenizer_TabWidth - t->column % kUpb_Tokenizer_TabWidth;
  } else {
    t->column++;
  }

  t->buffer_pos++;
  if (t->buffer_pos < t->buffer_size) {
    t->current_char = t->buffer[t->buffer_pos];
  } else {
    Refresh(t);
  }
}

static void RecordTo(upb_Tokenizer* t, upb_String* target) {
  t->record_target = target;
  t->record_start = t->buffer_pos;
}

static void StopRecording(upb_Tokenizer* t) {
  if (t->buffer_pos > t->record_start) {
    upb_String_Append(t->record_target, t->buffer + t->record_start,
                      t->buffer_pos - t->record_start);
  }
  t->record_target = NULL;
  t->record_start = -1;
}

static void StartToken(upb_Tokenizer* t) {
  t->token_type = kUpb_TokenType_Start;
  upb_String_Clear(&t->token_text);
  t->token_line = t->line;
  t->token_column = t->column;
  RecordTo(t, &t->token_text);
}

static void EndToken(upb_Tokenizer* t) {
  StopRecording(t);
  t->token_end_column = t->column;
}

static bool LookingAt(const upb_Tokenizer* t, bool (*f)(char)) {
  return f(t->current_char);
}

static bool TryConsumeOne(upb_Tokenizer* t, bool (*f)(char)) {
  if (f(t->current_char)) {
    NextChar(t);
    return true;
  } else {
    return false;
  }
}

static bool TryConsume(upb_Tokenizer* t, char c) {
  if (t->current_char == c) {
    NextChar(t);
    return true;
  } else {
    return false;
  }
}

static void ConsumeZeroOrMore(upb_Tokenizer* t, bool (*f)(char)) {
  while (f(t->current_char)) {
    NextChar(t);
  }
}

static void ConsumeOneOrMore(upb_Tokenizer* t, bool (*f)(char),
                             const char* err_msg) {
  if (!f(t->current_char)) {
    ReportError(t, err_msg);
  }

  do {
    NextChar(t);
  } while (f(t->current_char));
}

static void ConsumeString(upb_Tokenizer* t, char delimiter) {
  while (true) {
    switch (t->current_char) {
      case '\0':
        ReportError(t, "Unexpected end of string.");

      case '\n':
        ReportError(t, "String literals cannot cross line boundaries.");

      case '\\': {
        // An escape sequence.
        NextChar(t);
        if (TryConsumeOne(t, upb_Tokenizer_IsEscape)) {
          // Valid escape sequence.
        } else if (TryConsumeOne(t, upb_Tokenizer_IsOctalDigit)) {
          // Possibly followed by two more octal digits, but these will
          // just be consumed by the main loop anyway so we don't need

        } else if (TryConsume(t, 'x')) {
          if (!TryConsumeOne(t, upb_Tokenizer_IsHexDigit)) {
            ReportError(t, "Expected hex digits for escape sequence.");
          }

        } else if (TryConsume(t, 'u')) {
          if (!TryConsumeOne(t, upb_Tokenizer_IsHexDigit) ||
              !TryConsumeOne(t, upb_Tokenizer_IsHexDigit) ||
              !TryConsumeOne(t, upb_Tokenizer_IsHexDigit) ||
              !TryConsumeOne(t, upb_Tokenizer_IsHexDigit)) {
            ReportError(t, "Expected four hex digits for \\u escape sequence.");
          }
        } else if (TryConsume(t, 'U')) {

          if (!TryConsume(t, '0') || !TryConsume(t, '0') ||
              !(TryConsume(t, '0') || TryConsume(t, '1')) ||
              !TryConsumeOne(t, upb_Tokenizer_IsHexDigit) ||
              !TryConsumeOne(t, upb_Tokenizer_IsHexDigit) ||
              !TryConsumeOne(t, upb_Tokenizer_IsHexDigit) ||
              !TryConsumeOne(t, upb_Tokenizer_IsHexDigit) ||
              !TryConsumeOne(t, upb_Tokenizer_IsHexDigit)) {
            ReportError(t,
                        "Expected eight hex digits up to 10ffff for \\U escape "
                        "sequence");
          }
        } else {
          ReportError(t, "Invalid escape sequence in string literal.");
        }
        break;
      }

      default: {
        if (t->current_char == delimiter) {
          NextChar(t);
          return;
        }
        NextChar(t);
        break;
      }
    }
  }
}

static upb_TokenType ConsumeNumber(upb_Tokenizer* t, bool started_with_zero,
                                   bool started_with_dot) {
  bool is_float = false;

  if (started_with_zero && (TryConsume(t, 'x') || TryConsume(t, 'X'))) {

    ConsumeOneOrMore(t, upb_Tokenizer_IsHexDigit,
                     "\"0x\" must be followed by hex digits.");

  } else if (started_with_zero && LookingAt(t, upb_Tokenizer_IsDigit)) {

    ConsumeZeroOrMore(t, upb_Tokenizer_IsOctalDigit);
    if (LookingAt(t, upb_Tokenizer_IsDigit)) {
      ReportError(t, "Numbers starting with leading zero must be in octal.");
    }

  } else {

    if (started_with_dot) {
      is_float = true;
      ConsumeZeroOrMore(t, upb_Tokenizer_IsDigit);
    } else {
      ConsumeZeroOrMore(t, upb_Tokenizer_IsDigit);

      if (TryConsume(t, '.')) {
        is_float = true;
        ConsumeZeroOrMore(t, upb_Tokenizer_IsDigit);
      }
    }

    if (TryConsume(t, 'e') || TryConsume(t, 'E')) {
      is_float = true;
      if (!TryConsume(t, '-')) TryConsume(t, '+');
      ConsumeOneOrMore(t, upb_Tokenizer_IsDigit,
                       "\"e\" must be followed by exponent.");
    }

    if (t->options & kUpb_TokenizerOption_AllowFAfterFloat) {
      if (TryConsume(t, 'f') || TryConsume(t, 'F')) is_float = true;
    }
  }

  if (LookingAt(t, upb_Tokenizer_IsLetter)) {
    ReportError(t, "Need space between number and identifier.");
  }

  if (t->current_char == '.') {
    if (is_float) {
      ReportError(
          t, "Already saw decimal point or exponent; can't have another one.");
    } else {
      ReportError(t, "Hex and octal numbers must be integers.");
    }
  }

  return is_float ? kUpb_TokenType_Float : kUpb_TokenType_Integer;
}

static void ConsumeLineComment(upb_Tokenizer* t, upb_String* content) {
  if (content != NULL) RecordTo(t, content);

  while (t->current_char != '\0' && t->current_char != '\n') {
    NextChar(t);
  }
  TryConsume(t, '\n');

  if (content != NULL) StopRecording(t);
}

static void ConsumeBlockComment(upb_Tokenizer* t, upb_String* content) {
  const int start_line = t->line;
  const int start_column = t->column - 2;

  if (content != NULL) RecordTo(t, content);

  while (true) {
    while (t->current_char != '\0' && t->current_char != '*' &&
           t->current_char != '/' && t->current_char != '\n') {
      NextChar(t);
    }

    if (TryConsume(t, '\n')) {
      if (content != NULL) StopRecording(t);

      ConsumeZeroOrMore(t, upb_Tokenizer_IsWhitespaceNoNewline);
      if (TryConsume(t, '*')) {
        if (TryConsume(t, '/')) {

          break;
        }
      }

      if (content != NULL) RecordTo(t, content);
    } else if (TryConsume(t, '*') && TryConsume(t, '/')) {

      if (content != NULL) {
        StopRecording(t);

        upb_String_Erase(content, upb_String_Size(content) - 2, 2);
      }
      break;
    } else if (TryConsume(t, '/') && t->current_char == '*') {
      // Note:  We didn't consume the '*' because if there is a '/' after it

      ReportError(
          t, "\"/*\" inside block comment.  Block comments cannot be nested.");
    } else if (t->current_char == '\0') {
      ReportErrorFormat(
          t, "End-of-file inside block comment.\n%d:%d: Comment started here.",
          start_line, start_column);
    }
  }
}

static upb_CommentType TryConsumeCommentStart(upb_Tokenizer* t) {
  const bool style_sh = t->options & kUpb_TokenizerOption_CommentStyleShell;
  const bool style_cpp = !style_sh;

  if (style_cpp && TryConsume(t, '/')) {
    if (TryConsume(t, '/')) {
      return kUpb_CommentType_Line;
    } else if (TryConsume(t, '*')) {
      return kUpb_CommentType_Block;
    } else {

      t->token_type = kUpb_TokenType_Symbol;
      upb_String_Assign(&t->token_text, "/", 1);
      t->token_line = t->line;
      t->token_column = t->column - 1;
      t->token_end_column = t->column;
      return kUpb_CommentType_SlashNot;
    }
  } else if (style_sh && TryConsume(t, '#')) {
    return kUpb_CommentType_Line;
  } else {
    return kUpb_CommentType_None;
  }
}

static bool TryConsumeWhitespace(upb_Tokenizer* t) {
  if (t->options & kUpb_TokenizerOption_ReportNewlines) {
    if (TryConsumeOne(t, upb_Tokenizer_IsWhitespaceNoNewline)) {
      ConsumeZeroOrMore(t, upb_Tokenizer_IsWhitespaceNoNewline);
      t->token_type = kUpb_TokenType_Whitespace;
      return true;
    }
    return false;
  }
  if (TryConsumeOne(t, upb_Tokenizer_IsWhitespace)) {
    ConsumeZeroOrMore(t, upb_Tokenizer_IsWhitespace);
    t->token_type = kUpb_TokenType_Whitespace;
    return (t->options & kUpb_TokenizerOption_ReportWhitespace) != 0;
  }
  return false;
}

static bool TryConsumeNewline(upb_Tokenizer* t) {
  if (t->options & kUpb_TokenizerOption_ReportNewlines) {
    if (TryConsume(t, '\n')) {
      t->token_type = kUpb_TokenType_Newline;
      return true;
    }
  }
  return false;
}

int upb_Tokenizer_Column(const upb_Tokenizer* t) { return t->token_column; }

int upb_Tokenizer_EndColumn(const upb_Tokenizer* t) {
  return t->token_end_column;
}

int upb_Tokenizer_Line(const upb_Tokenizer* t) { return t->token_line; }

int upb_Tokenizer_TextSize(const upb_Tokenizer* t) {
  return t->token_text.size_;
}

const char* upb_Tokenizer_TextData(const upb_Tokenizer* t) {
  return t->token_text.data_;
}

upb_TokenType upb_Tokenizer_Type(const upb_Tokenizer* t) {
  return t->token_type;
}

bool upb_Tokenizer_Next(upb_Tokenizer* t, upb_Status* status) {
  t->status = status;
  t->previous_type = t->token_type;
  t->previous_line = t->token_line;
  t->previous_column = t->token_column;
  t->previous_end_column = t->token_end_column;

  if (UPB_SETJMP(t->err)) return false;

  while (!t->read_error) {
    StartToken(t);
    bool report_token = TryConsumeWhitespace(t) || TryConsumeNewline(t);
    EndToken(t);
    if (report_token) return true;

    switch (TryConsumeCommentStart(t)) {
      case kUpb_CommentType_Line:
        ConsumeLineComment(t, NULL);
        continue;
      case kUpb_CommentType_Block:
        ConsumeBlockComment(t, NULL);
        continue;
      case kUpb_CommentType_SlashNot:
        return true;
      case kUpb_CommentType_None:
        break;
    }

    if (t->read_error) break;

    if (LookingAt(t, upb_Tokenizer_IsUnprintable) || t->current_char == '\0') {
      ReportError(t, "Invalid control characters encountered in text.");
    }

    StartToken(t);

    if (TryConsumeOne(t, upb_Tokenizer_IsLetter)) {
      ConsumeZeroOrMore(t, upb_Tokenizer_IsAlphanumeric);
      t->token_type = kUpb_TokenType_Identifier;
    } else if (TryConsume(t, '0')) {
      t->token_type = ConsumeNumber(t, true, false);
    } else if (TryConsume(t, '.')) {

      if (TryConsumeOne(t, upb_Tokenizer_IsDigit)) {

        if (t->previous_type == kUpb_TokenType_Identifier &&
            t->token_line == t->previous_line &&
            t->token_column == t->previous_end_column) {

          t->column -= 2;
          ReportError(t, "Need space between identifier and decimal point.");
        }
        t->token_type = ConsumeNumber(t, false, true);
      } else {
        t->token_type = kUpb_TokenType_Symbol;
      }
    } else if (TryConsumeOne(t, upb_Tokenizer_IsDigit)) {
      t->token_type = ConsumeNumber(t, false, false);
    } else if (TryConsume(t, '\"')) {
      ConsumeString(t, '\"');
      t->token_type = kUpb_TokenType_String;
    } else if (TryConsume(t, '\'')) {
      ConsumeString(t, '\'');
      t->token_type = kUpb_TokenType_String;
    } else {

      if (t->current_char & 0x80) {
        ReportErrorFormat(t, "Interpreting non ascii codepoint %d.",
                          (uint8_t)t->current_char);
      }
      NextChar(t);
      t->token_type = kUpb_TokenType_Symbol;
    }

    EndToken(t);
    return true;
  }

  t->token_type = kUpb_TokenType_End;
  upb_String_Clear(&t->token_text);
  t->token_line = t->line;
  t->token_column = t->column;
  t->token_end_column = t->column;
  upb_Status_Clear(status);
  return false;
}

bool upb_Parse_Integer(const char* text, uint64_t max_value, uint64_t* output) {

  const char* ptr = text;
  int base = 10;
  uint64_t overflow_if_mul_base = (UINT64_MAX / 10) + 1;
  if (ptr[0] == '0') {
    if (ptr[1] == 'x' || ptr[1] == 'X') {

      base = 16;
      overflow_if_mul_base = (UINT64_MAX / 16) + 1;
      ptr += 2;
    } else {

      base = 8;
      overflow_if_mul_base = (UINT64_MAX / 8) + 1;
    }
  }

  uint64_t result = 0;

  while (*ptr != '\0') {
    int digit = DigitValue(*ptr++);
    if (digit >= base) {

      return false;
    }
    if (digit != 0) {
      result = digit;
      break;
    }
  }
  for (; *ptr != '\0'; ptr++) {
    int digit = DigitValue(*ptr);
    if (digit < 0 || digit >= base) {

      return false;
    }
    if (result >= overflow_if_mul_base) {

      return false;
    }

    result = result * base + digit;

    if (result < (uint64_t)base) return false;
  }
  if (result > max_value) return false;

  *output = result;
  return true;
}

double upb_Parse_Float(const char* text) {
  char* end;
  double result = _upb_NoLocaleStrtod(text, &end);

  if (*end == 'e' || *end == 'E') {
    ++end;
    if (*end == '-' || *end == '+') ++end;
  }

  if (*end == 'f' || *end == 'F') {
    ++end;
  }

  if ((end - text) != strlen(text) || *text == '-') {
    fprintf(stderr,
            "upb_Parse_Float() passed text that could not have"
            " been tokenized as a float: %s\n",
            text);
    UPB_ASSERT(0);
  }
  return result;
}

static void AppendUTF8(uint32_t code_point, upb_String* output) {
  char temp[24];
  int len = upb_Unicode_ToUTF8(code_point, temp);
  if (len == 0) {

    len = snprintf(temp, sizeof temp, "\\U%08x", code_point);
  }
  upb_String_Append(output, temp, len);
}

static bool ReadHexDigits(const char* ptr, int len, uint32_t* result) {
  *result = 0;
  if (len == 0) return false;
  for (const char* end = ptr + len; ptr < end; ++ptr) {
    if (*ptr == '\0') return false;
    *result = (*result << 4) + DigitValue(*ptr);
  }
  return true;
}

static int UnicodeLength(char key) {
  if (key == 'u') return 4;
  if (key == 'U') return 8;
  return 0;
}

static const char* FetchUnicodePoint(const char* ptr, uint32_t* code_point) {
  const char* p = ptr;

  const int len = UnicodeLength(*p++);
  if (!ReadHexDigits(p, len, code_point)) return ptr;
  p += len;

  if (upb_Unicode_IsHigh(*code_point) && *p == '\\' && *(p + 1) == 'u') {
    uint32_t trail_surrogate;
    if (ReadHexDigits(p + 2, 4, &trail_surrogate) &&
        upb_Unicode_IsLow(trail_surrogate)) {
      *code_point = upb_Unicode_FromPair(*code_point, trail_surrogate);
      p += 6;
    }
    // If this failed, then we just emit the head surrogate as a code point.
    // It's bogus, but so is the string.
  }

  return p;
}

upb_StringView upb_Parse_String(const char* text, upb_Arena* arena) {
  const size_t size = strlen(text);

  upb_String output;
  upb_String_Init(&output, arena);

  if (size == 0) {
    fprintf(stderr,
            "Tokenizer::ParseStringAppend() passed text that could not"
            " have been tokenized as a string: %s",
            text);
    UPB_ASSERT(0);
    return upb_StringView_FromDataAndSize(NULL, 0);
  }

  const size_t new_len = size + upb_String_Size(&output);
  upb_String_Reserve(&output, new_len);

  for (const char* ptr = text + 1; *ptr != '\0'; ptr++) {
    if (*ptr == '\\' && ptr[1] != '\0') {
      // An escape sequence.
      ++ptr;

      if (upb_Tokenizer_IsOctalDigit(*ptr)) {
        // An octal escape.  May one, two, or three digits.
        int code = DigitValue(*ptr);
        if (upb_Tokenizer_IsOctalDigit(ptr[1])) {
          ++ptr;
          code = code * 8 + DigitValue(*ptr);
        }
        if (upb_Tokenizer_IsOctalDigit(ptr[1])) {
          ++ptr;
          code = code * 8 + DigitValue(*ptr);
        }
        upb_String_PushBack(&output, (char)code);

      } else if (*ptr == 'x') {
        // A hex escape.  May zero, one, or two digits.  (The zero case
        // will have been caught as an error earlier.)
        int code = 0;
        if (upb_Tokenizer_IsHexDigit(ptr[1])) {
          ++ptr;
          code = DigitValue(*ptr);
        }
        if (upb_Tokenizer_IsHexDigit(ptr[1])) {
          ++ptr;
          code = code * 16 + DigitValue(*ptr);
        }
        upb_String_PushBack(&output, (char)code);

      } else if (*ptr == 'u' || *ptr == 'U') {
        uint32_t unicode;
        const char* end = FetchUnicodePoint(ptr, &unicode);
        if (end == ptr) {
          // Failure: Just dump out what we saw, don't try to parse it.
          upb_String_PushBack(&output, *ptr);
        } else {
          AppendUTF8(unicode, &output);
          ptr = end - 1;
        }
      } else {

        upb_String_PushBack(&output, TranslateEscape(*ptr));
      }

    } else if (*ptr == text[0] && ptr[1] == '\0') {

    } else {
      upb_String_PushBack(&output, *ptr);
    }
  }

  return upb_StringView_FromDataAndSize(upb_String_Data(&output),
                                        upb_String_Size(&output));
}

static bool AllInClass(bool (*f)(char), const char* text, int size) {
  for (int i = 0; i < size; i++) {
    if (!f(text[i])) return false;
  }
  return true;
}

bool upb_Tokenizer_IsIdentifier(const char* data, int size) {

  if (size == 0) return false;
  if (!upb_Tokenizer_IsLetter(data[0])) return false;
  if (!AllInClass(upb_Tokenizer_IsAlphanumeric, data + 1, size - 1))
    return false;
  return true;
}

upb_Tokenizer* upb_Tokenizer_New(const void* data, size_t size,
                                 upb_ZeroCopyInputStream* input, int options,
                                 upb_Arena* arena) {
  upb_Tokenizer* t = upb_Arena_Malloc(arena, sizeof(upb_Tokenizer));
  if (!t) return NULL;

  t->input = input;
  t->arena = arena;
  t->buffer = data;
  t->buffer_size = size;
  t->buffer_pos = 0;
  t->read_error = false;
  t->line = 0;
  t->column = 0;
  t->record_target = NULL;
  t->record_start = -1;

  if (options & kUpb_TokenizerOption_ReportNewlines) {
    options |= kUpb_TokenizerOption_ReportWhitespace;
  }
  t->options = options;

  upb_String_Init(&t->token_text, arena);
  t->token_type = kUpb_TokenType_Start;
  t->token_line = 0;
  t->token_column = 0;
  t->token_end_column = 0;

  t->previous_type = kUpb_TokenType_Start;
  t->previous_line = 0;
  t->previous_column = 0;
  t->previous_end_column = 0;

  if (size) {
    t->current_char = t->buffer[0];
  } else {
    Refresh(t);
  }
  return t;
}

void upb_Tokenizer_Fini(upb_Tokenizer* t) {

  if (t->buffer_size > t->buffer_pos) {
    upb_ZeroCopyInputStream_BackUp(t->input, t->buffer_size - t->buffer_pos);
  }
}

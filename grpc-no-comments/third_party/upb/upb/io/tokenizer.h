
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_IO_TOKENIZER_H_
#define UPB_IO_TOKENIZER_H_

#include "upb/base/status.h"
#include "upb/base/string_view.h"
#include "upb/io/zero_copy_input_stream.h"
#include "upb/mem/arena.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  kUpb_TokenType_Start,
  kUpb_TokenType_End,

  kUpb_TokenType_Identifier,

  kUpb_TokenType_Integer,

  kUpb_TokenType_Float,

  kUpb_TokenType_String,

  kUpb_TokenType_Symbol,

  kUpb_TokenType_Whitespace,

  kUpb_TokenType_Newline,
} upb_TokenType;

typedef enum {

  kUpb_TokenizerOption_AllowFAfterFloat = 1 << 0,

  kUpb_TokenizerOption_ReportWhitespace = 1 << 1,

  kUpb_TokenizerOption_ReportNewlines = 1 << 2,

  kUpb_TokenizerOption_CommentStyleShell = 1 << 3,
} upb_Tokenizer_Option;

typedef struct upb_Tokenizer upb_Tokenizer;

upb_Tokenizer* upb_Tokenizer_New(const void* data, size_t size,
                                 upb_ZeroCopyInputStream* input, int options,
                                 upb_Arena* arena);

void upb_Tokenizer_Fini(upb_Tokenizer* t);

bool upb_Tokenizer_Next(upb_Tokenizer* t, upb_Status* status);

upb_TokenType upb_Tokenizer_Type(const upb_Tokenizer* t);
int upb_Tokenizer_Column(const upb_Tokenizer* t);
int upb_Tokenizer_EndColumn(const upb_Tokenizer* t);
int upb_Tokenizer_Line(const upb_Tokenizer* t);
int upb_Tokenizer_TextSize(const upb_Tokenizer* t);
const char* upb_Tokenizer_TextData(const upb_Tokenizer* t);

bool upb_Tokenizer_IsIdentifier(const char* data, int size);

bool upb_Parse_Integer(const char* text, uint64_t max_value, uint64_t* output);

double upb_Parse_Float(const char* text);

upb_StringView upb_Parse_String(const char* text, upb_Arena* arena);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif

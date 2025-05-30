
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_DEF_BUILDER_INTERNAL_H_
#define UPB_REFLECTION_DEF_BUILDER_INTERNAL_H_

#include <setjmp.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "upb/base/status.h"
#include "upb/base/string_view.h"
#include "upb/hash/common.h"
#include "upb/hash/str_table.h"
#include "upb/mem/arena.h"
#include "upb/mini_descriptor/decode.h"
#include "upb/mini_table/file.h"
#include "upb/reflection/common.h"
#include "upb/reflection/def_type.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#define UPB_DEF_SET_OPTIONS(target, desc_type, options_type, proto)           \
  if (UPB_DESC(desc_type##_has_options)(proto)) {                             \
    size_t size;                                                              \
    char* pb = UPB_DESC(options_type##_serialize)(                            \
        UPB_DESC(desc_type##_options)(proto), ctx->tmp_arena, &size);         \
    if (!pb) _upb_DefBuilder_OomErr(ctx);                                     \
    target =                                                                  \
        UPB_DESC(options_type##_parse)(pb, size, _upb_DefBuilder_Arena(ctx)); \
    if (!target) _upb_DefBuilder_OomErr(ctx);                                 \
  } else {                                                                    \
    target = (const UPB_DESC(options_type)*)kUpbDefOptDefault;                \
  }

#ifdef __cplusplus
extern "C" {
#endif

struct upb_DefBuilder {
  upb_DefPool* symtab;
  upb_strtable feature_cache;
  UPB_DESC(FeatureSet*) legacy_features;
  char* tmp_buf;
  size_t tmp_buf_size;
  upb_FileDef* file;
  upb_Arena* arena;
  upb_Arena* tmp_arena;
  upb_Status* status;
  const upb_MiniTableFile* layout;
  upb_MiniTablePlatform platform;
  int enum_count;
  int msg_count;
  int ext_count;
  jmp_buf err;
};

extern const char* kUpbDefOptDefault;

UPB_NORETURN void _upb_DefBuilder_FailJmp(upb_DefBuilder* ctx);

UPB_NORETURN void _upb_DefBuilder_Errf(upb_DefBuilder* ctx, const char* fmt,
                                       ...) UPB_PRINTF(2, 3);
UPB_NORETURN void _upb_DefBuilder_OomErr(upb_DefBuilder* ctx);

const char* _upb_DefBuilder_MakeFullName(upb_DefBuilder* ctx,
                                         const char* prefix,
                                         upb_StringView name);

const void* _upb_DefBuilder_ResolveAny(upb_DefBuilder* ctx,
                                       const char* from_name_dbg,
                                       const char* base, upb_StringView sym,
                                       upb_deftype_t* type);

const void* _upb_DefBuilder_Resolve(upb_DefBuilder* ctx,
                                    const char* from_name_dbg, const char* base,
                                    upb_StringView sym, upb_deftype_t type);

char _upb_DefBuilder_ParseEscape(upb_DefBuilder* ctx, const upb_FieldDef* f,
                                 const char** src, const char* end);

const char* _upb_DefBuilder_FullToShort(const char* fullname);

UPB_INLINE void* _upb_DefBuilder_Alloc(upb_DefBuilder* ctx, size_t bytes) {
  if (bytes == 0) return NULL;
  void* ret = upb_Arena_Malloc(ctx->arena, bytes);
  if (!ret) _upb_DefBuilder_OomErr(ctx);
  return ret;
}

UPB_INLINE void* _upb_DefBuilder_AllocCounted(upb_DefBuilder* ctx, size_t size,
                                              size_t count) {
  if (count == 0) return NULL;
  if (SIZE_MAX / size < count) {
    _upb_DefBuilder_OomErr(ctx);
  }
  return _upb_DefBuilder_Alloc(ctx, size * count);
}

#define UPB_DEFBUILDER_ALLOCARRAY(ctx, type, count) \
  ((type*)_upb_DefBuilder_AllocCounted(ctx, sizeof(type), (count)))

UPB_INLINE void _upb_DefBuilder_Add(upb_DefBuilder* ctx, const char* name,
                                    upb_value v) {
  upb_StringView sym = {.data = name, .size = strlen(name)};
  bool ok = _upb_DefPool_InsertSym(ctx->symtab, sym, v, ctx->status);
  if (!ok) _upb_DefBuilder_FailJmp(ctx);
}

UPB_INLINE upb_Arena* _upb_DefBuilder_Arena(const upb_DefBuilder* ctx) {
  return ctx->arena;
}

UPB_INLINE upb_FileDef* _upb_DefBuilder_File(const upb_DefBuilder* ctx) {
  return ctx->file;
}

void _upb_DefBuilder_CheckIdentSlow(upb_DefBuilder* ctx, upb_StringView name,
                                    bool full);

UPB_INLINE void _upb_DefBuilder_CheckIdentFull(upb_DefBuilder* ctx,
                                               upb_StringView name) {
  bool good = name.size > 0;
  bool start = true;

  for (size_t i = 0; i < name.size; i++) {
    const char c = name.data[i];
    const char d = c | 0x20;
    const bool is_alpha = (('a' <= d) & (d <= 'z')) | (c == '_');
    const bool is_numer = ('0' <= c) & (c <= '9') & !start;
    const bool is_dot = (c == '.') & !start;

    good &= is_alpha | is_numer | is_dot;
    start = is_dot;
  }

  if (!good) _upb_DefBuilder_CheckIdentSlow(ctx, name, true);
}

bool _upb_DefBuilder_GetOrCreateFeatureSet(upb_DefBuilder* ctx,
                                           const UPB_DESC(FeatureSet*) parent,
                                           upb_StringView key,
                                           UPB_DESC(FeatureSet**) set);

const UPB_DESC(FeatureSet*)
    _upb_DefBuilder_DoResolveFeatures(upb_DefBuilder* ctx,
                                      const UPB_DESC(FeatureSet*) parent,
                                      const UPB_DESC(FeatureSet*) child,
                                      bool is_implicit);

UPB_INLINE const UPB_DESC(FeatureSet*)
    _upb_DefBuilder_ResolveFeatures(upb_DefBuilder* ctx,
                                    const UPB_DESC(FeatureSet*) parent,
                                    const UPB_DESC(FeatureSet*) child) {
  return _upb_DefBuilder_DoResolveFeatures(ctx, parent, child, false);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif

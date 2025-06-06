#include "upb/message/merge.h"

#include "stddef.h"
#include "upb/mem/arena.h"
#include "upb/message/message.h"
#include "upb/mini_table/extension_registry.h"
#include "upb/mini_table/message.h"
#include "upb/wire/decode.h"
#include "upb/wire/encode.h"

#include "upb/port/def.inc"

bool upb_Message_MergeFrom(upb_Message* dst, const upb_Message* src,
                           const upb_MiniTable* mt,
                           const upb_ExtensionRegistry* extreg,
                           upb_Arena* arena) {
  char* buf = NULL;
  size_t size = 0;

  upb_Arena* encode_arena = upb_Arena_New();
  upb_EncodeStatus e_status = upb_Encode(src, mt, 0, encode_arena, &buf, &size);
  if (e_status != kUpb_EncodeStatus_Ok) {
    upb_Arena_Free(encode_arena);
    return false;
  }
  upb_DecodeStatus d_status = upb_Decode(buf, size, dst, mt, extreg, 0, arena);
  if (d_status != kUpb_DecodeStatus_Ok) {
    upb_Arena_Free(encode_arena);
    return false;
  }
  upb_Arena_Free(encode_arena);
  return true;
}

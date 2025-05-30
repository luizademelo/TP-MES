
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_TEST_FUZZ_UTIL_H_
#define UPB_TEST_FUZZ_UTIL_H_

#include <string>
#include <vector>

#include "upb/mem/arena.h"
#include "upb/mini_table/extension_registry.h"
#include "upb/mini_table/message.h"

namespace upb {
namespace fuzz {

struct MiniTableFuzzInput {

  std::vector<std::string> mini_descriptors;

  std::vector<std::string> enum_mini_descriptors;

  std::string extensions;

  std::vector<uint32_t> links;
};

// TODO: maps.  If we give maps some space in the regular encoding instead of

const upb_MiniTable* BuildMiniTable(const MiniTableFuzzInput& input,
                                    upb_ExtensionRegistry** exts,
                                    upb_Arena* arena);

}
}

#endif

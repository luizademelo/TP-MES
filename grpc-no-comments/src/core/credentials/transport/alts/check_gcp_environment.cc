
// Copyright 2018 gRPC authors.

#include "src/core/credentials/transport/alts/check_gcp_environment.h"

#include <ctype.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <stdio.h>
#include <string.h>

#include "absl/log/log.h"

const size_t kBiosDataBufferSize = 256;

static char* trim(const char* src) {
  if (src == nullptr || *src == '\0') {
    return nullptr;
  }
  char* des = nullptr;
  size_t start = 0, end = strlen(src) - 1;

  while (end != 0 && isspace(src[end])) {
    end--;
  }

  while (start < strlen(src) && isspace(src[start])) {
    start++;
  }
  if (start <= end) {
    des = static_cast<char*>(
        gpr_zalloc(sizeof(char) * (end - start + 2 )));
    memcpy(des, src + start, end - start + 1);
  }
  return des;
}

namespace grpc_core {
namespace internal {

char* read_bios_file(const char* bios_file) {
  FILE* fp = fopen(bios_file, "r");
  if (!fp) {
    VLOG(2) << "BIOS data file does not exist or cannot be opened.";
    return nullptr;
  }
  char buf[kBiosDataBufferSize + 1];
  size_t ret = fread(buf, sizeof(char), kBiosDataBufferSize, fp);
  buf[ret] = '\0';
  char* trimmed_buf = trim(buf);
  fclose(fp);
  return trimmed_buf;
}

}
}

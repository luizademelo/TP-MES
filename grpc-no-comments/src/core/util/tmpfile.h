
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_TMPFILE_H
#define GRPC_SRC_CORE_UTIL_TMPFILE_H

#include <grpc/support/port_platform.h>
#include <stdio.h>

FILE* gpr_tmpfile(const char* prefix, char** tmp_filename);

#endif

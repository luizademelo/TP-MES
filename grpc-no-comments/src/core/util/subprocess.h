
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_SUBPROCESS_H
#define GRPC_SRC_CORE_UTIL_SUBPROCESS_H

#include <grpc/support/port_platform.h>

#include <string>

typedef struct gpr_subprocess gpr_subprocess;

const char* gpr_subprocess_binary_extension();

gpr_subprocess* gpr_subprocess_create(int argc, const char** argv);

gpr_subprocess* gpr_subprocess_create_with_envp(int argc, const char** argv,
                                                int envc, const char** envp);

bool gpr_subprocess_communicate(gpr_subprocess* p, std::string& input_data,
                                std::string* output_data, std::string* error);

void gpr_subprocess_destroy(gpr_subprocess* p);

int gpr_subprocess_join(gpr_subprocess* p);
void gpr_subprocess_interrupt(gpr_subprocess* p);
int gpr_subprocess_get_process_id(gpr_subprocess* p);

#endif

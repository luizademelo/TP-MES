
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_CMDLINE_H
#define GRPC_TEST_CORE_TEST_UTIL_CMDLINE_H

#include <grpc/support/port_platform.h>

#include <string>

#include "absl/log/log.h"

typedef struct gpr_cmdline gpr_cmdline;

gpr_cmdline* gpr_cmdline_create(const char* description);

void gpr_cmdline_add_int(gpr_cmdline* cl, const char* name, const char* help,
                         int* value);

void gpr_cmdline_add_flag(gpr_cmdline* cl, const char* name, const char* help,
                          int* value);

void gpr_cmdline_add_string(gpr_cmdline* cl, const char* name, const char* help,
                            const char** value);

void gpr_cmdline_on_extra_arg(
    gpr_cmdline* cl, const char* name, const char* help,
    void (*on_extra_arg)(void* user_data, const char* arg), void* user_data);

void gpr_cmdline_set_survive_failure(gpr_cmdline* cl);

int gpr_cmdline_parse(gpr_cmdline* cl, int argc, char** argv);

void gpr_cmdline_destroy(gpr_cmdline* cl);

std::string gpr_cmdline_usage_string(gpr_cmdline* cl, const char* argv0);

#endif

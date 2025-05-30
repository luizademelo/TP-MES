
// Copyright 2017 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifndef GRPC_POSIX_FORK

#include <grpc/fork.h>

#include "absl/log/log.h"

// NOTE: FORKING IS NOT GENERALLY SUPPORTED, THIS IS ONLY INTENDED TO WORK

void grpc_prefork() { LOG(ERROR) << "Forking not supported on Windows"; }

void grpc_postfork_parent() {}

void grpc_postfork_child() {}

void grpc_fork_handlers_auto_register() {}

#endif

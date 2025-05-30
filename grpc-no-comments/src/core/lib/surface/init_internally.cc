// Copyright 2022 gRPC authors.

#include "src/core/lib/surface/init_internally.h"

#include <grpc/support/port_platform.h>

namespace grpc_core {

void (*InitInternally)();
void (*ShutdownInternally)();
bool (*IsInitializedInternally)();

}

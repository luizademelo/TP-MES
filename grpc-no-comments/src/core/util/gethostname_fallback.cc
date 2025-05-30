
// Copyright 2017 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"
#include "src/core/util/gethostname.h"

#ifdef GRPC_GETHOSTNAME_FALLBACK

#include <stddef.h>

char* grpc_gethostname() { return NULL; }

#endif

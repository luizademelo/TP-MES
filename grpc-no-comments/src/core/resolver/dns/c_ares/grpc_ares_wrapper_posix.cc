
// Copyright 2016 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"
#if GRPC_ARES == 1 && defined(GRPC_POSIX_SOCKET_ARES_EV_DRIVER)

#include "src/core/lib/iomgr/socket_utils_posix.h"
#include "src/core/resolver/dns/c_ares/grpc_ares_wrapper.h"

bool grpc_ares_query_ipv6() { return grpc_ipv6_loopback_available(); }

#endif

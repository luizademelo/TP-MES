
// Copyright 2016 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#if GRPC_ARES == 1 && defined(GRPC_WINDOWS_SOCKET_ARES_EV_DRIVER)

#include <grpc/support/string_util.h>

#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/iomgr/socket_windows.h"
#include "src/core/resolver/dns/c_ares/grpc_ares_wrapper.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/util/string.h"

bool grpc_ares_query_ipv6() { return grpc_ipv6_loopback_available(); }

#endif

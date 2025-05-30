// Copyright 2022 gRPC authors.

#ifndef GRPC_TEST_CORE_EVENT_ENGINE_WINDOWS_CREATE_SOCKPAIR_H
#define GRPC_TEST_CORE_EVENT_ENGINE_WINDOWS_CREATE_SOCKPAIR_H

#include <grpc/support/port_platform.h>
#ifdef GPR_WINDOWS

#include <winsock2.h>

namespace grpc_event_engine {
namespace experimental {

sockaddr_in GetSomeIpv4LoopbackAddress();

void CreateSockpair(SOCKET sockpair[2], DWORD flags);

}
}

#endif
#endif

// Copyright 2021 The gRPC Authors

#ifndef GRPC_EVENT_ENGINE_PORT_H
#define GRPC_EVENT_ENGINE_PORT_H

#include <grpc/support/port_platform.h>

#if defined(GPR_ANDROID) || defined(GPR_LINUX) || defined(GPR_APPLE) ||     \
    defined(GPR_FREEBSD) || defined(GPR_OPENBSD) || defined(GPR_SOLARIS) || \
    defined(GPR_AIX) || defined(GPR_NACL) || defined(GPR_FUCHSIA) ||        \
    defined(GRPC_POSIX_SOCKET) || defined(GPR_NETBSD)
#define GRPC_EVENT_ENGINE_POSIX
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#elif defined(GPR_WINDOWS)
#include <winsock2.h>
#include <ws2tcpip.h>

#include <mswsock.h>
#else
#error UNKNOWN PLATFORM
#endif

#endif

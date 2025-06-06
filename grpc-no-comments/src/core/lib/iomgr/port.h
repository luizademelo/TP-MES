
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_PORT_H
#define GRPC_SRC_CORE_LIB_IOMGR_PORT_H

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS
#define GRPC_ARES_RESOLVE_LOCALHOST_MANUALLY 1
#endif
#if defined(GPR_WINDOWS)
#define GRPC_WINSOCK_SOCKET 1
#ifndef __MINGW32__
#define GRPC_HAVE_UNIX_SOCKET 1
#endif
#define GRPC_WINDOWS_SOCKETUTILS 1
#define GRPC_WINDOWS_SOCKET_ARES_EV_DRIVER 1
#elif defined(GPR_ANDROID)
#define GRPC_HAVE_IPV6_RECVPKTINFO 1
#define GRPC_HAVE_IP_PKTINFO 1
#define GRPC_HAVE_MSG_NOSIGNAL 1
#define GRPC_HAVE_UNIX_SOCKET 1
#if defined(LINUX_VERSION_CODE) && defined(__NDK_MAJOR__)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 9, 0) && __NDK_MAJOR__ >= 14
#define GRPC_HAVE_VSOCK 1
#endif
#endif
#define GRPC_LINUX_EVENTFD 1
#define GRPC_POSIX_SOCKET 1
#define GRPC_POSIX_SOCKETUTILS 1
#define GRPC_POSIX_WAKEUP_FD 1
#elif defined(GPR_LINUX)
#define GRPC_HAVE_ARPA_NAMESER 1
#define GRPC_HAVE_IFADDRS 1
#define GRPC_HAVE_IPV6_RECVPKTINFO 1
#define GRPC_HAVE_IP_PKTINFO 1
#define GRPC_HAVE_MSG_NOSIGNAL 1
#define GRPC_HAVE_UNIX_SOCKET 1

#define GRPC_HAVE_TCP_INQ 1
#ifdef LINUX_VERSION_CODE
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 0, 0)
#define GRPC_LINUX_ERRQUEUE 1
#endif
#endif
#if defined(LINUX_VERSION_CODE) && defined(__GLIBC_PREREQ)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 9, 0) && __GLIBC_PREREQ(2, 18)
#define GRPC_HAVE_VSOCK 1
#endif
#endif
#define GRPC_LINUX_MULTIPOLL_WITH_EPOLL 1
#define GRPC_POSIX_FORK 1
#define GRPC_POSIX_HOST_NAME_MAX 1
#define GRPC_POSIX_SOCKET 1
#define GRPC_POSIX_WAKEUP_FD 1
#ifdef __GLIBC_PREREQ
#if __GLIBC_PREREQ(2, 4)
#define GRPC_LINUX_EPOLL 1
#endif
#if __GLIBC_PREREQ(2, 9)
#define GRPC_LINUX_EPOLL_CREATE1 1
#define GRPC_LINUX_EVENTFD 1
#endif
#if __GLIBC_PREREQ(2, 10)
#define GRPC_LINUX_SOCKETUTILS 1
#endif
#if !(__GLIBC_PREREQ(2, 18))

#define GRPC_LINUX_TCP_H 1
#endif
#endif
#ifndef __GLIBC__
#define GRPC_LINUX_EPOLL 1
#define GRPC_LINUX_EPOLL_CREATE1 1
#define GRPC_LINUX_EVENTFD 1
#define GRPC_MSG_IOVLEN_TYPE int
#endif
#ifndef GRPC_LINUX_EVENTFD
#define GRPC_POSIX_NO_SPECIAL_WAKEUP_FD 1
#endif
#ifndef GRPC_LINUX_SOCKETUTILS
#define GRPC_POSIX_SOCKETUTILS
#endif
#elif defined(GPR_APPLE)
#define GRPC_HAVE_ARPA_NAMESER 1
#define GRPC_HAVE_IFADDRS 1
#define GRPC_HAVE_SO_NOSIGPIPE 1
#define GRPC_HAVE_UNIX_SOCKET 1
#define GRPC_MSG_IOVLEN_TYPE int
#define GRPC_POSIX_FORK 1
#define GRPC_POSIX_NO_SPECIAL_WAKEUP_FD 1
#ifdef GRPC_CFSTREAM
#define GRPC_CFSTREAM_IOMGR 1
#define GRPC_CFSTREAM_CLIENT 1
#define GRPC_CFSTREAM_ENDPOINT 1
#define GRPC_APPLE_EV 1
#define GRPC_POSIX_SOCKET_ARES_EV_DRIVER 1
#define GRPC_POSIX_SOCKET_EV 1
#define GRPC_POSIX_SOCKET_EV_EPOLL1 1
#define GRPC_POSIX_SOCKET_EV_POLL 1
#define GRPC_POSIX_SOCKET_IF_NAMETOINDEX 1
#define GRPC_POSIX_SOCKET_RESOLVE_ADDRESS 1
#define GRPC_POSIX_SOCKET_SOCKADDR 1
#define GRPC_POSIX_SOCKET_SOCKET_FACTORY 1
#define GRPC_POSIX_SOCKET_TCP 1
#define GRPC_POSIX_SOCKET_TCP_CLIENT 1
#define GRPC_POSIX_SOCKET_TCP_SERVER 1
#define GRPC_POSIX_SOCKET_TCP_SERVER_UTILS_COMMON 1
#define GRPC_POSIX_SOCKET_UDP_SERVER 1
#define GRPC_POSIX_SOCKET_UTILS_COMMON 1
#else
#define GRPC_POSIX_SOCKET 1
#endif
#define GRPC_POSIX_SOCKETUTILS 1
#define GRPC_POSIX_SYSCONF 1
#define GRPC_POSIX_WAKEUP_FD 1
#elif defined(GPR_FREEBSD)
#define GRPC_HAVE_ARPA_NAMESER 1
#define GRPC_HAVE_IFADDRS 1
#define GRPC_HAVE_IPV6_RECVPKTINFO 1
#define GRPC_HAVE_SO_NOSIGPIPE 1
#define GRPC_HAVE_UNIX_SOCKET 1
#define GRPC_POSIX_FORK 1
#define GRPC_POSIX_NO_SPECIAL_WAKEUP_FD 1
#define GRPC_POSIX_SOCKET 1
#define GRPC_POSIX_SOCKETUTILS 1
#define GRPC_POSIX_WAKEUP_FD 1
#elif defined(GPR_OPENBSD)
#define GRPC_HAVE_IFADDRS 1
#define GRPC_HAVE_IPV6_RECVPKTINFO 1
#define GRPC_HAVE_UNIX_SOCKET 1
#define GRPC_POSIX_NO_SPECIAL_WAKEUP_FD 1
#define GRPC_POSIX_SOCKET 1
#define GRPC_POSIX_SOCKETUTILS 1
#define GRPC_POSIX_WAKEUP_FD 1
#elif defined(GPR_SOLARIS)
#define GRPC_HAVE_UNIX_SOCKET 1
#define GRPC_POSIX_NO_SPECIAL_WAKEUP_FD 1
#define GRPC_POSIX_SOCKET 1
#define GRPC_POSIX_SOCKETUTILS 1
#define GRPC_POSIX_WAKEUP_FD 1
#elif defined(GPR_AIX)
#define GRPC_HAVE_UNIX_SOCKET 1
#define GRPC_POSIX_NO_SPECIAL_WAKEUP_FD 1
#define GRPC_POSIX_SOCKET 1
#define GRPC_POSIX_SOCKETUTILS 1
#define GRPC_POSIX_WAKEUP_FD 1
#elif defined(GPR_NETBSD)
#define GRPC_HAVE_ARPA_NAMESER 1
#define GRPC_HAVE_IFADDRS 1
#define GRPC_HAVE_IPV6_RECVPKTINFO 1
#define GRPC_HAVE_SO_NOSIGPIPE 1
#define GRPC_HAVE_UNIX_SOCKET 1
#define GRPC_POSIX_FORK 1
#define GRPC_POSIX_NO_SPECIAL_WAKEUP_FD 1
#define GRPC_POSIX_SOCKET 1
#define GRPC_POSIX_SOCKETUTILS 1
#define GRPC_POSIX_WAKEUP_FD 1
#elif defined(GPR_NACL)
#define GRPC_HAVE_ARPA_NAMESER 1
#define GRPC_POSIX_NO_SPECIAL_WAKEUP_FD 1
#define GRPC_POSIX_SOCKET 1
#define GRPC_POSIX_SOCKETUTILS 1
#define GRPC_POSIX_WAKEUP_FD 1
#elif defined(GPR_FUCHSIA)
#define GRPC_HAVE_IFADDRS 1
#define GRPC_HAVE_IPV6_RECVPKTINFO 1
#define GRPC_HAVE_IP_PKTINFO 1

#undef GRPC_HAVE_MSG_NOSIGNAL
#define GRPC_HAVE_UNIX_SOCKET 1
#define GRPC_POSIX_WAKEUP_FD 1

#define GRPC_POSIX_NO_SPECIAL_WAKEUP_FD 1
#define GRPC_POSIX_SOCKET 1
#define GRPC_POSIX_SOCKETADDR 1

#define GRPC_POSIX_SOCKETUTILS 1
#define GRPC_TIMER_USE_GENERIC 1
#elif defined(GPR_HAIKU)
#define GRPC_HAVE_ARPA_NAMESER 1
#define GRPC_HAVE_IFADDRS 1
#define GRPC_HAVE_IPV6_RECVPKTINFO 1
#define GRPC_HAVE_UNIX_SOCKET 1
#define GRPC_POSIX_FORK 1
#define GRPC_POSIX_NO_SPECIAL_WAKEUP_FD 1
#define GRPC_POSIX_SOCKET 1
#define GRPC_POSIX_SOCKETUTILS 1
#define GRPC_POSIX_WAKEUP_FD 1
#elif defined(__QNX__) || defined(__QNXNTO__)
#define GRPC_HAVE_ARPA_NAMESER 1
#define GRPC_HAVE_IFADDRS 1
#define GRPC_HAVE_IPV6_RECVPKTINFO 1
#define GRPC_HAVE_IP_PKTINFO 1
#define GRPC_HAVE_MSG_NOSIGNAL 1
#define GRPC_HAVE_UNIX_SOCKET 1

#define GRPC_POSIX_SOCKET 1
#define GRPC_POSIX_WAKEUP_FD 1
#define GRPC_POSIX_NO_SPECIAL_WAKEUP_FD 1
#define GRPC_POSIX_SOCKETUTILS 1
#define GRPC_POSIX_SYSCONF 1
#elif !defined(GPR_NO_AUTODETECT_PLATFORM)
#error "Platform not recognized"
#endif

#if defined(GRPC_POSIX_SOCKET) + defined(GRPC_WINSOCK_SOCKET) + \
        defined(GRPC_CFSTREAM) !=                               \
    1
#error \
    "Must define exactly one of GRPC_POSIX_SOCKET, GRPC_WINSOCK_SOCKET, GRPC_CFSTREAM"
#endif

#ifdef GRPC_POSIX_SOCKET
#define GRPC_POSIX_SOCKET_ARES_EV_DRIVER 1
#define GRPC_POSIX_SOCKET_EV 1
#define GRPC_POSIX_SOCKET_EV_POLL 1
#define GRPC_POSIX_SOCKET_EV_EPOLL1 1
#define GRPC_POSIX_SOCKET_IF_NAMETOINDEX 1
#define GRPC_POSIX_SOCKET_IOMGR 1
#define GRPC_POSIX_SOCKET_RESOLVE_ADDRESS 1
#define GRPC_POSIX_SOCKET_SOCKADDR 1
#define GRPC_POSIX_SOCKET_SOCKET_FACTORY 1
#define GRPC_POSIX_SOCKET_TCP 1
#define GRPC_POSIX_SOCKET_TCP_CLIENT 1
#define GRPC_POSIX_SOCKET_TCP_SERVER 1
#define GRPC_POSIX_SOCKET_TCP_SERVER_UTILS_COMMON 1
#define GRPC_POSIX_SOCKET_UDP_SERVER 1
#define GRPC_POSIX_SOCKET_UTILS_COMMON 1
#endif

#if defined(GRPC_POSIX_HOST_NAME_MAX) && defined(GRPC_POSIX_SYSCONF)
#error "Cannot define both GRPC_POSIX_HOST_NAME_MAX and GRPC_POSIX_SYSCONF"
#endif
#if !defined(GRPC_POSIX_HOST_NAME_MAX) && !defined(GRPC_POSIX_SYSCONF)
#define GRPC_GETHOSTNAME_FALLBACK 1
#endif

#endif

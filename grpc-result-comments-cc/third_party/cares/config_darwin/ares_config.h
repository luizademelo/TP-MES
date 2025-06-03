Here's the commented version of the code snippet. I've added explanations for each section to clarify the purpose of these macro definitions and undefinitions:

```c++
/* Undefining previously defined macros to ensure clean slate configuration */

/* Disable Apple Universal Build flag */
#undef AC_APPLE_UNIVERSAL_BUILD

/* Disable big-endian architecture flag */
#undef ARES_BIG_ENDIAN

/* Indicate we're not building libcurl */
#undef BUILDING_LIBCURL

/* Disable c-ares static symbol exposure */
#undef CARES_EXPOSE_STATICS

/* Disable c-ares symbol hiding */
#undef CARES_SYMBOL_HIDING

/* Disable c-ares extern symbol scope */
#undef CARES_SYMBOL_SCOPE_EXTERN

/* Undefine legacy INET configuration path */
#undef ETC_INET


/* Network and system configuration macros */

/* Type definition for gethostname() length parameter */
#define GETHOSTNAME_TYPE_ARG2 size_t

/* Qualifier for getnameinfo() first argument */
#define GETNAMEINFO_QUAL_ARG1

/* Type definitions for getnameinfo() arguments */
#define GETNAMEINFO_TYPE_ARG1 struct sockaddr *
#define GETNAMEINFO_TYPE_ARG2 socklen_t
#define GETNAMEINFO_TYPE_ARG46 socklen_t
#define GETNAMEINFO_TYPE_ARG7 int

/* Argument definition for getservbyport_r() */
#define GETSERVBYPORT_R_ARGS


/* Feature detection macros - indicate available system capabilities */

/* IPv6 support */
#define HAVE_AF_INET6

/* Header file availability */
#define HAVE_ARPA_INET_H
#define HAVE_ARPA_NAMESER_COMPAT_H
#define HAVE_ARPA_NAMESER_H
#define HAVE_ASSERT_H
#define HAVE_DLFCN_H
#define HAVE_ERRNO_H
#define HAVE_FCNTL_H
#define HAVE_INTTYPES_H
#define HAVE_MEMORY_H
#define HAVE_NETDB_H
#define HAVE_NETINET_IN_H
#define HAVE_NETINET_TCP_H
#define HAVE_NET_IF_H
#define HAVE_SIGNAL_H
#define HAVE_STDBOOL_H
#define HAVE_STDINT_H
#define HAVE_STDLIB_H
#define HAVE_STRINGS_H
#define HAVE_STRING_H
#define HAVE_SYS_IOCTL_H
#define HAVE_SYS_PARAM_H
#define HAVE_SYS_SELECT_H
#define HAVE_SYS_SOCKET_H
#define HAVE_SYS_STAT_H
#define HAVE_SYS_TIME_H
#define HAVE_SYS_TYPES_H
#define HAVE_SYS_UIO_H
#define HAVE_TIME_H
#define HAVE_UNISTD_H

/* Type availability */
#define HAVE_BOOL_T
#define HAVE_LL
#define HAVE_LONGLONG
#define HAVE_SIG_ATOMIC_T

/* IMPORTANT: gRPC MANUAL EDIT HERE!
 * defining HAVE_CLOCK_GETTIME_MONOTONIC breaks the MacOS build on gRPC CI */

/* System call availability */
#define HAVE_CONNECT
#define HAVE_FCNTL
#define HAVE_FCNTL_O_NONBLOCK
#define HAVE_FREEADDRINFO
#define HAVE_GETADDRINFO
#define HAVE_GETADDRINFO_THREADSAFE
#define HAVE_GETENV
#define HAVE_GETHOSTBYADDR
#define HAVE_GETHOSTBYNAME
#define HAVE_GETHOSTNAME
#define HAVE_GETNAMEINFO
#define HAVE_GETTIMEOFDAY
#define HAVE_IF_INDEXTONAME
#define HAVE_INET_NET_PTON
#define HAVE_INET_NTOP
#define HAVE_INET_PTON
#define HAVE_IOCTL
#define HAVE_IOCTL_FIONBIO
#define HAVE_IOCTL_SIOCGIFADDR
#define HAVE_LIBRESOLV
#define HAVE_PF_INET6
#define HAVE_RECV
#define HAVE_RECVFROM
#define HAVE_SEND
#define HAVE_SETSOCKOPT
#define HAVE_WRITEV

/* Structure availability */
#define HAVE_STRUCT_ADDRINFO
#define HAVE_STRUCT_IN6_ADDR
#define HAVE_STRUCT_SOCKADDR_IN6
#define HAVE_STRUCT_SOCKADDR_STORAGE
#define HAVE_STRUCT_TIMEVAL

/* String function availability */
#define HAVE_STRCASECMP
#define HAVE_STRDUP
#define HAVE_STRNCASECMP


/* Socket operation type definitions */

/* recvfrom() argument types */
#define RECVFROM_QUAL_ARG5
#define RECVFROM_TYPE_ARG1 int
#define RECVFROM_TYPE_ARG2 void *
#define RECVFROM_TYPE_ARG2_IS_VOID 0
#define RECVFROM_TYPE_ARG3 size_t
#define RECVFROM_TYPE_ARG4 int
#define RECVFROM_TYPE_ARG5 struct sockaddr *
#define RECVFROM_TYPE_ARG5_IS_VOID 0
#define RECVFROM_TYPE_ARG6 socklen_t *
#define RECVFROM_TYPE_ARG6_IS_VOID 0
#define RECVFROM_TYPE_RETV ssize_t

/* recv() argument types */
#define RECV_TYPE_ARG1 int
#define RECV_TYPE_ARG2 void *
#define RECV_TYPE_ARG3 size_t
#define RECV_TYPE_ARG4 int
#define RECV_TYPE_RETV ssize_t

/* send() argument types */
#define SEND_QUAL_ARG2
#define SEND_TYPE_ARG1 int
#define SEND_TYPE_ARG2 void *
#define SEND_TYPE_ARG3 size_t
#define SEND_TYPE_ARG4 int
#define SEND_TYPE_RETV ssize_t

/* Return type for signal handlers */
#define RETSIGTYPE

/* Time handling configuration */
#define TIME_WITH_SYS_TIME


/* Disabling unwanted features */

/* Disable blocking sockets */
#undef USE_BLOCKING_SOCKETS

/* Disable Windows lean headers */
#undef WIN32_LEAN_AND_MEAN

/* Undefine legacy in_addr_t type */
#undef in_addr_t
```

The comments explain:
1. The purpose of each macro group (undefinitions, type definitions, feature detection)
2. Important configuration notes (like the gRPC manual edit warning)
3. The significance of specific macros for network operations
4. System capability indicators
5. Type definitions for socket operations

The comments are structured to help maintainers understand:
- What features are being enabled/disabled
- Why certain configurations are present
- How the system is being configured for network operations
- Important considerations for specific platforms
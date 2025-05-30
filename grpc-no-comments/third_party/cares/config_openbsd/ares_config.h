
#define CARES_SYMBOL_HIDING 1

#define CARES_SYMBOL_SCOPE_EXTERN __attribute__ ((__visibility__ ("default")))

#define CARES_TYPEOF_ARES_SSIZE_T ssize_t

#define GETHOSTNAME_TYPE_ARG2 size_t

#define GETNAMEINFO_QUAL_ARG1 const

#define GETNAMEINFO_TYPE_ARG1 struct sockaddr *

#define GETNAMEINFO_TYPE_ARG2 socklen_t

#define GETNAMEINFO_TYPE_ARG46 size_t

#define GETNAMEINFO_TYPE_ARG7 int

#define GETSERVBYPORT_R_ARGS 4

#define GETSERVBYPORT_R_BUFSIZE sizeof(struct servent_data)

#define HAVE_AF_INET6 1

#define HAVE_ARPA_INET_H 1

#define HAVE_ARPA_NAMESER_H 1

#define HAVE_ASSERT_H 1

#define HAVE_BOOL_T 1

#define HAVE_CLOCK_GETTIME_MONOTONIC 1

#define HAVE_CONNECT 1

#define HAVE_DLFCN_H 1

#define HAVE_ERRNO_H 1

#define HAVE_FCNTL 1

#define HAVE_FCNTL_H 1

#define HAVE_FCNTL_O_NONBLOCK 1

#define HAVE_FREEADDRINFO 1

#define HAVE_GETADDRINFO 1

#define HAVE_GETENV 1

#define HAVE_GETHOSTBYADDR 1

#define HAVE_GETHOSTBYNAME 1

#define HAVE_GETHOSTNAME 1

#define HAVE_GETNAMEINFO 1

#define HAVE_GETSERVBYPORT_R 1

#define HAVE_GETTIMEOFDAY 1

#define HAVE_IF_INDEXTONAME 1

#define HAVE_INET_NTOP 1

#define HAVE_INET_PTON 1

#define HAVE_INTTYPES_H 1

#define HAVE_IOCTL 1

#define HAVE_IOCTL_FIONBIO 1

#define HAVE_IOCTL_SIOCGIFADDR 1

#define HAVE_LIMITS_H 1

#define HAVE_LL 1

#define HAVE_LONGLONG 1

#define HAVE_MEMORY_H 1

#define HAVE_MSG_NOSIGNAL 1

#define HAVE_NETDB_H 1

#define HAVE_NETINET_IN_H 1

#define HAVE_NETINET_TCP_H 1

#define HAVE_NET_IF_H 1

#define HAVE_PF_INET6 1

#define HAVE_RECV 1

#define HAVE_RECVFROM 1

#define HAVE_SEND 1

#define HAVE_SETSOCKOPT 1

#define HAVE_SIGNAL_H 1

#define HAVE_SIG_ATOMIC_T 1

#define HAVE_SOCKADDR_IN6_SIN6_SCOPE_ID 1

#define HAVE_SOCKET 1

#define HAVE_STDBOOL_H 1

#define HAVE_STDINT_H 1

#define HAVE_STDLIB_H 1

#define HAVE_STRCASECMP 1

#define HAVE_STRDUP 1

#define HAVE_STRINGS_H 1

#define HAVE_STRING_H 1

#define HAVE_STRNCASECMP 1

#define HAVE_STRUCT_ADDRINFO 1

#define HAVE_STRUCT_IN6_ADDR 1

#define HAVE_STRUCT_SOCKADDR_IN6 1

#define HAVE_STRUCT_SOCKADDR_STORAGE 1

#define HAVE_STRUCT_TIMEVAL 1

#define HAVE_SYS_IOCTL_H 1

#define HAVE_SYS_PARAM_H 1

#define HAVE_SYS_SELECT_H 1

#define HAVE_SYS_SOCKET_H 1

#define HAVE_SYS_STAT_H 1

#define HAVE_SYS_TIME_H 1

#define HAVE_SYS_TYPES_H 1

#define HAVE_SYS_UIO_H 1

#define HAVE_TIME_H 1

#define HAVE_UNISTD_H 1

#define HAVE_WRITEV 1

#define LT_OBJDIR ".libs/"

#define OS "x86_64-unknown-openbsd6.2"

#define PACKAGE "c-ares"

#define PACKAGE_BUGREPORT "c-ares mailing list: http://cool.haxx.se/mailman/listinfo/c-ares"

#define PACKAGE_NAME "c-ares"

#define PACKAGE_STRING "c-ares 1.13.0"

#define PACKAGE_TARNAME "c-ares"

#define PACKAGE_URL ""

#define PACKAGE_VERSION "1.13.0"

#define RANDOM_FILE "/dev/urandom"

#define RECVFROM_QUAL_ARG5

#define RECVFROM_TYPE_ARG1 int

#define RECVFROM_TYPE_ARG2 void

#define RECVFROM_TYPE_ARG2_IS_VOID 1

#define RECVFROM_TYPE_ARG3 size_t

#define RECVFROM_TYPE_ARG4 int

#define RECVFROM_TYPE_ARG5 struct sockaddr

#define RECVFROM_TYPE_ARG6 socklen_t

#define RECVFROM_TYPE_RETV ssize_t

#define RECV_TYPE_ARG1 int

#define RECV_TYPE_ARG2 void *

#define RECV_TYPE_ARG3 size_t

#define RECV_TYPE_ARG4 int

#define RECV_TYPE_RETV ssize_t

#define RETSIGTYPE void

#define SEND_QUAL_ARG2 const

#define SEND_TYPE_ARG1 int

#define SEND_TYPE_ARG2 void *

#define SEND_TYPE_ARG3 size_t

#define SEND_TYPE_ARG4 int

#define SEND_TYPE_RETV ssize_t

#define STDC_HEADERS 1

#define TIME_WITH_SYS_TIME 1

#define VERSION "1.13.0"

#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN

# endif
#endif

#ifndef _ALL_SOURCE

#endif

#ifndef _DARWIN_USE_64_BIT_INODE
# define _DARWIN_USE_64_BIT_INODE 1
#endif

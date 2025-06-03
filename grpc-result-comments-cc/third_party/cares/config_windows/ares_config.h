Here's the commented version of the code snippet. I've added explanations for each section to clarify the purpose of these macro definitions and undefinitions:

```c++
/* Undefining previously defined macros to prevent potential conflicts */
#undef AC_APPLE_UNIVERSAL_BUILD
#undef ARES_BIG_ENDIAN
#undef BUILDING_LIBCURL
#undef CARES_EXPOSE_STATICS
#undef CARES_SYMBOL_HIDING
#undef CARES_SYMBOL_SCOPE_EXTERN
#undef ETC_INET

/* Network-related type definitions for compatibility */
#define GETHOSTNAME_TYPE_ARG2 int           // Type for hostname length argument in gethostname()
#define GETNAMEINFO_QUAL_ARG1               // Qualifier for getnameinfo() first argument
#define GETNAMEINFO_TYPE_ARG1 struct sockaddr *  // Type for getnameinfo() address argument
#define GETNAMEINFO_TYPE_ARG2 socklen_t     // Type for getnameinfo() address length argument
#define GETNAMEINFO_TYPE_ARG46 socklen_t    // Type for getnameinfo() buffer length arguments
#define GETNAMEINFO_TYPE_ARG7 int           // Type for getnameinfo() flags argument

/* Socket function argument definitions */
#define GETSERVBYPORT_R_ARGS                // Arguments for getservbyport_r()

/* Feature detection macros - indicate available system features */
#define HAVE_AF_INET6                       // IPv6 address family support
#define HAVE_ASSERT_H                       // assert.h header available
#define HAVE_BOOL_T                         // bool type available
#define HAVE_CLOSESOCKET                    // closesocket() function available
#define HAVE_CONNECT                        // connect() function available
#define HAVE_ERRNO_H                        // errno.h header available
#define HAVE_FCNTL_H                        // fcntl.h header available
#define HAVE_FREEADDRINFO                   // freeaddrinfo() function available
#define HAVE_GETADDRINFO                    // getaddrinfo() function available
#define HAVE_GETADDRINFO_THREADSAFE         // Thread-safe getaddrinfo() available
#define HAVE_GETENV                         // getenv() function available
#define HAVE_GETHOSTBYADDR                  // gethostbyaddr() function available
#define HAVE_GETHOSTBYNAME                  // gethostbyname() function available
#define HAVE_GETHOSTNAME                    // gethostname() function available
#define HAVE_GETNAMEINFO                    // getnameinfo() function available
#define HAVE_INTTYPES_H                     // inttypes.h header available
#define HAVE_IOCTLSOCKET                    // ioctlsocket() function available
#define HAVE_IOCTLSOCKET_FIONBIO            // FIONBIO flag for ioctlsocket() available
#define HAVE_LIMITS_H                       // limits.h header available
#define HAVE_LL                             // long long type available
#define HAVE_LONGLONG                       // long long type available
#define HAVE_MALLOC_H                       // malloc.h header available
#define HAVE_MEMORY_H                       // memory.h header available
#define HAVE_PF_INET6                       // IPv6 protocol family support
#define HAVE_RECV                           // recv() function available
#define HAVE_RECVFROM                       // recvfrom() function available
#define HAVE_SEND                           // send() function available
#define HAVE_SETSOCKOPT                     // setsockopt() function available
#define HAVE_SIGNAL_H                       // signal.h header available
#define HAVE_SIG_ATOMIC_T                   // sig_atomic_t type available
#define HAVE_SOCKADDR_IN6_SIN6_SCOPE_ID     // sin6_scope_id in sockaddr_in6 available
#define HAVE_SOCKET                         // socket() function available
#define HAVE_STDBOOL_H                      // stdbool.h header available
#define HAVE_STDINT_H                       // stdint.h header available
#define HAVE_STDLIB_H                       // stdlib.h header available
#define HAVE_STRCMPI                        // strcmpi() function available
#define HAVE_STRDUP                         // strdup() function available
#define HAVE_STRICMP                        // stricmp() function available
#define HAVE_STRING_H                       // string.h header available
#define HAVE_STRNICMP                       // strnicmp() function available

/* Structure availability macros */
#define HAVE_STRUCT_ADDRINFO                // struct addrinfo available
#define HAVE_STRUCT_IN6_ADDR                // struct in6_addr available
#define HAVE_STRUCT_SOCKADDR_IN6            // struct sockaddr_in6 available
#define HAVE_STRUCT_SOCKADDR_STORAGE        // struct sockaddr_storage available
#define HAVE_STRUCT_TIMEVAL                 // struct timeval available

/* Additional system headers availability */
#define HAVE_SYS_STAT_H                     // sys/stat.h header available
#define HAVE_SYS_TYPES_H                    // sys/types.h header available
#define HAVE_TIME_H                          // time.h header available

/* Windows-specific headers and features */
#define HAVE_WINDOWS_H                      // windows.h header available
#define HAVE_WINSOCK2_H                     // winsock2.h header available
#define HAVE_WINSOCK_H                      // winsock.h header available
#define HAVE_WS2TCPIP_H                     // ws2tcpip.h header available

/* Socket function parameter types */
#define RECVFROM_QUAL_ARG5                  // Qualifier for recvfrom() 5th argument
#define RECVFROM_TYPE_ARG1 SOCKET           // Type for recvfrom() socket argument
#define RECVFROM_TYPE_ARG2 void *           // Type for recvfrom() buffer argument
#define RECVFROM_TYPE_ARG2_IS_VOID 0        // Indicates if recvfrom() buffer arg is void
#define RECVFROM_TYPE_ARG3 int              // Type for recvfrom() buffer length argument
#define RECVFROM_TYPE_ARG4 int              // Type for recvfrom() flags argument
#define RECVFROM_TYPE_ARG5 struct sockaddr * // Type for recvfrom() source address argument
#define RECVFROM_TYPE_ARG5_IS_VOID 0        // Indicates if recvfrom() address arg is void
#define RECVFROM_TYPE_ARG6 socklen_t *      // Type for recvfrom() address length argument
#define RECVFROM_TYPE_ARG6_IS_VOID 0        // Indicates if recvfrom() addrlen arg is void
#define RECVFROM_TYPE_RETV int              // Return type of recvfrom()

#define RECV_TYPE_ARG1 SOCKET               // Type for recv() socket argument
#define RECV_TYPE_ARG2 void *               // Type for recv() buffer argument
#define RECV_TYPE_ARG3 int                  // Type for recv() buffer length argument
#define RECV_TYPE_ARG4 int                  // Type for recv() flags argument
#define RECV_TYPE_RETV int                  // Return type of recv()

#define RETSIGTYPE                          // Return type of signal handlers

#define SEND_QUAL_ARG2                      // Qualifier for send() 2nd argument
#define SEND_TYPE_ARG1 SOCKET               // Type for send() socket argument
#define SEND_TYPE_ARG2 void *               // Type for send() buffer argument
#define SEND_TYPE_ARG3 int                  // Type for send() buffer length argument
#define SEND_TYPE_ARG4 int                  // Type for send() flags argument
#define SEND_TYPE_RETV int                  // Return type of send()

/* Undefining Windows-specific macros that might affect compilation */
#undef USE_BLOCKING_SOCKETS
#undef WIN32_LEAN_AND_MEAN

/* Undefining potentially conflicting type definition */
#undef in_addr_t
```

These comments explain:
1. The purpose of each macro definition/undefinition
2. The significance of feature detection macros (HAVE_*)
3. The type definitions for network-related functions
4. The organization into logical sections (undefines, feature detection, type definitions, etc.)
5. Platform-specific considerations (especially Windows)
6. Structure availability indicators

The comments make it clear that this appears to be part of a configuration header for a networking library, likely dealing with cross-platform compatibility.
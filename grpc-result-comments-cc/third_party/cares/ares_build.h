Here's the commented version of the code:

```c++
#ifndef __CARES_BUILD_H
#define __CARES_BUILD_H

/* Copyright (C) 2009 - 2013 by Daniel Stenberg et al
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of M.I.T. not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  M.I.T. makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 */

// Prevent multiple definitions of CARES_TYPEOF_ARES_SOCKLEN_T
#ifdef CARES_TYPEOF_ARES_SOCKLEN_T
#  error "CARES_TYPEOF_ARES_SOCKLEN_T shall not be defined except in ares_build.h"
   Error Compilation_aborted_CARES_TYPEOF_ARES_SOCKLEN_T_already_defined
#endif

// Platform-specific definitions for socket length type (ares_socklen_t)
// Most platforms use 'int' by default
#if defined(__DJGPP__) || defined(__GO32__)
#  define CARES_TYPEOF_ARES_SOCKLEN_T int

#elif defined(__SALFORDC__)
#  define CARES_TYPEOF_ARES_SOCKLEN_T int

#elif defined(__BORLANDC__)
#  define CARES_TYPEOF_ARES_SOCKLEN_T int

#elif defined(__TURBOC__)
#  define CARES_TYPEOF_ARES_SOCKLEN_T int

#elif defined(__WATCOMC__)
#  define CARES_TYPEOF_ARES_SOCKLEN_T int

#elif defined(__POCC__)
#  define CARES_TYPEOF_ARES_SOCKLEN_T int

#elif defined(__LCC__)
#  define CARES_TYPEOF_ARES_SOCKLEN_T int

#elif defined(__SYMBIAN32__)
#  define CARES_TYPEOF_ARES_SOCKLEN_T unsigned int  // Symbian uses unsigned int

#elif defined(__MWERKS__)
#  define CARES_TYPEOF_ARES_SOCKLEN_T int

#elif defined(_WIN32_WCE)
#  define CARES_TYPEOF_ARES_SOCKLEN_T int

#elif defined(__MINGW32__)
#  define CARES_TYPEOF_ARES_SOCKLEN_T int

#elif defined(__VMS)
#  define CARES_TYPEOF_ARES_SOCKLEN_T unsigned int  // VMS uses unsigned int

// Special cases requiring socklen_t and additional headers
#elif defined(__OS400__)
#  if defined(__ILEC400__)
#    define CARES_TYPEOF_ARES_SOCKLEN_T socklen_t
#    define CARES_PULL_SYS_TYPES_H      1  // Flag to include sys/types.h
#    define CARES_PULL_SYS_SOCKET_H     1  // Flag to include sys/socket.h
#  endif

#elif defined(__MVS__)
#  if defined(__IBMC__) || defined(__IBMCPP__)
#    define CARES_TYPEOF_ARES_SOCKLEN_T socklen_t
#    define CARES_PULL_SYS_TYPES_H      1
#    define CARES_PULL_SYS_SOCKET_H     1
#  endif

#elif defined(__370__)
#  if defined(__IBMC__) || defined(__IBMCPP__)
#    define CARES_TYPEOF_ARES_SOCKLEN_T socklen_t
#    define CARES_PULL_SYS_TYPES_H      1
#    define CARES_PULL_SYS_SOCKET_H     1
#  endif

#elif defined(TPF)
#  define CARES_TYPEOF_ARES_SOCKLEN_T int

#elif defined(_MSC_VER)
#  define CARES_TYPEOF_ARES_SOCKLEN_T int

#elif defined(__GNUC__)
#  define CARES_TYPEOF_ARES_SOCKLEN_T socklen_t  // GCC typically uses socklen_t
#  define CARES_PULL_SYS_TYPES_H      1
#  define CARES_PULL_SYS_SOCKET_H     1

#else
#  error "Unknown non-configure build target!"
   Error Compilation_aborted_Unknown_non_configure_build_target
#endif

// Include required headers based on platform requirements
#ifdef CARES_PULL_SYS_TYPES_H
#  include <sys/types.h>
#endif

#ifdef CARES_PULL_SYS_SOCKET_H
#  include <sys/socket.h>
#endif

// Define the actual socket length type if it was determined
#ifdef CARES_TYPEOF_ARES_SOCKLEN_T
  typedef CARES_TYPEOF_ARES_SOCKLEN_T ares_socklen_t;
#endif

// Platform-specific definitions for ssize_t equivalent (ares_ssize_t)
#ifdef _WIN32
#  ifdef _WIN64
#    ifdef __MINGW32__
#      include <_mingw.h>  // Required for MinGW64 definitions
#    endif
#    define CARES_TYPEOF_ARES_SSIZE_T __int64  // 64-bit Windows uses __int64
#  else
#    define CARES_TYPEOF_ARES_SSIZE_T long     // 32-bit Windows uses long
#  endif
#else
#  define CARES_TYPEOF_ARES_SSIZE_T ssize_t   // Non-Windows platforms use ssize_t
#endif

// Define the actual ssize type
typedef CARES_TYPEOF_ARES_SSIZE_T ares_ssize_t;

/* IMPORTANT: gRPC MANUAL EDIT HERE!
 * Undefine UNICODE, as c-ares does not use the ANSI version of functions
 * explicitly. This ensures we don't get UNICODE versions of Windows API calls
 * when c-ares isn't prepared for them. */
#ifdef UNICODE
#  undef UNICODE
#endif

#ifdef _UNICODE
#  undef _UNICODE
#endif

#endif /* __CARES_BUILD_H */
```

The comments explain:
1. The purpose of the header guard
2. The copyright and license information
3. The platform-specific logic for determining socket length types
4. The special cases requiring additional headers
5. The Windows-specific handling of ssize_t equivalents
6. The gRPC-specific modifications for UNICODE handling
7. The overall structure and purpose of each section

The comments are designed to help future maintainers understand:
- Why certain platforms have specific definitions
- What each section of the code is responsible for
- The relationships between different definitions
- Any special considerations or requirements
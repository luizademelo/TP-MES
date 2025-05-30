
/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef GRPC_SUPPORT_PORT_PLATFORM_H
#define GRPC_SUPPORT_PORT_PLATFORM_H

#if __cplusplus >= 201402L
#define GRPC_DEPRECATED(reason) [[deprecated(reason)]]
#else
#define GRPC_DEPRECATED(reason)
#endif

#ifndef GPR_DISABLE_ABSEIL_SYNC

#ifndef GPR_ABSEIL_SYNC
#define GPR_ABSEIL_SYNC 1
#endif
#endif

#if defined(_WIN64) || defined(WIN64) || defined(_WIN32) || defined(WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define GRPC_WIN32_LEAN_AND_MEAN_WAS_NOT_DEFINED
#define WIN32_LEAN_AND_MEAN
#endif

// Note: GRPC_DLL_EXPORTS is set in CMakeLists.txt when building shared

#if !defined(GRPC_DLL)
#if defined(GRPC_DLL_EXPORTS)
#define GRPC_DLL __declspec(dllexport)
#elif defined(GRPC_DLL_IMPORTS)
#define GRPC_DLL __declspec(dllimport)
#else
#define GRPC_DLL
#endif
#endif

#if !defined(GRPCXX_DLL)
#if defined(GRPCXX_DLL_EXPORTS)
#define GRPCXX_DLL __declspec(dllexport)
#elif defined(GRPCXX_DLL_IMPORTS)
#define GRPCXX_DLL __declspec(dllimport)
#else
#define GRPCXX_DLL
#endif
#endif

#if !defined(GPR_DLL)
#if defined(GPR_DLL_EXPORTS)
#define GPR_DLL __declspec(dllexport)
#elif defined(GPR_DLL_IMPORTS)
#define GPR_DLL __declspec(dllimport)
#else
#define GPR_DLL
#endif
#endif

#ifndef NOMINMAX
#define GRPC_NOMINMX_WAS_NOT_DEFINED
#define NOMINMAX
#endif

#include <windows.h>

#ifndef _WIN32_WINNT
#error \
    "Please compile grpc with _WIN32_WINNT of at least 0x600 (aka Windows Vista)"
#else
#if (_WIN32_WINNT < 0x0600)
#error \
    "Please compile grpc with _WIN32_WINNT of at least 0x600 (aka Windows Vista)"
#endif

#ifdef GRPC_WIN32_LEAN_AND_MEAN_WAS_NOT_DEFINED
#undef GRPC_WIN32_LEAN_AND_MEAN_WAS_NOT_DEFINED
#undef WIN32_LEAN_AND_MEAN
#endif

#ifdef GRPC_NOMINMAX_WAS_NOT_DEFINED
#undef GRPC_NOMINMAX_WAS_NOT_DEFINED
#undef NOMINMAX
#endif
#endif

#else
#define GRPC_DLL
#define GRPCXX_DLL
#define GPR_DLL
#endif

#if !defined(GPR_NO_AUTODETECT_PLATFORM)
#if defined(_WIN64) || defined(WIN64) || defined(_WIN32) || defined(WIN32)
#if defined(_WIN64) || defined(WIN64)
#define GPR_ARCH_64 1
#else
#define GPR_ARCH_32 1
#endif
#define GPR_PLATFORM_STRING "windows"
#define GPR_WINDOWS 1
#define GPR_WINDOWS_SUBPROCESS 1
#define GPR_WINDOWS_ENV
#ifdef __MSYS__
#define GPR_GETPID_IN_UNISTD_H 1
#define GPR_MSYS_TMPFILE
#define GPR_POSIX_LOG
#define GPR_POSIX_STRING
#define GPR_POSIX_TIME
#else
#define GPR_GETPID_IN_PROCESS_H 1
#define GPR_WINDOWS_TMPFILE
#define GPR_WINDOWS_LOG
#define GPR_WINDOWS_CRASH_HANDLER 1
#define GPR_WINDOWS_STAT
#define GPR_WINDOWS_STRING
#define GPR_WINDOWS_TIME
#endif
#ifdef __GNUC__
#define GPR_GCC_ATOMIC 1
#else
#define GPR_WINDOWS_ATOMIC 1
#endif
#elif defined(ANDROID) || defined(__ANDROID__)
#define GPR_PLATFORM_STRING "android"
#define GPR_ANDROID 1
#ifndef __ANDROID_API__
#error "__ANDROID_API__ must be defined for Android builds."
#endif
#if __ANDROID_API__ < 21
#error "Requires Android API v21 and above"
#endif

#define GRPC_ARES 0
#ifdef _LP64
#define GPR_ARCH_64 1
#else
#define GPR_ARCH_32 1
#endif
#define GPR_CPU_POSIX 1
#define GPR_GCC_SYNC 1
#define GPR_POSIX_ENV 1
#define GPR_POSIX_TMPFILE 1
#define GPR_POSIX_STAT 1
#define GPR_ANDROID_LOG 1
#define GPR_POSIX_STRING 1
#define GPR_POSIX_SUBPROCESS 1
#define GPR_POSIX_SYNC 1
#define GPR_POSIX_TIME 1
#define GPR_HAS_PTHREAD_H 1
#define GPR_GETPID_IN_UNISTD_H 1
#define GPR_SUPPORT_CHANNELS_FROM_FD 1
#if defined(__has_include)
#if __has_include(<android/ndk-version.h>)
#include <android/ndk-version.h>
#endif
#endif
#include <linux/version.h>
#elif defined(__linux__)
#define GPR_PLATFORM_STRING "linux"
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <features.h>
#define GPR_CPU_LINUX 1
#define GPR_GCC_ATOMIC 1
#define GPR_LINUX 1
#define GPR_LINUX_LOG
#define GPR_SUPPORT_CHANNELS_FROM_FD 1
#define GPR_LINUX_ENV 1
#define GPR_POSIX_TMPFILE 1
#define GPR_POSIX_STAT 1
#define GPR_POSIX_STRING 1
#define GPR_POSIX_SUBPROCESS 1
#define GPR_POSIX_SYNC 1
#define GPR_POSIX_TIME 1
#define GPR_HAS_PTHREAD_H 1
#define GPR_GETPID_IN_UNISTD_H 1
#ifdef _LP64
#define GPR_ARCH_64 1
#else
#define GPR_ARCH_32 1
#endif
#ifdef __GLIBC__
#define GPR_POSIX_CRASH_HANDLER 1
#ifdef __GLIBC_PREREQ
#if __GLIBC_PREREQ(2, 12)
#define GPR_LINUX_PTHREAD_NAME 1
#endif
#else

#define GPR_LINUX_PTHREAD_NAME 1
#endif
#include <linux/version.h>
#else
#define GPR_MUSL_LIBC_COMPAT 1
#endif
#elif defined(__ASYLO__)
#define GPR_ARCH_64 1
#define GPR_CPU_POSIX 1
#define GPR_PLATFORM_STRING "asylo"
#define GPR_GCC_SYNC 1
#define GPR_POSIX_STAT 1
#define GPR_POSIX_SYNC 1
#define GPR_POSIX_STRING 1
#define GPR_POSIX_LOG 1
#define GPR_POSIX_TIME 1
#define GPR_POSIX_ENV 1
#define GPR_ASYLO 1
#define GRPC_POSIX_SOCKET 1
#define GRPC_POSIX_SOCKETADDR
#define GRPC_POSIX_SOCKETUTILS 1
#define GRPC_TIMER_USE_GENERIC 1
#define GRPC_POSIX_NO_SPECIAL_WAKEUP_FD 1
#define GRPC_POSIX_WAKEUP_FD 1
#define GRPC_HAVE_MSG_NOSIGNAL 1
#define GRPC_HAVE_UNIX_SOCKET 1
#define GRPC_ARES 0
#define GPR_NO_AUTODETECT_PLATFORM 1
#elif defined(__APPLE__)
#include <Availability.h>
#include <TargetConditionals.h>
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#if TARGET_OS_IPHONE
#define GPR_PLATFORM_STRING "ios"
#define GPR_CPU_IPHONE 1
#define GRPC_CFSTREAM 1
#ifndef GRPC_IOS_EVENT_ENGINE_CLIENT
#define GRPC_IOS_EVENT_ENGINE_CLIENT 1
#endif

#define GRPC_ARES 0
#else
#define GPR_PLATFORM_STRING "osx"
#define GPR_CPU_POSIX 1
#define GPR_POSIX_CRASH_HANDLER 1
#endif
#define GPR_APPLE 1
#define GPR_GCC_ATOMIC 1
#define GPR_POSIX_LOG 1
#define GPR_POSIX_ENV 1
#define GPR_POSIX_TMPFILE 1
#define GPR_POSIX_STAT 1
#define GPR_POSIX_STRING 1
#define GPR_POSIX_SUBPROCESS 1
#define GPR_POSIX_SYNC 1
#define GPR_POSIX_TIME 1
#define GPR_HAS_PTHREAD_H 1
#define GPR_GETPID_IN_UNISTD_H 1
#ifndef GRPC_CFSTREAM
#define GPR_SUPPORT_CHANNELS_FROM_FD 1
#endif
#ifdef _LP64
#define GPR_ARCH_64 1
#else
#define GPR_ARCH_32 1
#endif
#elif defined(__FreeBSD__)
#define GPR_PLATFORM_STRING "freebsd"
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#define GPR_FREEBSD 1
#define GPR_CPU_POSIX 1
#define GPR_GCC_ATOMIC 1
#define GPR_POSIX_LOG 1
#define GPR_POSIX_ENV 1
#define GPR_POSIX_TMPFILE 1
#define GPR_POSIX_STAT 1
#define GPR_POSIX_STRING 1
#define GPR_POSIX_SUBPROCESS 1
#define GPR_POSIX_SYNC 1
#define GPR_POSIX_TIME 1
#define GPR_HAS_PTHREAD_H 1
#define GPR_GETPID_IN_UNISTD_H 1
#define GPR_SUPPORT_CHANNELS_FROM_FD 1
#ifdef _LP64
#define GPR_ARCH_64 1
#else
#define GPR_ARCH_32 1
#endif
#elif defined(__OpenBSD__)
#define GPR_PLATFORM_STRING "openbsd"
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#define GPR_OPENBSD 1
#define GPR_CPU_POSIX 1
#define GPR_GCC_ATOMIC 1
#define GPR_POSIX_LOG 1
#define GPR_POSIX_ENV 1
#define GPR_POSIX_TMPFILE 1
#define GPR_POSIX_STAT 1
#define GPR_POSIX_STRING 1
#define GPR_POSIX_SUBPROCESS 1
#define GPR_POSIX_SYNC 1
#define GPR_POSIX_TIME 1
#define GPR_HAS_PTHREAD_H 1
#define GPR_GETPID_IN_UNISTD_H 1
#define GPR_SUPPORT_CHANNELS_FROM_FD 1
#ifdef _LP64
#define GPR_ARCH_64 1
#else
#define GPR_ARCH_32 1
#endif
#elif defined(__sun) && defined(__SVR4)
#define GPR_PLATFORM_STRING "solaris"
#define GPR_SOLARIS 1
#define GPR_CPU_POSIX 1
#define GPR_GCC_ATOMIC 1
#define GPR_POSIX_LOG 1
#define GPR_POSIX_ENV 1
#define GPR_POSIX_TMPFILE 1
#define GPR_POSIX_STAT 1
#define GPR_POSIX_STRING 1
#define GPR_POSIX_SUBPROCESS 1
#define GPR_POSIX_SYNC 1
#define GPR_POSIX_TIME 1
#define GPR_HAS_PTHREAD_H 1
#define GPR_GETPID_IN_UNISTD_H 1
#ifdef _LP64
#define GPR_ARCH_64 1
#else
#define GPR_ARCH_32 1
#endif
#elif defined(_AIX)
#define GPR_PLATFORM_STRING "aix"
#ifndef _ALL_SOURCE
#define _ALL_SOURCE
#endif
#define GPR_AIX 1
#define GPR_CPU_POSIX 1
#define GPR_GCC_ATOMIC 1
#define GPR_POSIX_LOG 1
#define GPR_POSIX_ENV 1
#define GPR_POSIX_TMPFILE 1
#define GPR_POSIX_STAT 1
#define GPR_POSIX_STRING 1
#define GPR_POSIX_SUBPROCESS 1
#define GPR_POSIX_SYNC 1
#define GPR_POSIX_TIME 1
#define GPR_HAS_PTHREAD_H 1
#define GPR_GETPID_IN_UNISTD_H 1
#ifdef _LP64
#define GPR_ARCH_64 1
#else
#define GPR_ARCH_32 1
#endif
#elif defined(__NetBSD__)

#define GPR_PLATFORM_STRING "netbsd"
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#define GPR_NETBSD 1
#define GPR_CPU_POSIX 1
#define GPR_GCC_ATOMIC 1
#define GPR_GCC_TLS 1
#define GPR_POSIX_LOG 1
#define GPR_POSIX_ENV 1
#define GPR_POSIX_TMPFILE 1
#define GPR_POSIX_STAT 1
#define GPR_POSIX_STRING 1
#define GPR_POSIX_SUBPROCESS 1
#define GPR_POSIX_SYNC 1
#define GPR_POSIX_TIME 1
#define GPR_GETPID_IN_UNISTD_H 1
#define GPR_SUPPORT_CHANNELS_FROM_FD 1
#ifdef _LP64
#define GPR_ARCH_64 1
#else
#define GPR_ARCH_32 1
#endif
#elif defined(__native_client__)
#define GPR_PLATFORM_STRING "nacl"
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#define GPR_NACL 1
#define GPR_CPU_POSIX 1
#define GPR_GCC_ATOMIC 1
#define GPR_POSIX_LOG 1
#define GPR_POSIX_ENV 1
#define GPR_POSIX_TMPFILE 1
#define GPR_POSIX_STAT 1
#define GPR_POSIX_STRING 1
#define GPR_POSIX_SUBPROCESS 1
#define GPR_POSIX_SYNC 1
#define GPR_POSIX_TIME 1
#define GPR_HAS_PTHREAD_H 1
#define GPR_GETPID_IN_UNISTD_H 1
#ifdef _LP64
#define GPR_ARCH_64 1
#else
#define GPR_ARCH_32 1
#endif
#elif defined(__Fuchsia__)
#define GRPC_ARES 0
#define GPR_FUCHSIA 1
#define GPR_ARCH_64 1
#define GPR_PLATFORM_STRING "fuchsia"
#include <features.h>

#define GPR_MUSL_LIBC_COMPAT 1
#define GPR_CPU_POSIX 1
#define GPR_GCC_ATOMIC 1
#define GPR_POSIX_LOG 1
#define GPR_POSIX_SYNC 1
#define GPR_POSIX_ENV 1
#define GPR_POSIX_TMPFILE 1
#define GPR_POSIX_STAT 1
#define GPR_POSIX_SUBPROCESS 1
#define GPR_POSIX_SYNC 1
#define GPR_POSIX_STRING 1
#define GPR_POSIX_TIME 1
#define GPR_HAS_PTHREAD_H 1
#define GPR_GETPID_IN_UNISTD_H 1
#define GRPC_ROOT_PEM_PATH "/config/ssl/cert.pem"
#elif defined(__HAIKU__)
#define GPR_PLATFORM_STRING "haiku"

#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#define GPR_HAIKU 1
#define GPR_CPU_POSIX 1
#define GPR_GCC_ATOMIC 1
#define GPR_POSIX_LOG 1
#define GPR_POSIX_ENV 1
#define GPR_POSIX_TMPFILE 1
#define GPR_POSIX_STAT 1
#define GPR_POSIX_STRING 1
#define GPR_POSIX_SUBPROCESS 1
#define GPR_POSIX_SYNC 1
#define GPR_POSIX_TIME 1
#define GPR_HAS_PTHREAD_H 1
#define GPR_GETPID_IN_UNISTD_H 1
#define GPR_SUPPORT_CHANNELS_FROM_FD 1
#ifdef _LP64
#define GPR_ARCH_64 1
#else
#define GPR_ARCH_32 1
#endif
#elif defined(__QNX__) || defined(__QNXNTO__)
#define GPR_PLATFORM_STRING "qnx"
#define GPR_CPU_POSIX 1
#define GPR_GCC_ATOMIC 1
#define GPR_POSIX_LOG 1
#define GPR_POSIX_ENV 1
#define GPR_POSIX_TMPFILE 1
#define GPR_POSIX_STAT 1
#define GPR_POSIX_STRING 1
#define GPR_POSIX_SYNC 1
#define GPR_POSIX_TIME 1
#define GPR_HAS_PTHREAD_H 1
#define GPR_GETPID_IN_UNISTD_H 1
#ifdef _LP64
#define GPR_ARCH_64 1
#else
#define GPR_ARCH_32 1
#endif
#else
#error "Could not auto-detect platform"
#endif
#endif

#if defined(__has_include)
#if __has_include(<atomic>)
#define GRPC_HAS_CXX11_ATOMIC
#endif
#endif

#ifndef GPR_PLATFORM_STRING
#warning "GPR_PLATFORM_STRING not auto-detected"
#define GPR_PLATFORM_STRING "unknown"
#endif

#ifdef GPR_GCOV
#undef GPR_FORBID_UNREACHABLE_CODE
#define GPR_FORBID_UNREACHABLE_CODE 1
#endif

#ifdef _MSC_VER
#if _MSC_VER < 1700
typedef __int8 int8_t;
typedef __int16 int16_t;
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif
#else
#include <stdint.h>
#endif

#ifdef GPR_LINUX

#define GPR_CYCLE_COUNTER_FALLBACK 1
#else
#define GPR_CYCLE_COUNTER_FALLBACK 1
#endif

#ifndef GPR_CACHELINE_SIZE_LOG
#if defined(__i386__) || defined(__x86_64__)
#define GPR_CACHELINE_SIZE_LOG 6
#endif
#ifndef GPR_CACHELINE_SIZE_LOG

#define GPR_CACHELINE_SIZE_LOG 6
#endif
#endif

#define GPR_CACHELINE_SIZE (1 << GPR_CACHELINE_SIZE_LOG)

#if defined(GPR_GCC_ATOMIC) && !defined(__ATOMIC_RELAXED)
#undef GPR_GCC_ATOMIC
#define GPR_GCC_SYNC 1
#endif

#if defined(GPR_GCC_ATOMIC) + defined(GPR_GCC_SYNC) + \
        defined(GPR_WINDOWS_ATOMIC) !=                \
    1
#error Must define exactly one of GPR_GCC_ATOMIC, GPR_GCC_SYNC, GPR_WINDOWS_ATOMIC
#endif

#if defined(GPR_ARCH_32) + defined(GPR_ARCH_64) != 1
#error Must define exactly one of GPR_ARCH_32, GPR_ARCH_64
#endif

#if defined(GPR_CPU_LINUX) + defined(GPR_CPU_POSIX) + defined(GPR_WINDOWS) + \
        defined(GPR_CPU_IPHONE) + defined(GPR_CPU_CUSTOM) !=                 \
    1
#error Must define exactly one of GPR_CPU_LINUX, GPR_CPU_POSIX, GPR_WINDOWS, GPR_CPU_IPHONE, GPR_CPU_CUSTOM
#endif

#define GPR_MAX_ALIGNMENT 16

#ifndef GRPC_ARES
#define GRPC_ARES 1
#endif

#ifndef GRPC_IF_NAMETOINDEX
#define GRPC_IF_NAMETOINDEX 1
#endif

#ifndef GRPC_UNUSED
#if defined(__GNUC__) && !defined(__MINGW32__)
#define GRPC_UNUSED __attribute__((unused))
#else
#define GRPC_UNUSED
#endif
#endif

#ifndef GPR_PRINT_FORMAT_CHECK
#ifdef __GNUC__
#define GPR_PRINT_FORMAT_CHECK(FORMAT_STR, ARGS) \
  __attribute__((format(printf, FORMAT_STR, ARGS)))
#else
#define GPR_PRINT_FORMAT_CHECK(FORMAT_STR, ARGS)
#endif
#endif

#ifndef GPR_HAS_CPP_ATTRIBUTE
#ifdef __has_cpp_attribute
#define GPR_HAS_CPP_ATTRIBUTE(a) __has_cpp_attribute(a)
#else
#define GPR_HAS_CPP_ATTRIBUTE(a) 0
#endif
#endif

#if defined(__GNUC__) && !defined(__MINGW32__)
#define GPR_ALIGN_STRUCT(n) __attribute__((aligned(n)))
#else
#define GPR_ALIGN_STRUCT(n)
#endif

#ifndef GRPC_MUST_USE_RESULT
#if GPR_HAS_CPP_ATTRIBUTE(nodiscard)
#define GRPC_MUST_USE_RESULT [[nodiscard]]
#elif defined(__GNUC__) && !defined(__MINGW32__)
#define GRPC_MUST_USE_RESULT __attribute__((warn_unused_result))
#else
#define GRPC_MUST_USE_RESULT
#endif
#ifdef USE_STRICT_WARNING

#define GRPC_MUST_USE_RESULT_WHEN_USE_STRICT_WARNING GRPC_MUST_USE_RESULT
#else
#define GRPC_MUST_USE_RESULT_WHEN_USE_STRICT_WARNING
#endif
#endif

#ifndef GRPC_REINITIALIZES
#if defined(__clang__)
#if GPR_HAS_CPP_ATTRIBUTE(clang::reinitializes)
#define GRPC_REINITIALIZES [[clang::reinitializes]]
#else
#define GRPC_REINITIALIZES
#endif
#else
#define GRPC_REINITIALIZES
#endif
#endif

#ifndef GPR_HAS_ATTRIBUTE
#ifdef __has_attribute
#define GPR_HAS_ATTRIBUTE(a) __has_attribute(a)
#else
#define GPR_HAS_ATTRIBUTE(a) 0
#endif
#endif

#if GPR_HAS_ATTRIBUTE(noreturn)
#define GPR_ATTRIBUTE_NORETURN __attribute__((noreturn))
#else
#define GPR_ATTRIBUTE_NORETURN
#endif

#if defined(GPR_FORBID_UNREACHABLE_CODE) && GPR_FORBID_UNREACHABLE_CODE
#define GPR_UNREACHABLE_CODE(STATEMENT)
#else
#ifdef __cplusplus
extern "C" {
#endif
extern void gpr_unreachable_code(const char* reason, const char* file,
                                 int line) GPR_ATTRIBUTE_NORETURN;
#ifdef __cplusplus
}
#endif
#define GPR_UNREACHABLE_CODE(STATEMENT)                   \
  do {                                                    \
    gpr_unreachable_code(#STATEMENT, __FILE__, __LINE__); \
    STATEMENT;                                            \
  } while (0)
#endif

#ifndef GPRAPI
#define GPRAPI
#endif

#ifndef GRPCAPI
#define GRPCAPI GPRAPI
#endif

#ifndef CENSUSAPI
#define CENSUSAPI GRPCAPI
#endif

#ifndef GPR_HAS_FEATURE
#ifdef __has_feature
#define GPR_HAS_FEATURE(a) __has_feature(a)
#else
#define GPR_HAS_FEATURE(a) 0
#endif
#endif

#ifndef GPR_ATTRIBUTE_NOINLINE
#if GPR_HAS_ATTRIBUTE(noinline) || (defined(__GNUC__) && !defined(__clang__))
#define GPR_ATTRIBUTE_NOINLINE __attribute__((noinline))
#define GPR_HAS_ATTRIBUTE_NOINLINE 1
#else
#define GPR_ATTRIBUTE_NOINLINE
#endif
#endif

#ifndef GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION
#ifdef __cplusplus
#if GPR_HAS_CPP_ATTRIBUTE(clang::always_inline)
#define GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION [[clang::always_inline]]
#elif GPR_HAS_ATTRIBUTE(always_inline)
#define GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION __attribute__((always_inline))
#else

#define GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION
#endif
#else

#define GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION
#endif
#endif

#ifndef GPR_NO_UNIQUE_ADDRESS
#if GPR_HAS_CPP_ATTRIBUTE(no_unique_address)
#define GPR_NO_UNIQUE_ADDRESS [[no_unique_address]]
#else
#define GPR_NO_UNIQUE_ADDRESS
#endif
#endif

#ifndef GRPC_DEPRECATED
#if GPR_HAS_CPP_ATTRIBUTE(deprecated)
#define GRPC_DEPRECATED(reason) [[deprecated(reason)]]
#else
#define GRPC_DEPRECATED(reason)
#endif
#endif

#ifndef GPR_ATTRIBUTE_WEAK

#if (GPR_HAS_ATTRIBUTE(weak) || (defined(__GNUC__) && !defined(__clang__))) && \
    !(defined(__llvm__) && defined(_WIN32))
#define GPR_ATTRIBUTE_WEAK __attribute__((weak))
#define GPR_HAS_ATTRIBUTE_WEAK 1
#else
#define GPR_ATTRIBUTE_WEAK
#endif
#endif

#ifndef GPR_ATTRIBUTE_NO_TSAN
#if GPR_HAS_FEATURE(thread_sanitizer)
#define GPR_ATTRIBUTE_NO_TSAN __attribute__((no_sanitize("thread")))
#endif
#ifndef GPR_ATTRIBUTE_NO_TSAN
#define GPR_ATTRIBUTE_NO_TSAN
#endif
#endif

#ifndef GRPC_TSAN_SUPPRESSED
#if defined(__SANITIZE_THREAD__)
#define GRPC_TSAN_ENABLED
#elif GPR_HAS_FEATURE(thread_sanitizer)
#define GRPC_TSAN_ENABLED
#endif
#endif

#ifndef GRPC_ASAN_SUPPRESSED
#if defined(__SANITIZE_ADDRESS__)
#define GRPC_ASAN_ENABLED
#elif GPR_HAS_FEATURE(address_sanitizer)
#define GRPC_ASAN_ENABLED
#endif
#endif

#ifndef GRPC_ALLOW_EXCEPTIONS
#ifdef GPR_WINDOWS
#if defined(_MSC_VER) && defined(_CPPUNWIND)
#define GRPC_ALLOW_EXCEPTIONS 1
#elif defined(__EXCEPTIONS)
#define GRPC_ALLOW_EXCEPTIONS 1
#else
#define GRPC_ALLOW_EXCEPTIONS 0
#endif
#else
#ifdef __EXCEPTIONS
#define GRPC_ALLOW_EXCEPTIONS 1
#else
#define GRPC_ALLOW_EXCEPTIONS 0
#endif
#endif
#endif

#ifdef __has_builtin
#define GRPC_HAS_BUILTIN(a) __has_builtin(a)
#else
#define GRPC_HAS_BUILTIN(a) 0
#endif

#ifdef __GNUC__
#define GPR_LIKELY(x) __builtin_expect((x), 1)
#define GPR_UNLIKELY(x) __builtin_expect((x), 0)
#else
#define GPR_LIKELY(x) (x)
#define GPR_UNLIKELY(x) (x)
#endif

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif

#ifndef GPR_MSVC_EMPTY_BASE_CLASS_WORKAROUND
#ifdef GPR_WINDOWS
#define GPR_MSVC_EMPTY_BASE_CLASS_WORKAROUND __declspec(empty_bases)
#else
#define GPR_MSVC_EMPTY_BASE_CLASS_WORKAROUND
#endif
#endif

#define GRPC_CALLBACK_API_NONEXPERIMENTAL

#ifdef __clang__
#if __clang__ && __clang_major__ <= 12 && __has_feature(memory_sanitizer)
#undef GPR_NO_UNIQUE_ADDRESS
#define GPR_NO_UNIQUE_ADDRESS
#endif
#endif

#endif

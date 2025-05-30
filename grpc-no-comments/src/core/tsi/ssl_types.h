
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_SSL_TYPES_H
#define GRPC_SRC_CORE_TSI_SSL_TYPES_H

#include <grpc/support/port_platform.h>
#include <openssl/ssl.h>

#ifdef OPENSSL_IS_BORINGSSL
#define TSI_INT_AS_SIZE(x) ((size_t)(x))
#define TSI_SIZE_AS_SIZE(x) (x)
#else
#define TSI_INT_AS_SIZE(x) (x)
#define TSI_SIZE_AS_SIZE(x) ((int)(x))
#endif

#endif


// Copyright 2023 gRPC authors.

#ifndef GRPCPP_SECURITY_TLS_CRL_PROVIDER_H
#define GRPCPP_SECURITY_TLS_CRL_PROVIDER_H

#include <grpc/grpc_crl_provider.h>
#include <grpcpp/impl/sync.h>
#include <grpcpp/support/string_ref.h>

namespace grpc {
namespace experimental {

using grpc_core::experimental::
    CertificateInfo;
using grpc_core::experimental::
    CreateStaticCrlProvider;
using grpc_core::experimental::Crl;
using grpc_core::experimental::CrlProvider;

}
}

#endif

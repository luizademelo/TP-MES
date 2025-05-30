
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SECURITY_AUTH_METADATA_PROCESSOR_H
#define GRPCPP_SECURITY_AUTH_METADATA_PROCESSOR_H

#include <grpcpp/security/auth_context.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/string_ref.h>

#include <map>

namespace grpc {

class AuthMetadataProcessor {
 public:
  typedef std::multimap<grpc::string_ref, grpc::string_ref> InputMetadata;
  typedef std::multimap<std::string, std::string> OutputMetadata;

  virtual ~AuthMetadataProcessor() {}

  virtual bool IsBlocking() const { return true; }

  virtual grpc::Status Process(const InputMetadata& auth_metadata,
                               grpc::AuthContext* context,
                               OutputMetadata* consumed_auth_metadata,
                               OutputMetadata* response_metadata) = 0;
};

}

#endif

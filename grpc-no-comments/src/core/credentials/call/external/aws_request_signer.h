
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_CALL_EXTERNAL_AWS_REQUEST_SIGNER_H
#define GRPC_SRC_CORE_CREDENTIALS_CALL_EXTERNAL_AWS_REQUEST_SIGNER_H

#include <grpc/support/port_platform.h>

#include <map>
#include <string>

#include "src/core/lib/iomgr/error.h"
#include "src/core/util/uri.h"

namespace grpc_core {

class AwsRequestSigner {
 public:

  AwsRequestSigner(std::string access_key_id, std::string secret_access_key,
                   std::string token, std::string method, std::string url,
                   std::string region, std::string request_payload,
                   std::map<std::string, std::string> additional_headers,
                   grpc_error_handle* error);

  std::map<std::string, std::string> GetSignedRequestHeaders();

 private:
  std::string access_key_id_;
  std::string secret_access_key_;
  std::string token_;
  std::string method_;
  URI url_;
  std::string region_;
  std::string request_payload_;
  std::map<std::string, std::string> additional_headers_;

  std::string static_request_date_;
  std::map<std::string, std::string> request_headers_;
};

}

#endif

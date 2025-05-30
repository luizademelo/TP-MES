
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_RING_HASH_RING_HASH_H
#define GRPC_SRC_CORE_LOAD_BALANCING_RING_HASH_RING_HASH_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include "src/core/service_config/service_config_call_data.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/validation_errors.h"

#define GRPC_ARG_RING_HASH_ENDPOINT_HASH_KEY \
  GRPC_ARG_NO_SUBCHANNEL_PREFIX "hash_key"

namespace grpc_core {

class RequestHashAttribute final
    : public ServiceConfigCallData::CallAttributeInterface {
 public:
  static UniqueTypeName TypeName();

  explicit RequestHashAttribute(uint64_t request_hash)
      : request_hash_(request_hash) {}

  uint64_t request_hash() const { return request_hash_; }

 private:
  UniqueTypeName type() const override { return TypeName(); }

  uint64_t request_hash_;
};

}

#endif

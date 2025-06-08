Here's the commented version of the code:

```c++
# Require the Google Protocol Buffers library for Ruby
require 'google/protobuf'

# Binary descriptor data containing the compiled Protocol Buffer definition
# This is a serialized version of the health check service proto file
descriptor_data = "\n\x1bgrpc/health/v1/health.proto\x12\x0egrpc.health.v1\"%\n\x12HealthCheckRequest\x12\x0f\n\x07service\x18\x01 \x01(\t\"\xa9\x01\n\x13HealthCheckResponse\x12\x41\n\x06status\x18\x01 \x01(\x0e\x32\x31.grpc.health.v1.HealthCheckResponse.ServingStatus\"O\n\rServingStatus\x12\x0b\n\x07UNKNOWN\x10\x00\x12\x0b\n\x07SERVING\x10\x01\x12\x0f\n\x0bNOT_SERVING\x10\x02\x12\x13\n\x0fSERVICE_UNKNOWN\x10\x03\x32\xae\x01\n\x06Health\x12P\n\x05\x43heck\x12\".grpc.health.v1.HealthCheckRequest\x1a#.grpc.health.v1.HealthCheckResponse\x12R\n\x05Watch\x12\".grpc.health.v1.HealthCheckRequest\x1a#.grpc.health.v1.HealthCheckResponse0\x01\x42\x61\n\x11io.grpc.health.v1B\x0bHealthProtoP\x01Z,google.golang.org/grpc/health/grpc_health_v1\xaa\x02\x0eGrpc.Health.V1b\x06proto3"

# Get the generated descriptor pool which holds all compiled proto definitions
pool = Google::Protobuf::DescriptorPool.generated_pool

# Add the compiled health check service proto to the descriptor pool
pool.add_serialized_file(descriptor_data)

# Define the gRPC Health Check module structure in Ruby
module Grpc
  module Health
    module V1
      # Define the HealthCheckRequest message class by looking up the descriptor
      HealthCheckRequest = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("grpc.health.v1.HealthCheckRequest").msgclass
      
      # Define the HealthCheckResponse message class by looking up the descriptor
      HealthCheckResponse = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("grpc.health.v1.HealthCheckResponse").msgclass
      
      # Define the ServingStatus enum module within HealthCheckResponse
      HealthCheckResponse::ServingStatus = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("grpc.health.v1.HealthCheckResponse.ServingStatus").enummodule
    end
  end
end
```

Key points explained in the comments:
1. The code loads Protocol Buffers functionality for Ruby
2. The descriptor_data contains a compiled/serialized version of the health.proto file
3. The code registers this proto definition with Protocol Buffers' descriptor pool
4. It then creates Ruby classes/enums that correspond to the Protocol Buffer messages
5. The module structure mirrors the package structure defined in the proto file (grpc.health.v1)

The code essentially sets up Protocol Buffer message classes for the gRPC health check service, which is used to monitor service health status.
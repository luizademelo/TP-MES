Here's the commented version of the code:

```c++
# Copyright 2015 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Require necessary gRPC libraries
require 'grpc'
require 'grpc/health/v1/health_pb'

# Module namespace for gRPC Health Check service
module Grpc
  module Health
    module V1
      module Health
        # Service class implementing the gRPC Health Check Protocol
        class Service
          # Include GenericService module which provides base functionality for gRPC services
          include ::GRPC::GenericService

          # Configuration for message serialization/deserialization
          self.marshal_class_method = :encode  # Method used to encode messages
          self.unmarshal_class_method = :decode  # Method used to decode messages
          self.service_name = 'grpc.health.v1.Health'  # Full service name as per protocol

          # Define RPC methods for the Health service:

          # Check - Unary RPC method that takes a HealthCheckRequest and returns a HealthCheckResponse
          # Used to get the current health status of a service
          rpc :Check, ::Grpc::Health::V1::HealthCheckRequest, ::Grpc::Health::V1::HealthCheckResponse

          # Watch - Server streaming RPC method that takes a HealthCheckRequest and streams HealthCheckResponses
          # Used to monitor the health status of a service over time
          rpc :Watch, ::Grpc::Health::V1::HealthCheckRequest, stream(::Grpc::Health::V1::HealthCheckResponse)

          # Generate a client stub class for this service
          # This allows clients to interact with the Health service
          Stub = Service.rpc_stub_class
        end
      end
    end
  end
end
```

The comments explain:
1. The overall purpose of the file (gRPC Health Check service implementation)
2. The module hierarchy and organization
3. The Service class and its inheritance
4. The serialization configuration
5. Each RPC method's purpose and type (unary vs streaming)
6. The client stub generation

The comments are designed to help future developers understand both the high-level purpose and specific implementation details of this health check service.
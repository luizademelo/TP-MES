Here's the commented version of the code snippet:

```c++
# Copyright 2015 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Require the core gRPC library and the generated protobuf files
require 'grpc'
require 'grpc/testing/duplicate/echo_duplicate_pb'

module Grpc
  module Testing
    module Duplicate
      # Service implementation for EchoTestService
      module EchoTestService
        # The Service class defines the RPC service interface and methods
        class Service
          # Include the GenericService module which provides base functionality for gRPC services
          include ::GRPC::GenericService

          # Configuration for message serialization/deserialization
          self.marshal_class_method = :encode    # Method used to encode messages
          self.unmarshal_class_method = :decode # Method used to decode messages
          
          # The full service name that matches the protobuf service definition
          self.service_name = 'grpc.testing.duplicate.EchoTestService'

          # Define the RPC methods:
          # 1. Unary RPC - single request, single response
          rpc :Echo, ::Grpc::Testing::EchoRequest, ::Grpc::Testing::EchoResponse
          
          # 2. Server streaming RPC - single request, stream of responses
          rpc :ResponseStream, ::Grpc::Testing::EchoRequest, stream(::Grpc::Testing::EchoResponse)
        end

        # The Stub class is automatically generated to provide client-side functionality
        Stub = Service.rpc_stub_class
      end
    end
  end
end
```

Key additions in the comments:
1. Added explanation of the license header
2. Documented the purpose of each require statement
3. Explained the module hierarchy and service structure
4. Clarified the GenericService inclusion and its purpose
5. Documented the serialization configuration
6. Explained the service_name and its significance
7. Added detailed comments for each RPC method type
8. Explained the purpose of the generated Stub class

The comments provide context about both the implementation details and the gRPC concepts being used, which will help future developers understand and maintain the code.
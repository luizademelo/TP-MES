Here's the commented version of the code:

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

# Require the gRPC library and the generated protobuf files
require 'grpc'
require 'echo_pb'

# Module namespace for the Echo service
module Echo
  # Module for the EchoServer service implementation
  module EchoServer
    # Service class that implements the gRPC service interface
    class Service
      # Include the GenericService module from gRPC to provide base functionality
      include ::GRPC::GenericService

      # Configure the marshaling (serialization) methods for the service
      # These methods will be used to encode/decode messages between client and server
      self.marshal_class_method = :encode  # Method used to encode/serialize messages
      self.unmarshal_class_method = :decode  # Method used to decode/deserialize messages
      
      # Define the fully-qualified service name that matches the protobuf definition
      self.service_name = 'echo.EchoServer'

      # Define the RPC method 'Echo' that takes an EchoRequest and returns an EchoReply
      # This maps to the service definition in the protobuf file
      rpc :Echo, ::Echo::EchoRequest, ::Echo::EchoReply
    end

    # Create a Stub class that clients can use to call the service
    # The stub provides the client-side interface for making RPC calls
    Stub = Service.rpc_stub_class
  end
end
```

The comments explain:
1. The licensing information at the top
2. The required dependencies (gRPC library and generated protobuf files)
3. The module structure and purpose
4. The Service class implementation details including:
   - Marshaling configuration
   - Service name definition
   - RPC method definition
5. The Stub class creation for client-side usage

The comments provide context about the gRPC service setup while maintaining clarity about the specific Echo service implementation.
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

# Require the gRPC library and generated protocol buffer files
require 'grpc'
require 'math_pb'

# Math service module definition
module Math
  module Math
    # Service class that implements the gRPC service methods
    class Service
      # Include GenericService module from gRPC for base functionality
      include ::GRPC::GenericService

      # Configure serialization/deserialization methods
      self.marshal_class_method = :encode  # Method for encoding messages
      self.unmarshal_class_method = :decode  # Method for decoding messages
      self.service_name = 'math.Math'  # Fully qualified service name

      # Define RPC methods:

      # Unary RPC: single request, single response
      # Takes DivArgs and returns DivReply
      rpc :Div, ::Math::DivArgs, ::Math::DivReply

      # Bidirectional streaming RPC: stream of requests, stream of responses
      # Takes a stream of DivArgs and returns a stream of DivReplies
      rpc :DivMany, stream(::Math::DivArgs), stream(::Math::DivReply)

      # Server streaming RPC: single request, stream of responses
      # Takes FibArgs and returns a stream of Num messages
      rpc :Fib, ::Math::FibArgs, stream(::Math::Num)

      # Client streaming RPC: stream of requests, single response
      # Takes a stream of Num messages and returns a single Num
      rpc :Sum, stream(::Math::Num), ::Math::Num
    end

    # Generate a client stub class for this service
    # The stub provides client-side methods to call the RPCs
    Stub = Service.rpc_stub_class
  end
end
```

The comments explain:
1. The overall structure and purpose of the file
2. The service definition and configuration
3. Each RPC method type (unary, server streaming, client streaming, bidirectional streaming)
4. The purpose of the generated stub class
5. The serialization/deserialization configuration

The comments are placed to be helpful for both:
- Developers implementing the service
- Developers using the client stub to call the service
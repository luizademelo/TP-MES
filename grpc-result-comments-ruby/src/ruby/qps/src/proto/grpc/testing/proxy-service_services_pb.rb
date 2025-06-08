Here's the commented version of the code:

```c++
# Copyright 2017 gRPC authors.
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

# Require necessary gRPC libraries and generated protobuf files
require 'grpc'
require 'src/proto/grpc/testing/proxy-service_pb'

# Module namespace for gRPC testing functionality
module Grpc
  module Testing
    # Module for the ProxyClientService functionality
    module ProxyClientService
      # Service class implementing the gRPC service methods
      class Service
        # Include GRPC::GenericService to get base gRPC service functionality
        include ::GRPC::GenericService

        # Configure marshaling (serialization) methods for messages
        self.marshal_class_method = :encode  # Method used to encode messages
        self.unmarshal_class_method = :decode  # Method used to decode messages
        
        # Define the service name that will be used in the gRPC protocol
        self.service_name = 'grpc.testing.ProxyClientService'

        # Define the service's RPC methods:

        # Unary RPC: Get configuration from the server
        # Takes a Void request and returns a ClientConfig response
        rpc :GetConfig, ::Grpc::Testing::Void, ::Grpc::Testing::ClientConfig

        # Client streaming RPC: Report timing statistics to the server
        # Accepts a stream of ProxyStat messages and returns a Void response
        rpc :ReportTime, stream(::Grpc::Testing::ProxyStat), ::Grpc::Testing::Void

        # Client streaming RPC: Report histogram data to the server
        # Accepts a stream of HistogramData messages and returns a Void response
        rpc :ReportHist, stream(::Grpc::Testing::HistogramData), ::Grpc::Testing::Void
      end

      # Generate a client stub class for this service
      # This allows clients to call the service's RPC methods
      Stub = Service.rpc_stub_class
    end
  end
end
```

The comments explain:
1. The overall structure and purpose of the module
2. The base functionality being included
3. The message serialization configuration
4. Each RPC method's type (unary or streaming), purpose, and message types
5. The client stub generation

The comments are designed to help future developers understand:
- What the service does
- How to use it
- The nature of each RPC call
- Where to find related protobuf message definitions
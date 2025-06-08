Here's the commented version of the code:

```c++
# Copyright 2015-2016 gRPC authors.
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

# Require the necessary gRPC libraries
require 'grpc'
require 'grpc/testing/metrics_pb'

module Grpc
  module Testing
    module MetricsService
      # Service class that defines the MetricsService RPC methods
      class Service
        # Include GRPC::GenericService to get RPC functionality
        include ::GRPC::GenericService

        # Configuration for message serialization/deserialization
        self.marshal_class_method = :encode  # Method to use for message serialization
        self.unmarshal_class_method = :decode  # Method to use for message deserialization
        self.service_name = 'grpc.testing.MetricsService'  # The service name used in gRPC

        # RPC method definition: GetAllGauges
        # - Takes an EmptyMessage as input
        # - Returns a stream of GaugeResponse messages
        rpc :GetAllGauges, ::Grpc::Testing::EmptyMessage, stream(::Grpc::Testing::GaugeResponse)

        # RPC method definition: GetGauge
        # - Takes a GaugeRequest as input
        # - Returns a single GaugeResponse message
        rpc :GetGauge, ::Grpc::Testing::GaugeRequest, ::Grpc::Testing::GaugeResponse
      end

      # Stub class that clients use to connect to MetricsService
      Stub = Service.rpc_stub_class
    end
  end
end
```

The comments explain:
1. The overall purpose of the file (defining a gRPC MetricsService)
2. The service class and its inheritance
3. The serialization configuration
4. Each RPC method's purpose and signature
5. The client stub class

The comments are placed to be helpful for both:
- Developers maintaining the service implementation
- Clients who need to understand how to interact with the service

The license header is preserved as-is since it's a legal requirement rather than implementation documentation.
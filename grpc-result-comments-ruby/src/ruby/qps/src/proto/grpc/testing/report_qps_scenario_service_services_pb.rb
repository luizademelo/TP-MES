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

# Require the core gRPC Ruby library
require 'grpc'
# Require the generated protobuf service definition for QPS scenario reporting
require 'src/proto/grpc/testing/report_qps_scenario_service_pb'

module Grpc
  module Testing
    module ReportQpsScenarioService
      # Service class that implements the ReportQpsScenarioService RPC interface
      class Service
        # Include GRPC::GenericService to get base functionality for gRPC services
        include ::GRPC::GenericService

        # Configure the marshaling (serialization) methods for requests/responses
        self.marshal_class_method = :encode  # Method used to encode messages
        self.unmarshal_class_method = :decode  # Method used to decode messages
        
        # Define the full service name that matches the protobuf service definition
        self.service_name = 'grpc.testing.ReportQpsScenarioService'

        # Define the RPC method for reporting QPS (Queries Per Second) scenarios
        # - Method name: :ReportScenario
        # - Request type: ::Grpc::Testing::ScenarioResult (contains scenario results)
        # - Response type: ::Grpc::Testing::Void (empty response)
        rpc :ReportScenario, ::Grpc::Testing::ScenarioResult, ::Grpc::Testing::Void
      end

      # Generate a client stub class for this service that can be used to make RPC calls
      Stub = Service.rpc_stub_class
    end
  end
end
```

Key aspects covered in the comments:
1. File licensing and copyright information
2. Required dependencies (gRPC core and generated protobuf)
3. Module structure and organization
4. Service class implementation details
5. Configuration of serialization/deserialization methods
6. RPC method definition and its signature
7. Client stub generation for making remote calls

The comments provide context about the service's purpose (QPS scenario reporting) and explain the key components of the gRPC service definition in Ruby.
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

# Require the necessary gRPC library and generated protobuf files
require 'grpc'
require 'route_guide_pb'

# Module namespace for the RouteGuide service implementation
module Routeguide
  module RouteGuide

    # Service class that implements the RouteGuide service
    class Service
      # Include GRPC::GenericService to get base functionality for gRPC services
      include GRPC::GenericService

      # Configure serialization/deserialization methods
      self.marshal_class_method = :encode  # Method used to encode messages
      self.unmarshal_class_method = :decode  # Method used to decode messages
      self.service_name = 'routeguide.RouteGuide'  # Fully qualified service name

      # Define the RPC methods for the service:

      # Unary RPC: Client sends a single Point, server returns a single Feature
      rpc :GetFeature, Point, Feature

      # Server streaming RPC: Client sends a Rectangle, server streams multiple Features
      rpc :ListFeatures, Rectangle, stream(Feature)

      # Client streaming RPC: Client streams multiple Points, server returns a single RouteSummary
      rpc :RecordRoute, stream(Point), RouteSummary

      # Bidirectional streaming RPC: Both client and server can stream RouteNotes
      rpc :RouteChat, stream(RouteNote), stream(RouteNote)
    end

    # Create a client stub class for the RouteGuide service
    # This allows clients to call the RPC methods defined in the Service class
    Stub = Service.rpc_stub_class
  end
end
```

The comments explain:
1. The licensing and copyright information
2. Required dependencies
3. The module namespace organization
4. The Service class and its inheritance
5. Configuration of serialization methods
6. Each RPC method's type (unary, server streaming, client streaming, bidirectional)
7. The purpose of the generated Stub class for clients

The comments are concise yet informative, helping future developers understand both the structure and functionality of this gRPC service definition.
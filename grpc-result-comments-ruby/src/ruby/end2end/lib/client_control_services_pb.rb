Here's the commented version of the code:

```c++
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Require necessary gRPC libraries and generated protobuf files
require 'grpc'
require 'client_control_pb'

# Module containing client control service definitions
module ClientControl
  # Module for ClientController service definition
  module ClientController
    # Service class implementing gRPC service methods
    class Service
      # Include GenericService to provide gRPC functionality
      include ::GRPC::GenericService

      # Configuration for message serialization/deserialization
      self.marshal_class_method = :encode  # Method for serializing messages
      self.unmarshal_class_method = :decode  # Method for deserializing messages
      self.service_name = 'client_control.ClientController'  # Full service name

      # Define RPC methods:
      # 1. DoEchoRpc - Takes DoEchoRpcRequest and returns Void
      rpc :DoEchoRpc, ::ClientControl::DoEchoRpcRequest, ::ClientControl::Void
      # 2. Shutdown - Takes Void and returns Void (simple shutdown command)
      rpc :Shutdown, ::ClientControl::Void, ::ClientControl::Void
    end

    # Generate client stub class for this service
    Stub = Service.rpc_stub_class
  end

  # Module for ParentController service definition
  module ParentController
    # Service class implementing gRPC service methods
    class Service
      # Include GenericService to provide gRPC functionality
      include ::GRPC::GenericService

      # Configuration for message serialization/deserialization
      self.marshal_class_method = :encode  # Method for serializing messages
      self.unmarshal_class_method = :decode  # Method for deserializing messages
      self.service_name = 'client_control.ParentController'  # Full service name

      # Define RPC method:
      # SetClientControllerPort - Takes Port message and returns Void
      # Used to configure the port for client controller communication
      rpc :SetClientControllerPort, ::ClientControl::Port, ::ClientControl::Void
    end

    # Generate client stub class for this service
    Stub = Service.rpc_stub_class
  end
end
```

The comments explain:
1. The overall structure and purpose of the module
2. Each service definition and its components
3. The serialization/deserialization configuration
4. Each RPC method's purpose and signature
5. The client stub generation for each service

The comments are designed to help future developers understand:
- What services are available
- How to interact with them
- The message types used
- The underlying gRPC configuration
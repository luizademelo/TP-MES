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

require 'grpc'  # Require the gRPC Ruby library

# Module defining a simple gRPC service without using Protocol Buffers
module EchoWithoutProtobuf

  # Service class implementing a simple echo RPC service
  class Service
    # Include GRPC::GenericService to get basic gRPC service functionality
    include GRPC::GenericService

    # Configure marshaling (serialization) methods for message conversion
    # - Uses Ruby's try_convert method for both marshaling and unmarshaling
    self.marshal_class_method = :try_convert
    self.unmarshal_class_method = :try_convert
    
    # Define the service name that will be used in gRPC
    self.service_name = 'EchoWithoutProtobuf'

    # Define a simple RPC method named 'Echo' that takes a String and returns a String
    rpc :Echo, String, String
  end

  # Create a client stub class for the Service
  # This allows clients to call the Echo RPC method
  Stub = Service.rpc_stub_class
end
```

Key points explained in the comments:
1. The overall purpose of the module (simple gRPC service without Protocol Buffers)
2. The Service class and its inheritance/functionality
3. The marshaling configuration using Ruby's try_convert
4. The service name definition
5. The RPC method definition (Echo)
6. The client stub creation

The comments aim to make it clear how this code implements a basic gRPC service while avoiding the typical Protocol Buffers serialization, using Ruby's built-in conversion methods instead.
Here's the commented version of the code:

```c++
#!/usr/bin/env ruby

# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Set up the load path to include local library directory
this_dir = File.expand_path(File.dirname(__FILE__))
lib_dir = File.join(this_dir, 'lib')
# Add lib directory to the load path unless it's already included
$LOAD_PATH.unshift(lib_dir) unless $LOAD_PATH.include?(lib_dir)

# Require necessary gRPC libraries
require 'grpc'
require 'helloworld_services_pb'  # Contains the generated gRPC service and message classes

# Implementation of the Greeter service defined in the protobuf file
class GreeterServer < Helloworld::Greeter::Service
  # Implements the say_hello RPC method
  # @param hello_req [Helloworld::HelloRequest] the request message containing the name
  # @param _unused_call [GRPC::ActiveCall] unused call object
  # @return [Helloworld::HelloReply] the response message with greeting
  def say_hello(hello_req, _unused_call)
    Helloworld::HelloReply.new(message: "Hello #{hello_req.name}")
  end
end

# Main method to start the gRPC server
def main
  # Create a new gRPC server instance
  s = GRPC::RpcServer.new
  
  # Add an insecure HTTP/2 port (no SSL/TLS) listening on all interfaces
  s.add_http2_port('0.0.0.0:50051', :this_port_is_insecure)
  
  # Register the Greeter service implementation with the server
  s.handle(GreeterServer)

  # Run the server until terminated by SIGINT (Ctrl+C) or SIGTERM
  # The array specifies which signals to handle: 1 (SIGHUP), 'int' (SIGINT), 'SIGTERM'
  s.run_till_terminated_or_interrupted([1, 'int', 'SIGTERM'])
end

# Start the server by calling main
main
```

Key improvements made:
1. Added comments explaining the purpose of each significant code block
2. Documented the GreeterServer class and its method
3. Added parameter and return value documentation for the say_hello method
4. Explained the server configuration and signal handling
5. Clarified the purpose of the load path manipulation
6. Added context for the port binding configuration
7. Explained the server startup process

The comments are concise yet informative, providing enough context for future maintainers to understand the code's purpose and functionality without being overly verbose.
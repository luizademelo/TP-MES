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

# Add the current directory to the Ruby load path to allow requiring local files
this_dir = File.expand_path(File.dirname(__FILE__))
$LOAD_PATH.unshift(this_dir) unless $LOAD_PATH.include?(this_dir)

# Require the necessary gRPC library and the generated service definition
require 'grpc'
require 'echo_services_noprotobuf'

# Implementation of the Echo service without Protocol Buffers
class EchoServer < EchoWithoutProtobuf::Service
  # Implements the echo RPC method
  # @param echo_req [Object] The request message received from the client
  # @param _unused_call [GRPC::ActiveCall] The RPC call object (unused in this simple implementation)
  # @return [Object] Returns the same message that was received (echo behavior)
  def echo(echo_req, _unused_call)
    echo_req
  end
end

# Main method to start the gRPC server
def main
  # Create a new gRPC server instance
  s = GRPC::RpcServer.new
  
  # Bind the server to an insecure HTTP/2 port (no TLS)
  # '0.0.0.0' means listen on all available network interfaces
  # Port 50051 is the standard port for gRPC services
  s.add_http2_port('0.0.0.0:50051', :this_port_is_insecure)
  
  # Register the Echo service implementation with the server
  s.handle(EchoServer)
  
  # Start the server and run indefinitely until terminated
  s.run_till_terminated
end

# Start the server by calling the main method
main
```

Key improvements in the comments:
1. Added explanation of the load path modification
2. Documented the purpose of each require statement
3. Added class-level documentation for the EchoServer
4. Added detailed method documentation for the echo RPC method
5. Added comprehensive comments for each step in the main method
6. Explained the significance of the port binding parameters
7. Clarified the server's run behavior

The comments now provide a clear understanding of:
- The code's structure
- The gRPC server setup process
- The echo service implementation
- The server's network configuration
- The overall execution flow
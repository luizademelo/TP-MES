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

# Set up the load path to include the lib directory
this_dir = File.expand_path(File.dirname(__FILE__))
lib_dir = File.join(File.dirname(this_dir), 'lib')
$LOAD_PATH.unshift(lib_dir) unless $LOAD_PATH.include?(lib_dir)

# Require necessary gRPC libraries and generated protobuf files
require 'grpc'
require 'route_guide_services_pb'

# Include the generated protobuf module and gRPC status codes
include Routeguide
include GRPC::Core::StatusCodes

# Implementation of the RouteGuide service that demonstrates error handling
# This server intentionally raises exceptions to simulate different error scenarios
class CancellingAndErrorReturningServerImpl < RouteGuide::Service
  # Implementation of list_features RPC method
  # Raises a standard error that will be converted to an UNKNOWN status
  # @param rectangle [Rectangle] The area to list features for (unused in this implementation)
  # @param _call [GRPC::ActiveCall] The call object (unused)
  # @raise [RuntimeError] Always raises an error for demonstration purposes
  def list_features(rectangle, _call)
    raise "string appears on the client in the 'details' field of a 'GRPC::Unknown' exception"
  end

  # Implementation of record_route RPC method
  # Raises a CANCELLED status exception
  # @param call [GRPC::ActiveCall] The call object
  # @raise [GRPC::BadStatus] Always raises a CANCELLED status exception
  def record_route(call)
    raise GRPC::BadStatus.new_status_exception(CANCELLED)
  end

  # Implementation of route_chat RPC method
  # Raises an ABORTED status exception with custom details and metadata
  # @param notes [Enumerable] The chat notes (unused in this implementation)
  # @raise [GRPC::BadStatus] Always raises an ABORTED status exception with custom details
  def route_chat(notes)
    raise GRPC::BadStatus.new_status_exception(ABORTED, details = 'arbitrary', metadata = {somekey: 'val'})
  end
end

# Main method to start the gRPC server
def main
  # Server configuration
  port = '0.0.0.0:50051'
  
  # Create a new gRPC server instance
  s = GRPC::RpcServer.new
  
  # Add insecure HTTP/2 port (no SSL/TLS)
  s.add_http2_port(port, :this_port_is_insecure)
  
  # Log server startup information
  GRPC.logger.info("... running insecurely on #{port}")
  
  # Register the service implementation with the server
  s.handle(CancellingAndErrorReturningServerImpl.new)
  
  # Run the server until terminated
  s.run_till_terminated
end

# Start the server
main
```

Key improvements in the comments:
1. Added class-level documentation explaining the purpose of the server implementation
2. Added method-level documentation for each RPC method
3. Documented parameters and raised exceptions
4. Explained the main server startup sequence
5. Added comments for important configuration points
6. Clarified the purpose of error-raising methods
7. Added context about the insecure connection

The comments now provide a clear understanding of:
- What the code does (demonstrates different gRPC error scenarios)
- How the server is configured
- What each method is intended to demonstrate
- The expected behavior when exceptions are raised
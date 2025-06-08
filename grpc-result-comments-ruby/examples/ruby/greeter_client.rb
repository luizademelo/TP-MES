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

# Expand the current file's directory path and store it in this_dir
this_dir = File.expand_path(File.dirname(__FILE__))
# Construct the path to the lib directory by joining this_dir with 'lib'
lib_dir = File.join(this_dir, 'lib')
# Add lib_dir to the load path unless it's already included
$LOAD_PATH.unshift(lib_dir) unless $LOAD_PATH.include?(lib_dir)

# Require the gRPC library and the generated protobuf service file
require 'grpc'
require 'helloworld_services_pb'

# Main method that runs the gRPC client
def main
  # Get the user name from the first command line argument or default to 'world'
  user = ARGV.size > 0 ?  ARGV[0] : 'world'
  # Get the hostname from the second command line argument or default to 'localhost:50051'
  hostname = ARGV.size > 1 ?  ARGV[1] : 'localhost:50051'
  
  # Create a new insecure gRPC channel stub to communicate with the server
  stub = Helloworld::Greeter::Stub.new(hostname, :this_channel_is_insecure)
  
  begin
    # Call the say_hello RPC method with the user name and print the response
    message = stub.say_hello(Helloworld::HelloRequest.new(name: user)).message
    p "Greeting: #{message}"
  rescue GRPC::BadStatus => e
    # Handle any gRPC errors and print the error message
    abort "ERROR: #{e.message}"
  end
end

# Execute the main method
main
```

The comments explain:
1. The file path setup and library loading
2. The main method's purpose and flow
3. How command line arguments are processed with defaults
4. The gRPC stub creation and RPC call
5. Error handling for gRPC-specific exceptions
6. The overall execution flow

The comments are placed strategically to explain both the high-level purpose and specific implementation details while maintaining readability.
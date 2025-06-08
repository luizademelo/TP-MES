Here's the commented version of the code:

```c++
#!/usr/bin/env ruby

# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Set up the Ruby load path to include necessary library directories
this_dir = File.expand_path(File.dirname(__FILE__))
protos_lib_dir = File.join(this_dir, 'lib')
grpc_lib_dir = File.join(File.dirname(this_dir), 'lib')
# Add directories to $LOAD_PATH if they're not already included
$LOAD_PATH.unshift(grpc_lib_dir) unless $LOAD_PATH.include?(grpc_lib_dir)
$LOAD_PATH.unshift(protos_lib_dir) unless $LOAD_PATH.include?(protos_lib_dir)
$LOAD_PATH.unshift(this_dir) unless $LOAD_PATH.include?(this_dir)

# Require necessary libraries
require 'grpc'
require 'end2end_common'

# Creates and returns server credentials for secure connections
# The credentials are loaded from test certificate files
def create_server_creds
  # Determine the test data directory path
  test_root = File.join(File.dirname(__FILE__), '..', 'spec', 'testdata')
  GRPC.logger.info("test root: #{test_root}")
  
  # List of certificate files needed for secure connection
  files = ['ca.pem', 'server1.key', 'server1.pem']
  
  # Read all certificate files
  creds = files.map { |f| File.open(File.join(test_root, f)).read }
  
  # Create and return new server credentials
  GRPC::Core::ServerCredentials.new(
    creds[0],  # CA certificate
    [{ private_key: creds[1], cert_chain: creds[2] }],  # Private key and certificate chain
    true)  # Force client authentication
end

# Main execution function
def main
  secure = false  # Default to insecure connection
  
  # Parse command line options
  OptionParser.new do |opts|
    opts.on('--secure') do
      secure = true  # Set secure flag if --secure option is provided
    end
  end.parse!
  
  STDERR.puts 'start server'
  
  # Initialize server based on security requirements
  if secure
    # Create secure server with credentials
    server_runner = ServerRunner.new(SecureEchoServerImpl)
    server_runner.server_creds = create_server_creds
  else
    # Create insecure server
    server_runner = ServerRunner.new(EchoServerImpl)
  end
  
  # Start the server and get its port
  server_port = server_runner.run
  p server_port  # Print server port
  
  # Keep server running until input is received
  STDIN.read
  
  # Stop the server when input is received
  server_runner.stop
end

# Execute main function
main
```

Key improvements in the comments:
1. Added explanation of the load path setup
2. Documented the purpose of `create_server_creds` function
3. Explained the certificate file loading process
4. Detailed the main execution flow and option parsing
5. Clarified the secure vs insecure server creation
6. Explained the server lifecycle (start, wait, stop)
7. Added comments for important variables and parameters

The comments now provide a clear understanding of the code's purpose and functionality while maintaining readability.
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

# Load common functionality for end-to-end tests
require_relative './end2end_common'

# Main function that orchestrates the end-to-end test scenario
def main
  # Start the gRPC server with an echo service implementation
  STDERR.puts 'start server'
  echo_service = EchoServerImpl.new  # Creates new echo service instance
  server_runner = ServerRunner.new(echo_service)  # Wraps server in runner
  server_port = server_runner.run  # Starts server and gets its port
  
  # Start the client process that will communicate with the server
  STDERR.puts 'start client'
  client_controller = ClientController.new(
    'sig_handling_client.rb', server_port)  # Controls client process
  
  # Test signal handling by sending signals to client process 5 times
  count = 0
  while count < 5
    # Make an RPC call to the echo service
    client_controller.stub.do_echo_rpc(
      ClientControl::DoEchoRpcRequest.new(request: 'hello'))
    
    # Send termination signals to client process to test handling
    Process.kill('SIGTERM', client_controller.client_pid)  # Graceful shutdown
    Process.kill('SIGINT', client_controller.client_pid)   # Interrupt signal
    
    count += 1
  end
  
  # Cleanup: shutdown client and verify it exited successfully
  client_controller.stub.shutdown(ClientControl::Void.new)  # Request shutdown
  Process.wait(client_controller.client_pid)  # Wait for client to terminate
  
  # Verify client exited with success status code (0)
  fail "client exit code: #{$CHILD_STATUS}" unless $CHILD_STATUS.to_i.zero?
  
  # Stop the server after test completion
  server_runner.stop
end

# Execute the main function
main
```

Key aspects explained in the comments:
1. The overall purpose as an end-to-end test for signal handling
2. The server setup process with an echo service
3. The client control mechanism
4. The test loop that verifies signal handling
5. The cleanup and verification phase
6. Each significant operation is commented to explain its purpose

The comments maintain a balance between explaining the what and the why, while avoiding unnecessary comments for self-explanatory code.
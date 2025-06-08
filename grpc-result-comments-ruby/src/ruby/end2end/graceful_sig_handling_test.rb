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

# Main function to test graceful shutdown behavior of client when receiving SIGINT
def main
  # Start the gRPC echo server
  STDERR.puts 'start server'
  echo_service = EchoServerImpl.new
  server_runner = ServerRunner.new(echo_service)
  server_port = server_runner.run
  
  # Start the gRPC client that will connect to the server
  STDERR.puts 'start client'
  client_controller = ClientController.new(
    'graceful_sig_handling_client.rb', server_port)

  # Perform an echo RPC call to verify basic functionality
  client_controller.stub.do_echo_rpc(
    ClientControl::DoEchoRpcRequest.new(request: 'hello'))
  
  # Send SIGINT to the client process to test graceful shutdown
  STDERR.puts 'killing client'
  Process.kill('SIGINT', client_controller.client_pid)
  
  # Wait for the client process to terminate
  Process.wait(client_controller.client_pid)
  
  # Check the exit status of the client process
  client_exit_status = $CHILD_STATUS
  if client_exit_status.exited?
    if client_exit_status.exitstatus != 0
      # Client did not exit cleanly (non-zero status)
      STDERR.puts 'Client did not close gracefully'
      exit(1)
    end
  else
    # Client was terminated by a signal or other non-exit condition
    STDERR.puts 'Client did not close gracefully'
    exit(1)
  end

  # If we get here, client shutdown gracefully
  STDERR.puts 'Client ended gracefully'
  
  # Stop the server
  server_runner.stop
end

# Execute the main function
main
```

Key comments added:
1. Explained the overall purpose of the script (testing graceful shutdown)
2. Documented each major section (server startup, client startup, RPC call)
3. Explained the signal handling and process termination checks
4. Added comments about the exit status verification
5. Noted the success case where client shuts down gracefully
6. Added a comment about the final server shutdown

The comments follow the flow of the code and explain both the what and the why of each significant operation.
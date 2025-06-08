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

# Load common end-to-end test functionality
require_relative './end2end_common'

def main
  # Start the gRPC server with EchoServer implementation
  STDERR.puts 'start server'
  server_runner = ServerRunner.new(EchoServerImpl)
  server_port = server_runner.run
  
  # Start the client process that will test channel closing behavior
  STDERR.puts 'start client'
  client_controller = ClientController.new(
    'channel_closing_client.rb', server_port)

  # Allow some time for client-server initialization
  sleep 3

  begin
    # Set a timeout for the entire client operation (120 seconds)
    Timeout.timeout(120) do
      loop do
        begin
          # Attempt to gracefully shutdown the client
          client_controller.stub.shutdown(ClientControl::Void.new)
          break
        rescue GRPC::BadStatus => e
          # Handle case where client isn't ready yet - log and retry
          STDERR.puts "control_stub.shutdown RPC received error:|#{e}|. " \
          "This could mean that that child process e.g. isn't running yet, " \
          "so we'll retry the RPC"
        end
      end
      # Wait for client process to complete
      Process.wait(client_controller.client_pid)
    end
  rescue Timeout::Error
    # Handle timeout case - kill the client process and clean up
    STDERR.puts "timeout wait for client pid #{client_controller.client_pid}"
    Process.kill('SIGKILL', client_controller.client_pid)
    Process.wait(client_controller.client_pid)
    STDERR.puts 'killed client child'
    raise 'Timed out waiting for client process. It likely freezes when a ' \
      'channel is closed while connectivity is watched'
  end

  # Verify client exit status
  client_exit_code = $CHILD_STATUS
  if client_exit_code != 0
    fail "channel closing client failed, exit code #{client_exit_code}"
  end

  # Clean up server resources
  server_runner.stop
end

# Execute the main function
main
```

Key comments added:
1. Explained the overall purpose of the script (testing channel closing behavior)
2. Documented each major section (server startup, client startup, shutdown sequence)
3. Added explanations for error handling and timeout logic
4. Clarified the purpose of the sleep and retry mechanism
5. Noted the cleanup phases for both client and server
6. Explained the exit code verification

The comments maintain a balance between explaining the what (the code's actions) and the why (the purpose behind those actions) while avoiding redundancy with the code itself.
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

# Load common end-to-end test functionality
require_relative './end2end_common'

# Controller class that handles channel shutdown requests from parent process
class ChannelClosingClientController < ClientControl::ClientController::Service
  # Initialize with a gRPC channel that can be closed
  def initialize(ch)
    @ch = ch  # Store the channel instance for later use
  end

  # Shutdown method that closes the channel when called
  # Returns an empty Void response as per protocol requirements
  def shutdown(_, _)
    @ch.close  # Close the gRPC channel
    ClientControl::Void.new  # Return empty response
  end
end

# Main execution method
def main
  # Variables to store ports received from command line
  parent_controller_port = ''
  server_port = ''
  
  # Parse command line options
  OptionParser.new do |opts|
    opts.on('--parent_controller_port=P', String) do |p|
      parent_controller_port = p  # Port for parent controller communication
    end
    opts.on('--server_port=P', String) do |p|
      server_port = p  # Port for server connection
    end
  end.parse!

  # Create insecure gRPC channel to test server
  ch = GRPC::Core::Channel.new("localhost:#{server_port}", {},
                               :this_channel_is_insecure)

  # Create test RPC server and start it in a separate thread
  srv = new_rpc_server_for_testing
  thd = Thread.new do
    # Bind server to an available port
    port = srv.add_http2_port('localhost:0', :this_port_is_insecure)
    # Report our controller port back to parent process
    report_controller_port_to_parent(parent_controller_port, port)
    # Register our channel closing controller
    srv.handle(ChannelClosingClientController.new(ch))
    # Start the server
    srv.run
  end

  # Main monitoring loop for channel connectivity
  loop do
    begin
      # Check current channel state and watch for changes
      state = ch.connectivity_state(true)
      # Wait for state change with 1 hour timeout
      ch.watch_connectivity_state(state, Time.now + 360)
    rescue RuntimeError => e
      # Expected error when channel is closed by controller
      STDERR.puts "(expected) error occurred: #{e.inspect}"
      break
    end
  end

  # Cleanup: stop server and wait for thread to complete
  srv.stop
  thd.join
end

# Start the program
main
```

Key aspects explained in the comments:
1. The overall purpose of the script (testing gRPC channel shutdown)
2. The ChannelClosingClientController class and its shutdown method
3. Command line argument parsing
4. gRPC channel and server setup
5. The connectivity monitoring loop
6. Expected error handling
7. Cleanup process

The comments aim to explain both the high-level purpose and the specific implementation details to help future maintainers understand and modify the code.
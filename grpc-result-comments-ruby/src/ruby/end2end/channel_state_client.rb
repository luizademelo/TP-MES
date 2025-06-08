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

# Main function that sets up and runs the gRPC connectivity test
def main
  # Initialize variables for ports
  parent_controller_port = ''
  server_port = ''
  
  # Parse command line arguments
  OptionParser.new do |opts|
    # Define option for parent controller port
    opts.on('--parent_controller_port=P', String) do |p|
      parent_controller_port = p
    end
    # Define option for server port
    opts.on('--server_port=P', String) do |p|
      server_port = p
    end
  end.parse!
  
  # Report controller port back to parent process (0 indicates success)
  report_controller_port_to_parent(parent_controller_port, 0)

  # Create an insecure gRPC channel to the specified server
  ch = GRPC::Core::Channel.new("localhost:#{server_port}", {},
                               :this_channel_is_insecure)

  # Continuously monitor channel connectivity state
  loop do
    # Get current connectivity state
    state = ch.connectivity_state
    
    # Watch for state changes with a timeout of 360 seconds
    ch.watch_connectivity_state(state, Time.now + 360)
  end
end

# Execute the main function
main
```

Key comments added:
1. Added description of the main function's purpose
2. Explained variable initialization
3. Documented the command line argument parsing
4. Explained the purpose of the port reporting
5. Added comments about the gRPC channel creation
6. Documented the connectivity monitoring loop
7. Explained each step within the monitoring loop

The comments provide clear explanations of:
- The overall purpose of the script (gRPC connectivity testing)
- The command line interface
- The gRPC channel setup
- The continuous connectivity monitoring mechanism
- Important function calls and their parameters
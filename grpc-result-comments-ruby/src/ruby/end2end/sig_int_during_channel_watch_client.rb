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

# Load common functionality for end-to-end tests
require_relative './end2end_common'

# Main entry point for the script
def main
  STDERR.puts 'sig_int_during_channel_watch_client.rb main'
  
  # Initialize variables for ports
  parent_controller_port = ''
  server_port = ''
  
  # Parse command line arguments
  OptionParser.new do |opts|
    # Option to specify parent controller port
    opts.on('--parent_controller_port=P', String) do |p|
      parent_controller_port = p
    end
    # Option to specify server port
    opts.on('--server_port=P', String) do |p|
      server_port = p
    end
  end.parse!

  # Set up SIGINT handler to exit cleanly
  trap('SIGINT') { exit 0 }
  STDERR.puts 'sig_int_during_channel_watch_client.rb: SIGINT trap has been set'

  # Notify parent process about controller port
  report_controller_port_to_parent(parent_controller_port, 0)

  # Create a background thread to monitor channel connectivity
  thd = Thread.new do
    # Create insecure channel to server
    child_thread_channel = GRPC::Core::Channel.new("localhost:#{server_port}",
                                                 {},
                                                 :this_channel_is_insecure)
    # Continuously monitor channel state
    loop do
      # Get current connectivity state
      state = child_thread_channel.connectivity_state(false)
      # Watch for state changes with 360 second timeout
      child_thread_channel.watch_connectivity_state(state, Time.now + 360)
    end
  end

  # In main thread, also monitor channel connectivity
  main_channel = GRPC::Core::Channel.new("localhost:#{server_port}",
                                       {},
                                       :this_channel_is_insecure)
  # Continuously monitor channel state
  loop do
    # Get current connectivity state
    state = main_channel.connectivity_state(false)
    # Watch for state changes with 360 second timeout
    main_channel.watch_connectivity_state(state, Time.now + 360)
  end

  # Wait for background thread to complete (though it runs indefinitely)
  thd.join
end

# Execute main function
main
```

Key aspects explained in the comments:
1. The script's purpose as a test client for gRPC channel connectivity monitoring
2. Command line argument parsing for ports
3. SIGINT signal handling for clean termination
4. Dual monitoring approach (main thread + background thread) of channel connectivity
5. The continuous monitoring loop checking channel state with timeout
6. Use of insecure channel connection for testing purposes

The comments aim to make clear:
- The overall flow of the program
- Why certain operations are being performed
- The relationship between different components
- The expected behavior of the connectivity monitoring
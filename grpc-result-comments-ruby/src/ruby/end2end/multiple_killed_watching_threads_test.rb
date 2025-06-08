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

# Require common end-to-end test functionality
require_relative './end2end_common'

# Ensure threads raise exceptions rather than silently failing
Thread.abort_on_exception = true

# Include GRPC connectivity state constants for readability
include GRPC::Core::ConnectivityStates

# Watches the connectivity state of a channel
# @param ch [GRPC::Core::Channel] The gRPC channel to monitor
# @param sleep_time [Numeric] Time to sleep before killing the watch thread
def watch_state(ch, sleep_time)
  # Create a new thread to watch the channel state
  thd = Thread.new do
    # Get current state (without trying to connect)
    state = ch.connectivity_state(false)
    # Verify initial state is IDLE
    fail "non-idle state: #{state}" unless state == IDLE
    # Watch for state changes from IDLE for up to 360 seconds
    ch.watch_connectivity_state(IDLE, Time.now + 360)
  end

  # Allow the watcher to run briefly before killing it
  sleep sleep_time
  thd.kill
end

# Runs multiple channel state watchers that will be killed after a short time
# @param num_threads [Integer] Number of watcher threads to create
# @param sleep_time [Numeric] Time to wait before killing each thread
def run_multiple_killed_watches(num_threads, sleep_time)
  channels = []
  num_threads.times do
    # Create an insecure channel to a non-existent host
    ch = GRPC::Core::Channel.new('phony_host',
                                 nil, :this_channel_is_insecure)
    # Start watching this channel's state
    watch_state(ch, sleep_time)
    channels << ch
  end

  # Verify all channels ended in expected states
  channels.each do |c|
    connectivity_state = c.connectivity_state(false)

    # Channel should either be in IDLE or FATAL_FAILURE state
    unless [FATAL_FAILURE, IDLE].include?(connectivity_state)
      fail "unexpected connectivity state: #{connectivity_state}"
    end
  end
end

# Main test function that runs the test scenarios
def main
  # Test case 1: 10 iterations with 0.1s delay
  STDERR.puts '10 iterations, sleep 0.1 before killing thread'
  run_multiple_killed_watches(10, 0.1)
  
  # Test case 2: 1000 iterations with 0.001s delay (stress test)
  STDERR.puts '1000 iterations, sleep 0.001 before killing thread'
  run_multiple_killed_watches(1000, 0.001)
end

# Execute the main test function
main
```

The comments explain:
1. The overall purpose of the script (testing gRPC channel state watching)
2. Each method's functionality and parameters
3. The test scenarios being executed
4. Important implementation details like thread handling and state verification
5. The expected behavior and failure conditions

The comments are designed to help future maintainers understand:
- What the code does
- Why it's structured the way it is
- What the expected behavior should be
- How to interpret the test cases
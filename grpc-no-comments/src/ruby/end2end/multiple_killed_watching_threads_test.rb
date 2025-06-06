#!/usr/bin/env ruby

# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require_relative './end2end_common'

Thread.abort_on_exception = true

include GRPC::Core::ConnectivityStates

def watch_state(ch, sleep_time)
  thd = Thread.new do
    state = ch.connectivity_state(false)
    fail "non-idle state: #{state}" unless state == IDLE
    ch.watch_connectivity_state(IDLE, Time.now + 360)
  end

  sleep sleep_time
  thd.kill
end

def run_multiple_killed_watches(num_threads, sleep_time)
  channels = []
  num_threads.times do
    ch = GRPC::Core::Channel.new('phony_host',
                                 nil, :this_channel_is_insecure)
    watch_state(ch, sleep_time)
    channels << ch
  end

  channels.each do |c|
    connectivity_state = c.connectivity_state(false)

    unless [FATAL_FAILURE, IDLE].include?(connectivity_state)
      fail "unexpected connectivity state: #{connectivity_state}"
    end
  end
end

def main
  STDERR.puts '10 iterations, sleep 0.1 before killing thread'
  run_multiple_killed_watches(10, 0.1)
  STDERR.puts '1000 iterations, sleep 0.001 before killing thread'
  run_multiple_killed_watches(1000, 0.001)
end

main

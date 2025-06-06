#!/usr/bin/env ruby

# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require_relative './end2end_common'

def main
  parent_controller_port = ''
  server_port = ''
  OptionParser.new do |opts|
    opts.on('--parent_controller_port=P', String) do |p|
      parent_controller_port = p
    end
    opts.on('--server_port=P', String) do |p|
      server_port = p
    end
  end.parse!
  report_controller_port_to_parent(parent_controller_port, 0)

  ch = GRPC::Core::Channel.new("localhost:#{server_port}", {},
                               :this_channel_is_insecure)

  loop do
    state = ch.connectivity_state
    ch.watch_connectivity_state(state, Time.now + 360)
  end
end

main

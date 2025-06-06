#!/usr/bin/env ruby

# Copyright 2018 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require_relative './end2end_common'
require 'objspace'

def main
  parent_controller_port = ''
  server_port = ''
  loop_count = 200

  OptionParser.new do |opts|
    opts.on('--parent_controller_port=P', String) do |p|
      parent_controller_port = p
    end
    opts.on('--server_port=P', String) do |p|
      server_port = p
    end
  end.parse!
  report_controller_port_to_parent(parent_controller_port, 0)

  loop_count.times do
    stub = Echo::EchoServer::Stub.new("localhost:#{server_port}", :this_channel_is_insecure)
    stub.echo(Echo::EchoRequest.new(request: 'client/child'))

    ObjectSpace.memsize_of_all
  end

  STDERR.puts "Succeeded in getting memory usage for #{loop_count} times"
end

main

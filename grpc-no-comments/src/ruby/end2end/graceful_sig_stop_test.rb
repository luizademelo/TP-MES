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

def main
  STDERR.puts 'start server'
  echo_service = EchoServerImpl.new
  server_runner = ServerRunner.new(echo_service)
  server_port = server_runner.run
  STDERR.puts 'start client'
  client_controller = ClientController.new(
    './graceful_sig_stop_client.rb', server_port)
  client_controller.stub.shutdown(ClientControl::Void.new)
  Process.wait(client_controller.client_pid)
  fail "client exit code: #{$CHILD_STATUS}" unless $CHILD_STATUS.to_i.zero?
  server_runner.stop
end

main

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
    'graceful_sig_handling_client.rb', server_port)

  client_controller.stub.do_echo_rpc(
    ClientControl::DoEchoRpcRequest.new(request: 'hello'))
  STDERR.puts 'killing client'
  Process.kill('SIGINT', client_controller.client_pid)
  Process.wait(client_controller.client_pid)
  client_exit_status = $CHILD_STATUS
  if client_exit_status.exited?
    if client_exit_status.exitstatus != 0
      STDERR.puts 'Client did not close gracefully'
      exit(1)
    end
  else
    STDERR.puts 'Client did not close gracefully'
    exit(1)
  end

  STDERR.puts 'Client ended gracefully'
  server_runner.stop
end

main

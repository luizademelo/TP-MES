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
  server_runner = ServerRunner.new(EchoServerImpl)
  server_port = server_runner.run
  STDERR.puts 'start client'
  client_controller = ClientController.new(
    'forking_client_client.rb', server_port)

  begin
    Timeout.timeout(180) do
      Process.wait(client_controller.client_pid)
    end
  rescue Timeout::Error
    STDERR.puts "timeout wait for client pid #{client_controller.client_pid}"
    Process.kill('SIGKILL', client_controller.client_pid)
    Process.wait(client_controller.client_pid)
    STDERR.puts 'killed client child'
    raise 'Timed out waiting for client process. ' \
      'It likely freezes when requiring grpc, then forking, then using grpc '
  end

  client_exit_code = $CHILD_STATUS
  if client_exit_code != 0
    fail "forking client client failed, exit code #{client_exit_code}"
  end

  server_runner.stop
end

main

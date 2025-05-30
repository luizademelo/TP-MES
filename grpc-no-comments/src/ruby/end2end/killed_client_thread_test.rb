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

class SleepingEchoServerImpl < Echo::EchoServer::Service
  def initialize(received_rpc_callback)
    @received_rpc_callback = received_rpc_callback
  end

  def echo(echo_req, _)
    @received_rpc_callback.call

    sleep
    Echo::EchoReply.new(response: echo_req.request)
  end
end

def main
  STDERR.puts 'start server'

  received_rpc = false
  received_rpc_mu = Mutex.new
  received_rpc_cv = ConditionVariable.new
  received_rpc_callback = proc do
    received_rpc_mu.synchronize do
      received_rpc = true
      received_rpc_cv.signal
    end
  end

  service_impl = SleepingEchoServerImpl.new(received_rpc_callback)

  rpc_server_args = { poll_period: 0, pool_keep_alive: 0 }
  server_runner = ServerRunner.new(service_impl, rpc_server_args: rpc_server_args)
  server_port = server_runner.run
  STDERR.puts 'start client'
  client_controller = ClientController.new(
    'killed_client_thread_client.rb', server_port)

  received_rpc_mu.synchronize do
    received_rpc_cv.wait(received_rpc_mu) until received_rpc
  end

  Process.kill('SIGTERM', client_controller.client_pid)
  STDERR.puts 'sent shutdown'

  begin
    Timeout.timeout(120) do
      Process.wait(client_controller.client_pid)
    end
  rescue Timeout::Error
    STDERR.puts "timeout wait for client pid #{client_controller.client_pid}"
    Process.kill('SIGKILL', client_controller.client_pid)
    Process.wait(client_controller.client_pid)
    STDERR.puts 'killed client child'
    raise 'Timed out waiting for client process. ' \
      'It likely freezes when killed while in the middle of an rpc'
  end

  client_exit_code = $CHILD_STATUS
  if client_exit_code.termsig != 15
    fail 'expected client exit from SIGTERM ' \
      "but got child status: #{client_exit_code}"
  end

  server_runner.stop
end

main

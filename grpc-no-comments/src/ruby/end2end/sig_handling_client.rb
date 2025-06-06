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

class SigHandlingClientController < ClientControl::ClientController::Service
  def initialize(srv, stub)
    @srv = srv
    @stub = stub
  end

  def do_echo_rpc(req, _)
    response = @stub.echo(Echo::EchoRequest.new(request: req.request))
    fail 'bad response' unless response.response == req.request
    ClientControl::Void.new
  end

  def shutdown(_, _)

    @shutdown_thread = Thread.new do
      @srv.stop
    end
    ClientControl::Void.new
  end

  def join_shutdown_thread
    @shutdown_thread.join
  end
end

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

  Signal.trap('TERM') do
    STDERR.puts 'SIGTERM received'
  end

  Signal.trap('INT') do
    STDERR.puts 'SIGINT received'
  end

  srv = new_rpc_server_for_testing(poll_period: 3)
  port = srv.add_http2_port('localhost:0',
                            :this_port_is_insecure)
  stub = Echo::EchoServer::Stub.new("localhost:#{server_port}",
                                    :this_channel_is_insecure)
  control_service = SigHandlingClientController.new(srv, stub)
  srv.handle(control_service)
  server_thread = Thread.new do
    srv.run
  end
  srv.wait_till_running

  report_controller_port_to_parent(parent_controller_port, port)
  server_thread.join
  control_service.join_shutdown_thread
end

main

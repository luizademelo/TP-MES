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

# Set up Ruby load paths to include local libraries
this_dir = File.expand_path(File.dirname(__FILE__))
protos_lib_dir = File.join(this_dir, 'lib')
grpc_lib_dir = File.join(File.dirname(this_dir), 'lib')
$LOAD_PATH.unshift(grpc_lib_dir) unless $LOAD_PATH.include?(grpc_lib_dir)
$LOAD_PATH.unshift(protos_lib_dir) unless $LOAD_PATH.include?(protos_lib_dir)
$LOAD_PATH.unshift(this_dir) unless $LOAD_PATH.include?(this_dir)

# Require necessary libraries
require 'grpc'                  # gRPC library
require 'echo_services_pb'      # Protobuf generated echo service
require 'client_control_services_pb' # Protobuf generated client control service
require 'socket'                # Socket library
require 'optparse'              # Command line option parsing
require 'thread'                # Thread support
require 'timeout'               # Timeout functionality
require 'English'               # Access to $ERROR_INFO etc.
require_relative '../spec/support/helpers' # Helper methods

include GRPC::Spec::Helpers

# A simple mutable value container class
class MutableValue
  attr_accessor :value

  def initialize(value)
    @value = value
  end
end

# Implementation of the Echo service
class EchoServerImpl < Echo::EchoServer::Service
  # Simple echo implementation that returns the same message it receives
  def echo(echo_req, _)
    Echo::EchoReply.new(response: echo_req.request)
  end
end

# Secure version of Echo service that requires authorization
class SecureEchoServerImpl < Echo::EchoServer::Service
  # Echo implementation that checks for authorization header
  def echo(echo_req, call)
    unless call.metadata["authorization"] == 'test'
      fail "expected authorization header with value: test"
    end
    Echo::EchoReply.new(response: echo_req.request)
  end
end

# Class to manage running a gRPC server
class ServerRunner
  attr_accessor :server_creds

  # Initialize with service implementation and optional server arguments
  def initialize(service_impl, rpc_server_args: {})
    @service_impl = service_impl
    @rpc_server_args = rpc_server_args
    @server_creds = :this_port_is_insecure  # Default to insecure connection
  end

  # Start the server and return the port it's running on
  def run
    @srv = new_rpc_server_for_testing(@rpc_server_args)
    port = @srv.add_http2_port('0.0.0.0:0', @server_creds)  # Bind to any available port
    @srv.handle(@service_impl)

    # Start server in a new thread
    @thd = Thread.new do
      @srv.run
    end
    @srv.wait_till_running
    port
  end

  # Stop the server gracefully
  def stop
    @srv.stop
    @thd.join
    fail 'server not stopped' unless @srv.stopped?
  end
end

# Controller for managing client processes
class ClientController < ClientControl::ParentController::Service
  attr_reader :stub, :client_pid

  # Initialize controller with client main file and server port
  def initialize(client_main, server_port)
    this_dir = File.expand_path(File.dirname(__FILE__))
    client_path = File.join(this_dir, client_main)
    
    # Set up server for client control
    @server = new_rpc_server_for_testing(poll_period: 3)
    port = @server.add_http2_port('localhost:0', :this_port_is_insecure)
    
    # Start server in a new thread
    server_thread = Thread.new do
      @server.handle(self)
      @server.run
    end
    @server.wait_till_running
    
    # Setup synchronization variables for client port communication
    @client_controller_port_mu = Mutex.new
    @client_controller_port_cv = ConditionVariable.new
    @client_controller_port = nil
    
    # Spawn client process
    @client_pid = Process.spawn(RbConfig.ruby,
                              client_path,
                              "--parent_controller_port=#{port}",
                              "--server_port=#{server_port}")
    # Wait for client to report its control port with timeout
    begin
      Timeout.timeout(60) do
        @client_controller_port_mu.synchronize do
          while @client_controller_port.nil?
            @client_controller_port_cv.wait(@client_controller_port_mu)
          end
        end
      end
    rescue => e
      fail "timeout waiting for child process to report port. error: #{e}"
    end
    
    # Stop the control server and create client stub
    @server.stop
    server_thread.join
    @stub = ClientControl::ClientController::Stub.new(
      "localhost:#{@client_controller_port}", :this_channel_is_insecure)
  end

  # RPC method to receive client's control port
  def set_client_controller_port(req, _)
    @client_controller_port_mu.synchronize do
      unless @client_controller_port.nil?
        fail 'client controller port already set'
      end
      @client_controller_port = req.port
      @client_controller_port_cv.broadcast
    end
    ClientControl::Void.new
  end
end

# Helper method to report client controller port back to parent process
def report_controller_port_to_parent(parent_controller_port, client_controller_port)
  unless parent_controller_port.to_i > 0
    fail "bad parent control port: |#{parent_controller_port}|"
  end
  stub = ClientControl::ParentController::Stub.new(
    "localhost:#{parent_controller_port.to_i}", :this_channel_is_insecure)
  m = ClientControl::Port.new
  m.port = client_controller_port.to_i
  stub.set_client_controller_port(m, deadline: Time.now + 10)
end

# Helper method to add logging around actions
def with_logging(action)
  STDERR.puts "#{action}: begin (pid=#{Process.pid})"
  yield
  STDERR.puts "#{action}: done (pid=#{Process.pid})"
end
```
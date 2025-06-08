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

# Set up load paths for required libraries
this_dir = File.expand_path(File.dirname(__FILE__))
lib_dir = File.join(File.dirname(this_dir), 'lib')
# Add lib directory to load path if not already present
$LOAD_PATH.unshift(lib_dir) unless $LOAD_PATH.include?(lib_dir)
# Add current directory to load path if not already present
$LOAD_PATH.unshift(this_dir) unless $LOAD_PATH.include?(this_dir)

# Require necessary libraries and protobuf generated files
require 'grpc'
require 'qps-common'
require 'src/proto/grpc/testing/messages_pb'
require 'src/proto/grpc/testing/benchmark_service_services_pb'
require 'src/proto/grpc/testing/stats_pb'

# Implementation of the BenchmarkService gRPC service
class BenchmarkServiceImpl < Grpc::Testing::BenchmarkService::Service
  # Handles unary RPC calls
  # @param req [Grpc::Testing::SimpleRequest] The request object
  # @param _call [GRPC::ActiveCall] The call object (unused)
  # @return [Grpc::Testing::SimpleResponse] Response with payload of requested size
  def unary_call(req, _call)
    sr = Grpc::Testing::SimpleResponse
    pl = Grpc::Testing::Payload
    # Create response with null-filled payload of requested size
    sr.new(payload: pl.new(body: nulls(req.response_size)))
  end

  # Handles streaming RPC calls
  # @param reqs [Enumerable] Stream of incoming requests
  # @return [Enumerator] Enumerator that implements ping-pong streaming behavior
  def streaming_call(reqs)
    PingPongEnumerator.new(reqs).each_item
  end
end

# Class representing the benchmark gRPC server
class BenchmarkServer
  # Initializes the benchmark server
  # @param config [Hash] Server configuration including security parameters
  # @param port [Integer] Port number to listen on
  def initialize(config, port)
    # Set up server credentials based on security configuration
    if config.security_params
      certs = load_test_certs
      cred = GRPC::Core::ServerCredentials.new(
        nil, [{private_key: certs[1], cert_chain: certs[2]}], false)
    else
      cred = :this_port_is_insecure
    end

    # TODO: @apolcyn, if scenario config increases total outstanding

    # Create gRPC server with large thread pool and queue size
    @server = GRPC::RpcServer.new(pool_size: 1024, max_waiting_requests: 1024)
    # Start listening on specified port
    @port = @server.add_http2_port("0.0.0.0:" + port.to_s, cred)
    # Register service implementation
    @server.handle(BenchmarkServiceImpl.new)
    # Record start time for statistics
    @start_time = Time.now
    # Start server in a new thread
    t = Thread.new {
      @server.run
    }
    t.abort_on_exception  # Crash if server thread fails
  end

  # Records server statistics
  # @param reset [Boolean] Whether to reset the timer after recording
  # @return [Grpc::Testing::ServerStats] Statistics including elapsed time
  def mark(reset)
    s = Grpc::Testing::ServerStats.new(time_elapsed:
                                       (Time.now-@start_time).to_f)
    @start_time = Time.now if reset
    s
  end

  # Gets the port number the server is listening on
  # @return [Integer] Port number
  def get_port
    @port
  end

  # Stops the server
  def stop
    @server.stop
  end
end
```
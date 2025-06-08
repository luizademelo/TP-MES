Here's the commented version of the code:

```c++
# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'spec_helper'

# Simple message class for echo service testing
class EchoMsg
  attr_reader :msg

  # Initialize with an optional message string
  def initialize(msg: '')
    @msg = msg
  end

  # Class method to serialize EchoMsg object to string
  def self.marshal(o)
    o.msg
  end

  # Class method to deserialize string into EchoMsg object
  def self.unmarshal(msg)
    EchoMsg.new(msg: msg)
  end
end

# gRPC echo service implementation with various RPC patterns
class EchoService
  include GRPC::GenericService
  
  # Define RPC methods with their input/output types:
  # - Simple request-response
  # - Client streaming
  # - Server streaming
  # - Bidirectional streaming
  # - Unimplemented client streaming (for testing)
  rpc :an_rpc, EchoMsg, EchoMsg
  rpc :a_client_streaming_rpc, stream(EchoMsg), EchoMsg
  rpc :a_server_streaming_rpc, EchoMsg, stream(EchoMsg)
  rpc :a_bidi_rpc, stream(EchoMsg), stream(EchoMsg)
  rpc :a_client_streaming_rpc_unimplemented, stream(EchoMsg), EchoMsg
  
  attr_reader :received_md
  attr_accessor :on_call_started

  # Initialize with optional trailing metadata
  def initialize(**kw)
    @trailing_metadata = kw
    @received_md = []  # Stores received metadata
    @on_call_started = nil  # Optional callback when call starts
  end

  # Simple request-response RPC implementation
  def an_rpc(req, call)
    GRPC.logger.info('echo service received a request')
    on_call_started&.call(call)  # Trigger callback if set
    call.output_metadata.update(@trailing_metadata)
    @received_md << call.metadata unless call.metadata.nil?  # Store metadata
    req  # Echo back the request
  end

  # Client streaming RPC implementation
  def a_client_streaming_rpc(call)
    call.output_metadata.update(@trailing_metadata)
    # Log each received message from client stream
    call.each_remote_read.each do |r|
      GRPC.logger.info(r)
    end
    EchoMsg.new  # Return empty response
  end

  # Server streaming RPC implementation
  def a_server_streaming_rpc(_req, call)
    call.output_metadata.update(@trailing_metadata)
    # Return array of messages to be streamed to client
    [EchoMsg.new, EchoMsg.new]
  end

  # Bidirectional streaming RPC implementation
  def a_bidi_rpc(requests, call)
    call.output_metadata.update(@trailing_metadata)
    # Log each received message from client stream
    requests.each do |r|
      GRPC.logger.info(r)
    end
    # Return array of messages to be streamed to client
    [EchoMsg.new, EchoMsg.new]
  end
end

# Auto-generated client stub class for EchoService
EchoStub = EchoService.rpc_stub_class

# Server-side interceptor for testing purposes
class TestServerInterceptor < GRPC::ServerInterceptor
  # Intercept request-response calls
  def request_response(request:, call:, method:)
    GRPC.logger.info("Received request/response call at method #{method}" \
      " with request #{request} for call #{call}")
    call.output_metadata[:interc] = 'from_request_response'
    GRPC.logger.info("[GRPC::Ok] (#{method.owner.name}.#{method.name})")
    yield
  end

  # Intercept client streaming calls
  def client_streamer(call:, method:)
    call.output_metadata[:interc] = 'from_client_streamer'
    # Log each message from client stream
    call.each_remote_read.each do |r|
      GRPC.logger.info("In interceptor: #{r}")
    end
    GRPC.logger.info(
      "Received client streamer call at method #{method} for call #{call}"
    )
    yield
  end

  # Intercept server streaming calls
  def server_streamer(request:, call:, method:)
    GRPC.logger.info("Received server streamer call at method #{method} with request" \
      " #{request} for call #{call}")
    call.output_metadata[:interc] = 'from_server_streamer'
    yield
  end

  # Intercept bidirectional streaming calls
  def bidi_streamer(requests:, call:, method:)
    # Log each message from client stream
    requests.each do |r|
      GRPC.logger.info("Bidi request: #{r}")
    end
    GRPC.logger.info("Received bidi streamer call at method #{method} with requests" \
      " #{requests} for call #{call}")
    call.output_metadata[:interc] = 'from_bidi_streamer'
    yield
  end
end

# Client-side interceptor for testing purposes
class TestClientInterceptor < GRPC::ClientInterceptor
  # Intercept request-response calls
  def request_response(request:, call:, method:, metadata: {})
    GRPC.logger.info("Intercepted request/response call at method #{method}" \
      " with request #{request} for call #{call}" \
      " and metadata: #{metadata}")
    metadata['foo'] = 'bar_from_request_response'
    yield
  end

  # Intercept client streaming calls
  def client_streamer(requests:, call:, method:, metadata: {})
    GRPC.logger.info("Received client streamer call at method #{method}" \
      " with requests #{requests} for call #{call}" \
      " and metadata: #{metadata}")
    # Log each message being sent
    requests.each do |r|
      GRPC.logger.info("In client interceptor: #{r}")
    end
    metadata['foo'] = 'bar_from_client_streamer'
    yield
  end

  # Intercept server streaming calls
  def server_streamer(request:, call:, method:, metadata: {})
    GRPC.logger.info("Received server streamer call at method #{method}" \
      " with request #{request} for call #{call}" \
      " and metadata: #{metadata}")
    metadata['foo'] = 'bar_from_server_streamer'
    yield
  end

  # Intercept bidirectional streaming calls
  def bidi_streamer(requests:, call:, method:, metadata: {})
    GRPC.logger.info("Received bidi streamer call at method #{method}" \
      "with requests #{requests} for call #{call}" \
      " and metadata: #{metadata}")
    # Log each message being sent
    requests.each do |r|
      GRPC.logger.info("In client interceptor: #{r}")
    end
    metadata['foo'] = 'bar_from_bidi_streamer'
    yield
  end
end
```
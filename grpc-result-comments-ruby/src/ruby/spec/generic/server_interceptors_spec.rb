Here's the commented version of the code:

```ruby
# Copyright 2017 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# This spec file tests server interceptors functionality in gRPC
require 'spec_helper'

# Test suite for Server Interceptors
describe 'Server Interceptors' do
  # Setup test variables:
  # - interceptor: Test interceptor instance
  # - request: Sample request message
  # - trailing_metadata: Empty hash for server metadata
  # - service: Echo service instance with trailing metadata
  # - interceptors: Empty array for interceptors
  let(:interceptor) { TestServerInterceptor.new }
  let(:request) { EchoMsg.new }
  let(:trailing_metadata) { {} }
  let(:service) { EchoService.new(**trailing_metadata) }
  let(:interceptors) { [] }

  # Before each test, build an RPC server with given interceptors
  before(:each) do
    build_rpc_server(server_opts: { interceptors: interceptors })
  end

  # Context: When a server interceptor is added
  context 'when a server interceptor is added' do
    let(:interceptors) { [interceptor] }  # Add the test interceptor
    let(:client_metadata) { { client_md: 'test' } }  # Client metadata for testing
    let(:client_call_opts) { { metadata: client_metadata, return_op: true } }  # Call options

    # Test request/response call behavior
    context 'with a request/response call' do
      let(:trailing_metadata) { { server_om: 'from_request_response' } }  # Server metadata

      # Test that the interceptor is called for request/response calls
      it 'should be called', server: true do
        expect(interceptor).to receive(:request_response)
          .once.and_call_original

        run_services_on_server(@server, services: [service]) do
          stub = build_insecure_stub(EchoStub)
          expect(stub.an_rpc(request)).to be_a(EchoMsg)
        end
      end

      # Test that the interceptor can modify trailing metadata
      it 'can modify trailing metadata', server: true do
        expect(interceptor).to receive(:request_response)
          .once.and_call_original

        run_services_on_server(@server, services: [service]) do
          stub = build_insecure_stub(EchoStub)
          expect_any_instance_of(GRPC::ActiveCall).to(
            receive(:request_response).with(request, metadata: client_metadata)
              .once.and_call_original
          )
          op = stub.an_rpc(request, client_call_opts)
          msg = op.execute
          expect(op.trailing_metadata).to eq(
            'interc' => 'from_request_response',
            'server_om' => 'from_request_response'
          )
          expect(msg).to be_a(EchoMsg)
        end
      end
    end

    # Test client streaming call behavior
    context 'with a client streaming call' do
      let(:trailing_metadata) { { server_om: 'from_client_streamer' } }  # Server metadata
      let(:requests) { [EchoMsg.new, EchoMsg.new] }  # Multiple requests for streaming

      # Test that the interceptor is called for client streaming calls
      it 'should be called', server: true do
        expect(interceptor).to receive(:client_streamer)
          .once.and_call_original

        run_services_on_server(@server, services: [service]) do
          stub = build_insecure_stub(EchoStub)
          expect(stub.a_client_streaming_rpc(requests)).to be_a(EchoMsg)
        end
      end

      # Test that the interceptor can modify trailing metadata in client streaming
      it 'can modify trailing metadata', server: true do
        expect(interceptor).to receive(:client_streamer)
          .once.and_call_original

        run_services_on_server(@server, services: [service]) do
          stub = build_insecure_stub(EchoStub)
          expect_any_instance_of(GRPC::ActiveCall).to(
            receive(:client_streamer).with(requests)
              .once.and_call_original
          )
          op = stub.a_client_streaming_rpc(requests, client_call_opts)
          msg = op.execute
          expect(op.trailing_metadata).to eq(
            'interc' => 'from_client_streamer',
            'server_om' => 'from_client_streamer'
          )
          expect(msg).to be_a(EchoMsg)
        end
      end
    end

    # Test server streaming call behavior
    context 'with a server streaming call' do
      let(:trailing_metadata) { { server_om: 'from_server_streamer' } }  # Server metadata
      let(:request) { EchoMsg.new }  # Single request for server streaming

      # Test that the interceptor is called for server streaming calls
      it 'should be called', server: true do
        expect(interceptor).to receive(:server_streamer)
          .once.and_call_original

        run_services_on_server(@server, services: [service]) do
          stub = build_insecure_stub(EchoStub)
          responses = stub.a_server_streaming_rpc(request)
          responses.each do |r|
            expect(r).to be_a(EchoMsg)
          end
        end
      end

      # Test that the interceptor can modify trailing metadata in server streaming
      it 'can modify trailing metadata', server: true do
        expect(interceptor).to receive(:server_streamer)
          .once.and_call_original

        run_services_on_server(@server, services: [service]) do
          stub = build_insecure_stub(EchoStub)
          expect_any_instance_of(GRPC::ActiveCall).to(
            receive(:server_streamer).with(request)
              .once.and_call_original
          )
          op = stub.a_server_streaming_rpc(request, client_call_opts)
          responses = op.execute
          responses.each do |r|
            expect(r).to be_a(EchoMsg)
          end
          expect(op.trailing_metadata).to eq(
            'interc' => 'from_server_streamer',
            'server_om' => 'from_server_streamer'
          )
        end
      end
    end

    # Test bidirectional streaming call behavior
    context 'with a bidi call' do
      let(:trailing_metadata) { { server_om: 'from_bidi_streamer' } }  # Server metadata
      let(:requests) { [EchoMsg.new, EchoMsg.new] }  # Multiple requests for bidi streaming

      # Test that the interceptor is called for bidirectional calls
      it 'should be called', server: true do
        expect(interceptor).to receive(:bidi_streamer)
          .once.and_call_original

        run_services_on_server(@server, services: [service]) do
          stub = build_insecure_stub(EchoStub)
          responses = stub.a_bidi_rpc(requests)
          responses.each do |r|
            expect(r).to be_a(EchoMsg)
          end
        end
      end

      # Test that the interceptor can modify trailing metadata in bidirectional calls
      it 'can modify trailing metadata', server: true do
        expect(interceptor).to receive(:bidi_streamer)
          .once.and_call_original

        run_services_on_server(@server, services: [service]) do
          stub = build_insecure_stub(EchoStub)
          expect_any_instance_of(GRPC::ActiveCall).to(
            receive(:bidi_streamer).with(requests)
              .once.and_call_original
          )
          op = stub.a_bidi_rpc(requests, client_call_opts)
          responses = op.execute
          responses.each do |r|
            expect(r).to be_a(EchoMsg)
          end
          expect(op.trailing_metadata).to eq(
            'interc' => 'from_bidi_streamer',
            'server_om' => 'from_bidi_streamer'
          )
        end
      end
    end
  end

  # Context: When multiple interceptors are added
  context 'when multiple interceptors are added' do
    let(:interceptor2) { TestServerInterceptor.new }  # Second interceptor
    let(:interceptor3) { TestServerInterceptor.new }  # Third interceptor
    let(:interceptors) do
      [
        interceptor,
        interceptor2,
        interceptor3
      ]
    end

    # Test that each interceptor is called in sequence
    it 'each should be called', server: true do
      expect(interceptor).to receive(:request_response)
        .once.and_call_original
      expect(interceptor2).to receive(:request_response)
        .once.and_call_original
      expect(interceptor3).to receive(:request_response)
        .once.and_call_original

      run_services_on_server(@server, services: [service]) do
        stub = build_insecure_stub(EchoStub)
        expect(stub.an_rpc(request)).to be_a(EchoMsg)
      end
    end
  end

  # Context: When no interceptor is added
  context 'when an interceptor is not added' do
    # Test that the interceptor is not called when not added to server
    it 'should not be called', server: true do
      expect(interceptor).to_not receive(:call)

      run_services_on_server(@server, services: [service]) do
        stub = build_insecure_stub(EchoStub)
        expect(stub.an_rpc(request)).to be_a(EchoMsg)
      end
    end
  end
end
```

The comments explain:
1. The overall purpose of the test file
2. The setup for each test case
3. The purpose of each test context and individual test
4. The expected behavior being verified
5. The different types of gRPC calls being tested (unary, client streaming, server streaming, bidirectional)
6. The interceptor behavior being verified in each case

The comments are focused on explaining the why behind the code rather than just describing what the code does. They provide context for future maintainers about the test scenarios and expected behaviors.
Here's the commented version of the code:

```c++
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
require 'spec_helper'

# Loads test certificates from the testdata directory
def load_test_certs
  test_root = File.join(File.dirname(File.dirname(__FILE__)), 'testdata')
  files = ['ca.pem', 'server1.key', 'server1.pem']
  files.map { |f| File.open(File.join(test_root, f)).read }
end

# Compares wanted metadata with received metadata
def check_md(wanted_md, received_md)
  wanted_md.zip(received_md).each do |w, r|
    w.each do |key, value|
      expect(r[key]).to eq(value)
    end
  end
end

# Empty service class for testing
class EmptyService
  include GRPC::GenericService
end

# Service with RPC declared but not implemented
class NoRpcImplementation
  include GRPC::GenericService
  rpc :an_rpc, EchoMsg, EchoMsg
end

# Service that intentionally fails RPCs
class FailingService
  include GRPC::GenericService
  rpc :an_rpc, EchoMsg, EchoMsg
  attr_reader :details, :code, :md

  def initialize(_default_var = 'ignored')
    @details = 'app error'
    @code = 3
    @md = { 'failed_method' => 'an_rpc' }
  end

  def an_rpc(_req, _call)
    fail GRPC::BadStatus.new(@code, @details, @md)
  end
end

# Stub class for FailingService
FailingStub = FailingService.rpc_stub_class

# Service that introduces delays in RPC processing
class SlowService
  include GRPC::GenericService
  rpc :an_rpc, EchoMsg, EchoMsg
  rpc :a_server_streaming_rpc, EchoMsg, stream(EchoMsg)
  attr_reader :received_md, :delay

  def initialize(_default_var = 'ignored')
    @delay = 0.25
    @received_md = []
  end

  def an_rpc(req, call)
    GRPC.logger.info("starting a slow #{@delay} rpc")
    sleep @delay
    @received_md << call.metadata unless call.metadata.nil?
    req
  end

  def a_server_streaming_rpc(_, call)
    GRPC.logger.info("starting a slow #{@delay} server streaming rpc")
    sleep @delay
    @received_md << call.metadata unless call.metadata.nil?
    [EchoMsg.new, EchoMsg.new]
  end
end

# Stub class for SlowService
SlowStub = SlowService.rpc_stub_class

# Service for testing synchronized cancellation
class SynchronizedCancellationService
  include GRPC::GenericService
  rpc :an_rpc, EchoMsg, EchoMsg
  attr_reader :received_md, :delay

  def initialize(notify_request_received, wait_until_rpc_cancelled)
    @notify_request_received = notify_request_received
    @wait_until_rpc_cancelled = wait_until_rpc_cancelled
  end

  def an_rpc(req, _call)
    GRPC.logger.info('starting a synchronusly cancelled rpc')
    @notify_request_received.call(req)
    @wait_until_rpc_cancelled.call
    req
  end
end

# Stub class for SynchronizedCancellationService
SynchronizedCancellationStub = SynchronizedCancellationService.rpc_stub_class

# Service for testing call object usage after RPC completion
class CheckCallAfterFinishedService
  include GRPC::GenericService
  rpc :an_rpc, EchoMsg, EchoMsg
  rpc :a_client_streaming_rpc, stream(EchoMsg), EchoMsg
  rpc :a_server_streaming_rpc, EchoMsg, stream(EchoMsg)
  rpc :a_bidi_rpc, stream(EchoMsg), stream(EchoMsg)
  attr_reader :server_side_call

  def an_rpc(req, call)
    fail 'shouldnt reuse service' unless @server_side_call.nil?
    @server_side_call = call
    req
  end

  def a_client_streaming_rpc(call)
    fail 'shouldnt reuse service' unless @server_side_call.nil?
    @server_side_call = call

    call.each_remote_read.each { |r| GRPC.logger.info(r) }
    EchoMsg.new
  end

  def a_server_streaming_rpc(_, call)
    fail 'shouldnt reuse service' unless @server_side_call.nil?
    @server_side_call = call
    [EchoMsg.new, EchoMsg.new]
  end

  def a_bidi_rpc(requests, call)
    fail 'shouldnt reuse service' unless @server_side_call.nil?
    @server_side_call = call
    requests.each { |r| GRPC.logger.info(r) }
    [EchoMsg.new, EchoMsg.new]
  end
end

# Stub class for CheckCallAfterFinishedService
CheckCallAfterFinishedServiceStub = CheckCallAfterFinishedService.rpc_stub_class

# Service for testing bad server responses
class BidiService
  include GRPC::GenericService
  rpc :server_sends_bad_input, stream(EchoMsg), stream(EchoMsg)

  def server_sends_bad_input(_, _)
    'bad response. (not an enumerable, client sees an error)'
  end
end

# Stub class for BidiService
BidiStub = BidiService.rpc_stub_class

# Main test suite for GRPC::RpcServer
describe GRPC::RpcServer do
  RpcServer = GRPC::RpcServer
  StatusCodes = GRPC::Core::StatusCodes

  before(:each) do
    @method = 'an_rpc_method'
    @pass = 0
    @fail = 1
    @noop = proc { |x| x }
  end

  # Tests for RpcServer initialization
  describe '#new' do
    it 'can be created with just some args' do
      opts = { server_args: { a_channel_arg: 'an_arg' } }
      blk = proc do
        new_rpc_server_for_testing(**opts)
      end
      expect(&blk).not_to raise_error
    end

    it 'cannot be created with invalid ServerCredentials' do
      blk = proc do
        opts = {
          server_args: { a_channel_arg: 'an_arg' },
          creds: Object.new
        }
        new_rpc_server_for_testing(**opts)
      end
      expect(&blk).to raise_error
    end
  end

  # Tests for server stopped state
  describe '#stopped?' do
    before(:each) do
      opts = { server_args: { a_channel_arg: 'an_arg' }, poll_period: 1.5 }
      @srv = new_rpc_server_for_testing(**opts)
      @srv.add_http2_port('0.0.0.0:0', :this_port_is_insecure)
    end

    it 'starts out false' do
      expect(@srv.stopped?).to be(false)
    end

    it 'stays false after the server starts running', server: true do
      @srv.handle(EchoService)
      t = Thread.new { @srv.run }
      @srv.wait_till_running
      expect(@srv.stopped?).to be(false)
      @srv.stop
      t.join
    end

    it 'is true after a running server is stopped', server: true do
      @srv.handle(EchoService)
      t = Thread.new { @srv.run }
      @srv.wait_till_running
      @srv.stop
      t.join
      expect(@srv.stopped?).to be(true)
    end
  end

  # Tests for server running state
  describe '#running?' do
    it 'starts out false' do
      opts = {
        server_args: { a_channel_arg: 'an_arg' }
      }
      r = new_rpc_server_for_testing(**opts)
      expect(r.running?).to be(false)
    end

    it 'is false if run is called with no services registered', server: true do
      opts = {
        server_args: { a_channel_arg: 'an_arg' },
        poll_period: 2
      }
      r = new_rpc_server_for_testing(**opts)
      r.add_http2_port('0.0.0.0:0', :this_port_is_insecure)
      expect { r.run }.to raise_error(RuntimeError)
    end

    it 'is true after run is called with a registered service' do
      opts = {
        server_args: { a_channel_arg: 'an_arg' },
        poll_period: 2.5
      }
      r = new_rpc_server_for_testing(**opts)
      r.add_http2_port('0.0.0.0:0', :this_port_is_insecure)
      r.handle(EchoService)
      t = Thread.new { r.run }
      r.wait_till_running
      expect(r.running?).to be(true)
      r.stop
      t.join
    end
  end

  # Tests for service handling
  describe '#handle' do
    before(:each) do
      @opts = { server_args: { a_channel_arg: 'an_arg' }, poll_period: 1 }
      @srv = new_rpc_server_for_testing(**@opts)
      @srv.add_http2_port('0.0.0.0:0', :this_port_is_insecure)
    end

    it 'raises if #run has already been called' do
      @srv.handle(EchoService)
      t = Thread.new { @srv.run }
      @srv.wait_till_running
      expect { @srv.handle(EchoService) }.to raise_error
      @srv.stop
      t.join
    end

    it 'raises if the server has been run and stopped' do
      @srv.handle(EchoService)
      t = Thread.new { @srv.run }
      @srv.wait_till_running
      @srv.stop
      t.join
      expect { @srv.handle(EchoService) }.to raise_error
    end

    it 'raises if the service does not include GenericService ' do
      expect { @srv.handle(Object) }.to raise_error
    end

    it 'raises if the service does not declare any rpc methods' do
      expect { @srv.handle(EmptyService) }.to raise_error
    end

    it 'raises if a handler method is already registered' do
      @srv.handle(EchoService)
      expect { r.handle(EchoService) }.to raise_error
    end
  end

  # Tests for server run behavior
  describe '#run' do
    let(:client_opts) { { channel_override: @ch } }
    let(:marshal) { EchoService.rpc_descs[:an_rpc].marshal_proc }
    let(:unmarshal) { EchoService.rpc_descs[:an_rpc].unmarshal_proc(:output) }

    # Tests without connect metadata
    context 'with no connect_metadata' do
      before(:each) do
        server_opts = {
          poll_period: 1
        }
        @srv = new_rpc_server_for_testing(**server_opts)
        server_port = @srv.add_http2_port('0.0.0.0:0', :this_port_is_insecure)
        @host = "localhost:#{server_port}"
        @ch = GRPC::Core::Channel.new(@host, nil, :this_channel_is_insecure)
      end

      it 'should return NOT_FOUND status on unknown methods', server: true do
        @srv.handle(EchoService)
        t = Thread.new { @srv.run }
        @srv.wait_till_running
        req = EchoMsg.new
        blk = proc do
          stub = GRPC::ClientStub.new(@host, :this_channel_is_insecure,
                                      **client_opts)
          stub.request_response('/unknown', req, marshal, unmarshal)
        end
        expect(&blk).to raise_error GRPC::BadStatus
        @srv.stop
        t.join
      end

      it 'should return UNIMPLEMENTED on unimplemented methods', server: true do
        @srv.handle(NoRpcImplementation)
        t = Thread.new { @srv.run }
        @srv.wait_till_running
        req = EchoMsg.new
        blk = proc do
          stub = GRPC::ClientStub.new(@host, :this_channel_is_insecure,
                                      **client_opts)
          stub.request_response('/an_rpc', req, marshal, unmarshal)
        end
        expect(&blk).to raise_error do |error|
          expect(error).to be_a(GRPC::BadStatus)
          expect(error.code).to be(GRPC::Core::StatusCodes::UNIMPLEMENTED)
        end
        @srv.stop
        t.join
      end

      it 'should return UNIMPLEMENTED on unimplemented ' \
         'methods for client_streamer', server: true do
        @srv.handle(EchoService)
        t = Thread.new { @srv.run }
        @srv.wait_till_running
        blk = proc do
          stub = EchoStub.new(@host, :this_channel_is_insecure, **client_opts)
          requests = [EchoMsg.new, EchoMsg.new]
          stub.a_client_streaming_rpc_unimplemented(requests)
        end

        begin
          expect(&blk).to raise_error do |error|
            expect(error).to be_a(GRPC::BadStatus)
            expect(error.code).to eq(GRPC::Core::StatusCodes::UNIMPLEMENTED)
          end
        ensure
          @srv.stop
          t.join
        end
      end

      it 'should handle multiple sequential requests', server: true do
        @srv.handle(EchoService)
        t = Thread.new { @srv.run }
        @srv.wait_till_running
        req = EchoMsg.new
        n = 5
        stub = EchoStub.new(@host, :this_channel_is_insecure, **client_opts)
        n.times { expect(stub.an_rpc(req)).to be_a(EchoMsg) }
        @srv.stop
        t.join
      end

      it 'should receive metadata sent as rpc keyword args', server: true do
        service = EchoService.new
        @srv.handle(service)
        t = Thread.new { @srv.run }
        @srv.wait_till_running
        req = EchoMsg.new
        stub = EchoStub.new(@host, :this_channel_is_insecure, **client_opts)
        expect(stub.an_rpc(req, metadata: { k1: 'v1', k2: 'v2' }))
          .to be_a(EchoMsg)
        wanted_md = [{ 'k1' => 'v1', 'k2' => 'v2' }]
        check_md(wanted_md, service.received_md)
        @srv.stop
        t.join
      end

      it 'should receive metadata if a deadline is specified', server: true do
        service = SlowService.new
        @srv.handle(service)
        t = Thread.new { @srv.run }
        @srv.wait_till_running
        req = EchoMsg.new
        stub = SlowStub.new(@host, :this_channel_is_insecure, **client_opts)
        timeout = service.delay + 1.0
        deadline = GRPC::Core::TimeConsts.from_relative_time(timeout)
        resp = stub.an_rpc(req,
                           deadline: deadline,
                           metadata: { k1: 'v1', k2: 'v2' })
        expect(resp).to be_a(EchoMsg)
        wanted_md = [{ 'k1' => 'v1', 'k2' => 'v2' }]
        check_md(wanted_md, service.received_md)
        @srv.stop
        t.join
      end

      it 'should raise DeadlineExceeded', server: true do
        service = SlowService.new
        @srv.handle(service)
        t = Thread.new { @srv.run }
        @srv.wait_till_running
        req = EchoMsg.new
        stub = SlowStub.new(@host, :this_channel_is_insecure, **client_opts)
        timeout = service.delay - 0.1
        deadline = GRPC::Core::TimeConsts.from_relative_time(timeout)
        responses = stub.a_server_streaming_rpc(req,
                                                deadline: deadline,
                                                metadata: { k1: 'v1', k2: 'v2' })
        expect { responses.to_a }.to raise_error(GRPC::DeadlineExceeded)
        @srv.stop
        t.join
      end

      it 'should handle cancellation correctly', server: true do
        request_received = false
        request_received_mu = Mutex.new
        request_received_cv = ConditionVariable.new
        notify_request_received = proc do |req|
          request_received_mu.synchronize do
            fail 'req is nil' if req.nil?
            expect(req.is_a?(EchoMsg)).to be true
            fail 'test bug - already set' if request_received
            request_received = true
            request_received_cv.signal
          end
        end

        rpc_cancelled = false
        rpc_cancelled
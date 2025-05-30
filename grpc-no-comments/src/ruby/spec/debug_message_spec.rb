# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'spec_helper'

TEST_DEBUG_MESSAGE = 'raised by test server'.freeze

class DebugMessageTestService
  include GRPC::GenericService
  rpc :an_rpc_raises_abort, EchoMsg, EchoMsg
  rpc :an_rpc_raises_standarderror, EchoMsg, EchoMsg

  def an_rpc_raises_abort(_req, _call)
    fail GRPC::Aborted.new(
      'aborted',
      {},
      TEST_DEBUG_MESSAGE)
  end

  def an_rpc_raises_standarderror(_req, _call)
    fail(StandardError, TEST_DEBUG_MESSAGE)
  end
end

DebugMessageTestServiceStub = DebugMessageTestService.rpc_stub_class

describe 'surfacing and transmitting of debug messages' do
  RpcServer = GRPC::RpcServer

  before(:all) do
    server_opts = {
      poll_period: 1
    }
    @srv = new_rpc_server_for_testing(**server_opts)
    @port = @srv.add_http2_port('0.0.0.0:0', :this_port_is_insecure)
    @srv.handle(DebugMessageTestService)
    @srv_thd = Thread.new { @srv.run }
    @srv.wait_till_running
  end

  after(:all) do
    expect(@srv.stopped?).to be(false)
    @srv.stop
    @srv_thd.join
  end

  it 'debug error message is not present BadStatus exceptions that dont set it' do
    exception_message = ''
    begin
      fail GRPC::Unavailable('unavailable', {})
    rescue StandardError => e
      p "Got exception: #{e.message}"
      exception_message = e.message
    end
    expect(exception_message.empty?).to be(false)
    expect(exception_message.include?('debug_error_string')).to be(false)
  end

  it 'debug error message is present in locally generated errors' do

    test_root = File.join(File.dirname(__FILE__), 'testdata')
    files = ['ca.pem', 'client.key', 'client.pem']
    creds = files.map { |f| File.open(File.join(test_root, f)).read }
    creds = GRPC::Core::ChannelCredentials.new(creds[0], creds[1], creds[2])
    stub = DebugMessageTestServiceStub.new(
      "localhost:#{@port}", creds)
    begin
      stub.an_rpc_raises_abort(EchoMsg.new)
    rescue StandardError => e
      p "Got exception: #{e.message}"
      exception_message = e.message

      expect(e.is_a?(GRPC::BadStatus)).to be(true)
    end

    expect(exception_message.include?('. debug_error_string:{')).to be(true)
  end

  it 'debug message is not transmitted from server to client' do

    stub = DebugMessageTestServiceStub.new(
      "localhost:#{@port}", :this_channel_is_insecure)
    exception_message = ''
    begin
      stub.an_rpc_raises_abort(EchoMsg.new)
    rescue StandardError => e
      p "Got exception: #{e.message}"
      exception_message = e.message

      expect(e.is_a?(GRPC::Aborted)).to be(true)
    end

    expect(exception_message.include?('. debug_error_string:{')).to be(true)
    expect(exception_message.include?(TEST_DEBUG_MESSAGE)).to be(false)
  end

  it 'standard_error messages are transmitted from server to client' do

    stub = DebugMessageTestServiceStub.new(
      "localhost:#{@port}", :this_channel_is_insecure)
    exception_message = ''
    begin
      stub.an_rpc_raises_standarderror(EchoMsg.new)
    rescue StandardError => e
      p "Got exception: #{e.message}"
      exception_message = e.message
      expect(e.is_a?(GRPC::BadStatus)).to be(true)
    end

    expect(exception_message.include?(TEST_DEBUG_MESSAGE)).to be(true)
  end
end

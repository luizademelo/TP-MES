# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'spec_helper'

def create_channel_creds
  test_root = File.join(File.dirname(__FILE__), 'testdata')
  files = ['ca.pem', 'client.key', 'client.pem']
  creds = files.map { |f| File.open(File.join(test_root, f)).read }
  GRPC::Core::ChannelCredentials.new(creds[0], creds[1], creds[2])
end

def client_cert
  test_root = File.join(File.dirname(__FILE__), 'testdata')
  cert = File.open(File.join(test_root, 'client.pem')).read
  fail unless cert.is_a?(String)
  cert
end

def create_server_creds
  test_root = File.join(File.dirname(__FILE__), 'testdata')
  GRPC.logger.info("test root: #{test_root}")
  files = ['ca.pem', 'server1.key', 'server1.pem']
  creds = files.map { |f| File.open(File.join(test_root, f)).read }
  GRPC::Core::ServerCredentials.new(
    creds[0],
    [{ private_key: creds[1], cert_chain: creds[2] }],
    true)
end

class SslTestService
  include GRPC::GenericService
  rpc :an_rpc, EchoMsg, EchoMsg
  rpc :a_client_streaming_rpc, stream(EchoMsg), EchoMsg
  rpc :a_server_streaming_rpc, EchoMsg, stream(EchoMsg)
  rpc :a_bidi_rpc, stream(EchoMsg), stream(EchoMsg)

  def check_peer_cert(call)
    error_msg = "want:\n#{client_cert}\n\ngot:\n#{call.peer_cert}"
    fail(error_msg) unless call.peer_cert == client_cert
  end

  def an_rpc(req, call)
    check_peer_cert(call)
    req
  end

  def a_client_streaming_rpc(call)
    check_peer_cert(call)
    call.each_remote_read.each { |r| GRPC.logger.info(r) }
    EchoMsg.new
  end

  def a_server_streaming_rpc(_, call)
    check_peer_cert(call)
    [EchoMsg.new, EchoMsg.new]
  end

  def a_bidi_rpc(requests, call)
    check_peer_cert(call)
    requests.each { |r| GRPC.logger.info(r) }
    [EchoMsg.new, EchoMsg.new]
  end
end

SslTestServiceStub = SslTestService.rpc_stub_class

describe 'client-server auth' do
  RpcServer = GRPC::RpcServer

  before(:all) do
    server_opts = {
      poll_period: 1
    }
    @srv = new_rpc_server_for_testing(**server_opts)
    ssl_creds = create_server_creds
    xds_creds = GRPC::Core::XdsServerCredentials.new(ssl_creds)
    port = @srv.add_http2_port('0.0.0.0:0', ssl_creds)
    xds_port = @srv.add_http2_port('0.0.0.0:0', xds_creds)
    @srv.handle(SslTestService)
    @srv_thd = Thread.new { @srv.run }
    @srv.wait_till_running

    client_opts = {
      channel_args: {
        GRPC::Core::Channel::SSL_TARGET => 'foo.test.google.fr'
      }
    }
    @stub = SslTestServiceStub.new("localhost:#{port}",
                                   create_channel_creds,
                                   **client_opts)

    xds_channel_creds = GRPC::Core::XdsChannelCredentials.new(create_channel_creds)
    @xds_stub = SslTestServiceStub.new("localhost:#{xds_port}",
                                       xds_channel_creds,
                                       **client_opts)
  end

  after(:all) do
    expect(@srv.stopped?).to be(false)
    @srv.stop
    @srv_thd.join
  end

  it 'client-server auth with unary RPCs' do
    @stub.an_rpc(EchoMsg.new)
  end

  it 'client-server auth with client streaming RPCs' do
    @stub.a_client_streaming_rpc([EchoMsg.new, EchoMsg.new])
  end

  it 'client-server auth with server streaming RPCs' do
    responses = @stub.a_server_streaming_rpc(EchoMsg.new)
    responses.each { |r| GRPC.logger.info(r) }
  end

  it 'client-server auth with bidi RPCs' do
    responses = @stub.a_bidi_rpc([EchoMsg.new, EchoMsg.new])
    responses.each { |r| GRPC.logger.info(r) }
  end

  it 'xds_client-xds_server ssl fallback auth with unary RPCs' do
    @xds_stub.an_rpc(EchoMsg.new)
  end

  it 'xds_client-xds_server ssl fallback auth with client streaming RPCs' do
    @xds_stub.a_client_streaming_rpc([EchoMsg.new, EchoMsg.new])
  end

  it 'xds_client-xds_server ssl fallback auth with server streaming RPCs' do
    responses = @xds_stub.a_server_streaming_rpc(EchoMsg.new)
    responses.each { |r| GRPC.logger.info(r) }
  end

  it 'xds_client-xds_server ssl fallback auth with bidi RPCs' do
    responses = @xds_stub.a_bidi_rpc([EchoMsg.new, EchoMsg.new])
    responses.each { |r| GRPC.logger.info(r) }
  end
end

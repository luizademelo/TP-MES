#!/usr/bin/env ruby

# Copyright 2020 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

this_dir = File.expand_path(File.dirname(__FILE__))
protos_lib_dir = File.join(this_dir, 'lib')
grpc_lib_dir = File.join(File.dirname(this_dir), 'lib')
$LOAD_PATH.unshift(grpc_lib_dir) unless $LOAD_PATH.include?(grpc_lib_dir)
$LOAD_PATH.unshift(protos_lib_dir) unless $LOAD_PATH.include?(protos_lib_dir)
$LOAD_PATH.unshift(this_dir) unless $LOAD_PATH.include?(this_dir)

require 'sanity_check_dlopen'
require 'grpc'
require 'end2end_common'

def create_channel_creds
  test_root = File.join(File.dirname(__FILE__), '..', 'spec', 'testdata')
  files = ['ca.pem', 'client.key', 'client.pem']
  creds = files.map { |f| File.open(File.join(test_root, f)).read }
  GRPC::Core::ChannelCredentials.new(creds[0], creds[1], creds[2])
end

def client_cert
  test_root = File.join(File.dirname(__FILE__), '..', 'spec', 'testdata')
  cert = File.open(File.join(test_root, 'client.pem')).read
  fail unless cert.is_a?(String)
  cert
end

def create_server_creds
  test_root = File.join(File.dirname(__FILE__), '..', 'spec', 'testdata')
  GRPC.logger.info("test root: #{test_root}")
  files = ['ca.pem', 'server1.key', 'server1.pem']
  creds = files.map { |f| File.open(File.join(test_root, f)).read }
  GRPC::Core::ServerCredentials.new(
    creds[0],
    [{ private_key: creds[1], cert_chain: creds[2] }],
    true)
end

def run_rpc_expect_unavailable(stub)
  exception = nil
  begin
    stub.echo(Echo::EchoRequest.new(request: 'hello'), deadline: Time.now + 10)
  rescue GRPC::BadStatus => e
    exception = e
  end
  fail "Expected call to fail UNAVAILABLE. Got failure:|#{exception}|" unless exception.is_a?(GRPC::Unavailable)
end

def main
  server_runner = ServerRunner.new(EchoServerImpl)
  server_runner.server_creds = create_server_creds
  server_port = server_runner.run
  channel_args = {
    GRPC::Core::Channel::SSL_TARGET => 'foo.test.google.fr'
  }
  call_creds_invocation_count = MutableValue.new(0)
  call_creds_invocation_count_mu = Mutex.new
  empty_header_proc = proc do
    call_creds_invocation_count_mu.synchronize do
      call_creds_invocation_count.value += 1
    end

    { '' => '123' }
  end
  bad_type_proc = proc do
    call_creds_invocation_count_mu.synchronize do
      call_creds_invocation_count.value += 1
    end

    1
  end
  nil_proc = proc do
    call_creds_invocation_count_mu.synchronize do
      call_creds_invocation_count.value += 1
    end

    nil
  end
  raising_proc = proc do
    call_creds_invocation_count_mu.synchronize do
      call_creds_invocation_count.value += 1
    end

    raise 'exception thrown by raising_proc call creds'
  end
  good_header_proc = proc do
    call_creds_invocation_count_mu.synchronize do
      call_creds_invocation_count.value += 1
    end
    { 'authorization' => 'fake_val' }
  end
  empty_header_stub = Echo::EchoServer::Stub.new(
    "localhost:#{server_port}",
    create_channel_creds.compose(GRPC::Core::CallCredentials.new(empty_header_proc)),
    channel_args: channel_args)
  bad_type_stub = Echo::EchoServer::Stub.new(
    "localhost:#{server_port}",
    create_channel_creds.compose(GRPC::Core::CallCredentials.new(bad_type_proc)),
    channel_args: channel_args)
  nil_stub = Echo::EchoServer::Stub.new(
    "localhost:#{server_port}",
    create_channel_creds.compose(GRPC::Core::CallCredentials.new(nil_proc)),
    channel_args: channel_args)
  raising_stub = Echo::EchoServer::Stub.new(
    "localhost:#{server_port}",
    create_channel_creds.compose(GRPC::Core::CallCredentials.new(raising_proc)),
    channel_args: channel_args)
  good_stub = Echo::EchoServer::Stub.new(
    "localhost:#{server_port}",
    create_channel_creds.compose(GRPC::Core::CallCredentials.new(good_header_proc)),
    channel_args: channel_args)
  STDERR.puts 'perform an RPC using call creds that return valid headers and expect OK...'
  good_stub.echo(Echo::EchoRequest.new(request: 'hello'), deadline: Time.now + 300)
  STDERR.puts 'perform an RPC using call creds that return an empty header and expect it to fail...'
  run_rpc_expect_unavailable(empty_header_stub)
  STDERR.puts 'perform an RPC using call creds that return a bad type and expect it to fail...'
  run_rpc_expect_unavailable(bad_type_stub)
  STDERR.puts 'perform an RPC using call creds that return nil and expect OK...'
  nil_stub.echo(Echo::EchoRequest.new(request: 'hello'), deadline: Time.now + 300)
  STDERR.puts 'perform an RPC using call creds that raise an error and expect it to fail...'
  run_rpc_expect_unavailable(raising_stub)
  STDERR.puts 'perform an RPC using call creds that return valid headers and expect OK...'

  good_stub.echo(Echo::EchoRequest.new(request: 'hello'), deadline: Time.now + 300)
  server_runner.stop
  call_creds_invocation_count_mu.synchronize do
    unless call_creds_invocation_count.value == 6
      fail 'test did not actually use the call credentials'
    end
  end
end

main

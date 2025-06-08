Here's the commented version of the code:

```ruby
#!/usr/bin/env ruby

# Copyright 2020 gRPC authors.
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

# Set up load paths for required libraries
this_dir = File.expand_path(File.dirname(__FILE__))
protos_lib_dir = File.join(this_dir, 'lib')
grpc_lib_dir = File.join(File.dirname(this_dir), 'lib')
$LOAD_PATH.unshift(grpc_lib_dir) unless $LOAD_PATH.include?(grpc_lib_dir)
$LOAD_PATH.unshift(protos_lib_dir) unless $LOAD_PATH.include?(protos_lib_dir)
$LOAD_PATH.unshift(this_dir) unless $LOAD_PATH.include?(this_dir)

# Require necessary dependencies
require 'sanity_check_dlopen'
require 'grpc'
require 'end2end_common'

# Creates and returns channel credentials using test certificate files
# @return [GRPC::Core::ChannelCredentials] SSL credentials for client channel
def create_channel_creds
  test_root = File.join(File.dirname(__FILE__), '..', 'spec', 'testdata')
  files = ['ca.pem', 'client.key', 'client.pem']
  creds = files.map { |f| File.open(File.join(test_root, f)).read }
  GRPC::Core::ChannelCredentials.new(creds[0], creds[1], creds[2])
end

# Reads and returns the client certificate file content
# @return [String] Content of client.pem certificate file
def client_cert
  test_root = File.join(File.dirname(__FILE__), '..', 'spec', 'testdata')
  cert = File.open(File.join(test_root, 'client.pem')).read
  fail unless cert.is_a?(String)
  cert
end

# Creates and returns server credentials using test certificate files
# @return [GRPC::Core::ServerCredentials] SSL credentials for server
def create_server_creds
  test_root = File.join(File.dirname(__FILE__), '..', 'spec', 'testdata')
  GRPC.logger.info("test root: #{test_root}")
  files = ['ca.pem', 'server1.key', 'server1.pem']
  creds = files.map { |f| File.open(File.join(test_root, f)).read }
  GRPC::Core::ServerCredentials.new(
    creds[0],
    [{ private_key: creds[1], cert_chain: creds[2] }],
    true)  # true enables client certificate verification
end

# Executes an RPC call and expects it to fail with UNAVAILABLE status
# @param stub [GRPC::ClientStub] The gRPC client stub to test
def run_rpc_expect_unavailable(stub)
  exception = nil
  begin
    stub.echo(Echo::EchoRequest.new(request: 'hello'), deadline: Time.now + 10)
  rescue GRPC::BadStatus => e
    exception = e
  end
  fail "Expected call to fail UNAVAILABLE. Got failure:|#{exception}|" unless exception.is_a?(GRPC::Unavailable)
end

# Main test function that executes various test scenarios
def main
  # Set up test server with credentials
  server_runner = ServerRunner.new(EchoServerImpl)
  server_runner.server_creds = create_server_creds
  server_port = server_runner.run

  # Configure channel arguments
  channel_args = {
    GRPC::Core::Channel::SSL_TARGET => 'foo.test.google.fr'  # Fake SSL target name for testing
  }

  # Setup for tracking call credential invocations
  call_creds_invocation_count = MutableValue.new(0)
  call_creds_invocation_count_mu = Mutex.new

  # Define various call credential behaviors to test:
  
  # Returns empty header (should fail)
  empty_header_proc = proc do
    call_creds_invocation_count_mu.synchronize do
      call_creds_invocation_count.value += 1
    end
    { '' => '123' }
  end

  # Returns wrong type (should fail)
  bad_type_proc = proc do
    call_creds_invocation_count_mu.synchronize do
      call_creds_invocation_count.value += 1
    end
    1  # Intentionally returning wrong type
  end

  # Returns nil (should pass)
  nil_proc = proc do
    call_creds_invocation_count_mu.synchronize do
      call_creds_invocation_count.value += 1
    end
    nil
  end

  # Raises exception (should fail)
  raising_proc = proc do
    call_creds_invocation_count_mu.synchronize do
      call_creds_invocation_count.value += 1
    end
    raise 'exception thrown by raising_proc call creds'
  end

  # Returns valid header (should pass)
  good_header_proc = proc do
    call_creds_invocation_count_mu.synchronize do
      call_creds_invocation_count.value += 1
    end
    { 'authorization' => 'fake_val' }  # Valid authorization header
  end

  # Create client stubs with different call credential behaviors
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

  # Execute test scenarios:
  
  # Test valid credentials
  STDERR.puts 'perform an RPC using call creds that return valid headers and expect OK...'
  good_stub.echo(Echo::EchoRequest.new(request: 'hello'), deadline: Time.now + 300)
  
  # Test invalid credentials scenarios
  STDERR.puts 'perform an RPC using call creds that return an empty header and expect it to fail...'
  run_rpc_expect_unavailable(empty_header_stub)
  
  STDERR.puts 'perform an RPC using call creds that return a bad type and expect it to fail...'
  run_rpc_expect_unavailable(bad_type_stub)
  
  STDERR.puts 'perform an RPC using call creds that return nil and expect OK...'
  nil_stub.echo(Echo::EchoRequest.new(request: 'hello'), deadline: Time.now + 300)
  
  STDERR.puts 'perform an RPC using call creds that raise an error and expect it to fail...'
  run_rpc_expect_unavailable(raising_stub)
  
  # Repeat valid credentials test
  STDERR.puts 'perform an RPC using call creds that return valid headers and expect OK...'
  good_stub.echo(Echo::EchoRequest.new(request: 'hello'), deadline: Time.now + 300)

  # Clean up and verify test execution
  server_runner.stop
  call_creds_invocation_count_mu.synchronize do
    unless call_creds_invocation_count.value == 6
      fail 'test did not actually use the call credentials'
    end
  end
end

# Execute the main test function
main
```

The comments explain:
1. File header and license information
2. Load path setup for dependencies
3. Each function's purpose, parameters, and return values
4. The main test flow and different test scenarios
5. The expected behavior for each test case
6. Thread synchronization points
7. Credential configuration details
8. Test verification logic

The comments are designed to help future developers understand:
- The overall purpose of the test script
- How the different credential types are being tested
- What each test case is verifying
- The expected outcomes
- The thread safety mechanisms in place
- The test verification at the end
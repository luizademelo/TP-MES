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

# Enable fork support for gRPC
ENV['GRPC_ENABLE_FORK_SUPPORT'] = "1"
# Ensure this script only runs on Linux as forking is only supported there
fail "forking only supported on linux" unless RUBY_PLATFORM =~ /linux/

# Set up load paths for required libraries
this_dir = File.expand_path(File.dirname(__FILE__))
protos_lib_dir = File.join(this_dir, 'lib')
grpc_lib_dir = File.join(File.dirname(this_dir), 'lib')
$LOAD_PATH.unshift(grpc_lib_dir) unless $LOAD_PATH.include?(grpc_lib_dir)
$LOAD_PATH.unshift(protos_lib_dir) unless $LOAD_PATH.include?(protos_lib_dir)
$LOAD_PATH.unshift(this_dir) unless $LOAD_PATH.include?(this_dir)

# Require necessary libraries
require 'sanity_check_dlopen'  # Checks for proper dynamic linking
require 'grpc'                 # gRPC library
require 'end2end_common'       # Common utilities for end-to-end tests

# Performs a simple RPC call using the given stub
# @param stub [GRPC::ClientStub] The gRPC client stub
# @return [Echo::EchoResponse] The response from the server
def do_rpc(stub)
  stub.echo(Echo::EchoRequest.new(request: 'hello'), deadline: Time.now + 300)
end

# Creates channel credentials for secure communication
# @return [GRPC::Core::ChannelCredentials] SSL/TLS credentials
def create_channel_creds
  test_root = File.join(File.dirname(__FILE__), '..', 'spec', 'testdata')
  files = ['ca.pem', 'client.key', 'client.pem']  # Required SSL files
  creds = files.map { |f| File.open(File.join(test_root, f)).read }
  GRPC::Core::ChannelCredentials.new(creds[0], creds[1], creds[2])
end

# Reads and returns the client certificate
# @return [String] The content of the client certificate file
def client_cert
  test_root = File.join(File.dirname(__FILE__), '..', 'spec', 'testdata')
  cert = File.open(File.join(test_root, 'client.pem')).read
  fail unless cert.is_a?(String)  # Ensure certificate is valid
  cert
end

# Runs the client test scenario with fork operations
# @param stub [GRPC::ClientStub] The gRPC client stub
def run_client(stub)
  # Initial RPC call before forking
  do_rpc(stub)
  
  # Parent process prepares for fork
  with_logging("parent: GRPC.prefork") { GRPC.prefork }
  
  # First child process
  pid = fork do
    # Child initializes after fork
    with_logging("child1: GRPC.postfork_child") { GRPC.postfork_child }
    with_logging("child1: first post-fork RPC") { do_rpc(stub) }
    
    # First child prepares for second fork
    with_logging("child1: GRPC.prefork") { GRPC.prefork }
    
    # Second child process (grandchild)
    pid2 = fork do
      with_logging("child2: GRPC.postfork_child") { GRPC.postfork_child }
      with_logging("child2: first post-fork RPC") { do_rpc(stub) }
      with_logging("child2: second post-fork RPC") { do_rpc(stub) }
      STDERR.puts "child2: done"
    end
    
    # First child continues after second fork
    with_logging("child1: GRPC.postfork_parent") { GRPC.postfork_parent }
    with_logging("child1: second post-fork RPC") { do_rpc(stub) }
    Process.wait(pid2)  # Wait for second child to finish
    STDERR.puts "child1: done"
  end
  
  # Parent process continues after first fork
  with_logging("parent: GRPC.postfork_parent") { GRPC.postfork_parent }
  with_logging("parent: first post-fork RPC") { do_rpc(stub) }
  with_logging("parent: second post-fork RPC") { do_rpc(stub) }
  Process.wait pid  # Wait for first child to finish
  STDERR.puts "parent: done"
end

# Main entry point for the script
def main
  this_dir = File.expand_path(File.dirname(__FILE__))
  echo_server_path = File.join(this_dir, 'echo_server.rb')
  
  # Set up pipes for inter-process communication with server
  to_child_r, _to_child_w = IO.pipe
  to_parent_r, to_parent_w = IO.pipe
  
  # Start the echo server in a separate process
  Process.spawn(RbConfig.ruby, echo_server_path, "--secure", 
                in: to_child_r, out: to_parent_w, err: "server_log")
  
  # Close unused pipe ends
  to_child_r.close
  to_parent_w.close
  
  # Get server port from the pipe
  child_port = to_parent_r.gets.strip
  STDERR.puts "server running on port: #{child_port}"
  
  # Create secure channel credentials with call credentials
  channel_creds = create_channel_creds.compose(
    GRPC::Core::CallCredentials.new(proc do |args|
      { 'authorization' => 'test' }.merge(args)
    end))
  
  # Create client stub with secure connection
  stub = Echo::EchoServer::Stub.new(
    "localhost:#{child_port}", channel_creds,
    channel_args: { GRPC::Core::Channel::SSL_TARGET => 'foo.test.google.fr' })
  
  # Run the client test scenario twice
  2.times do
    run_client(stub)
  end
end

# Execute the main function
main
```

Key aspects covered in the comments:
1. File header and license information
2. Environment setup and requirements
3. Purpose of each function
4. Parameter and return value documentation
5. Explanation of the complex forking logic
6. Secure channel setup details
7. Inter-process communication flow
8. Main execution flow

The comments are designed to help future developers understand:
- The overall purpose of the script (testing gRPC with forking)
- The secure communication setup
- The complex process hierarchy created by the nested forks
- The sequence of RPC calls and fork operations
- The error handling and logging approach
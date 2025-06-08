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

# Set up the load path to include the library directory
this_dir = File.expand_path(File.dirname(__FILE__))
lib_dir = File.join(File.dirname(this_dir), 'lib')
$LOAD_PATH.unshift(lib_dir) unless $LOAD_PATH.include?(lib_dir)

# Require necessary libraries
require 'grpc'
require 'optparse'

# A dummy message class for testing purposes without protocol buffers
class NoProtoMsg
  # Empty marshaling method
  def self.marshal(_o)
    ''
  end

  # Empty unmarshaling method that returns a new NoProtoMsg instance
  def self.unmarshal(_o)
    NoProtoMsg.new
  end
end

# A generic gRPC service definition without protocol buffers
class NoProtoService
  include GRPC::GenericService
  # Define a single RPC method named AnRPC that takes and returns NoProtoMsg
  rpc :AnRPC, NoProtoMsg, NoProtoMsg
end

# Implementation of the NoProtoService
class NoProto < NoProtoService
  def initialize(_default_var = 'ignored')
    # Constructor that takes an ignored parameter
  end

  # Implementation of the AnRPC method
  def an_rpc(req, _call)
    # Log that a request was received
    GRPC.logger.info('echo service received a request')
    # Simply echo back the received request
    req
  end
end

# Load test certificates from the spec/testdata directory
def load_test_certs
  this_dir = File.expand_path(File.dirname(__FILE__))
  data_dir = File.join(File.dirname(this_dir), 'spec/testdata')
  # List of certificate files to load
  files = ['ca.pem', 'server1.key', 'server1.pem']
  # Read and return all certificate files
  files.map { |f| File.open(File.join(data_dir, f)).read }
end

# Create server credentials using the test certificates
def test_server_creds
  certs = load_test_certs
  GRPC::Core::ServerCredentials.new(
    nil, [{ private_key: certs[1], cert_chain: certs[2] }], false)
end

# Main method to run the gRPC server
def main
  # Default options for the server
  options = {
    'host' => 'localhost:9090',
    'secure' => false
  }
  
  # Set up command line option parsing
  OptionParser.new do |opts|
    opts.banner = 'Usage: [--host <hostname>:<port>] [--secure|-s]'
    opts.on('--host HOST', '<hostname>:<port>') do |v|
      options['host'] = v
    end
    opts.on('-s', '--secure', 'access using test creds') do |v|
      options['secure'] = v
    end
  end.parse!

  # Create a new gRPC server
  s = GRPC::RpcServer.new
  
  # Configure server based on options
  if options['secure']
    # Secure mode: use test credentials
    s.add_http2_port(options['host'], test_server_creds)
    GRPC.logger.info("... running securely on #{options['host']}")
  else
    # Insecure mode
    s.add_http2_port(options['host'], :this_port_is_insecure)
    GRPC.logger.info("... running insecurely on #{options['host']}")
  end

  # Register the NoProto service with the server
  s.handle(NoProto)
  # Run the server until terminated
  s.run_till_terminated
end

# Start the server
main
```
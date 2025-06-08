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

# Set up the load path to include the lib directory
this_dir = File.expand_path(File.dirname(__FILE__))
lib_dir = File.join(File.dirname(this_dir), 'lib')
$LOAD_PATH.unshift(lib_dir) unless $LOAD_PATH.include?(lib_dir)

# Require necessary libraries
require 'grpc'
require 'optparse'

# A simple message class with no protobuf content
class NoProtoMsg
  # Empty marshaller method
  def self.marshal(_o)
    ''
  end

  # Returns a new NoProtoMsg instance when unmarshalling
  def self.unmarshal(_o)
    NoProtoMsg.new
  end
end

# A generic gRPC service definition with one RPC method
class NoProtoService
  include GRPC::GenericService
  # Define a simple RPC method that takes and returns NoProtoMsg
  rpc :AnRPC, NoProtoMsg, NoProtoMsg
end

# Generate the stub class for the NoProtoService
NoProtoStub = NoProtoService.rpc_stub_class

# Load test certificates from the spec/testdata directory
def load_test_certs
  this_dir = File.expand_path(File.dirname(__FILE__))
  data_dir = File.join(File.dirname(this_dir), 'spec/testdata')
  files = ['ca.pem', 'server1.key', 'server1.pem']
  files.map { |f| File.open(File.join(data_dir, f)).read }
end

# Create test credentials using the loaded certificates
def test_creds
  certs = load_test_certs
  GRPC::Core::ChannelCredentials.new(certs[0])
end

# Main execution method
def main
  # Default connection options
  options = {
    'host' => 'localhost:7071',
    'secure' => false
  }
  
  # Set up command line option parser
  OptionParser.new do |opts|
    opts.banner = 'Usage: [--host <hostname>:<port>] [--secure|-s]'
    opts.on('--host HOST', '<hostname>:<port>') do |v|
      options['host'] = v
    end
    opts.on('-s', '--secure', 'access using test creds') do |v|
      options['secure'] = v
    end
  end.parse!

  # Create a stub connection based on the options
  if options['secure']
    # Secure connection options
    stub_opts = {
      :creds => test_creds,
      GRPC::Core::Channel::SSL_TARGET => 'foo.test.google.fr'
    }
    p stub_opts
    p options['host']
    stub = NoProtoStub.new(options['host'], **stub_opts)
    GRPC.logger.info("... connecting securely on #{options['host']}")
  else
    # Insecure connection
    stub = NoProtoStub.new(options['host'])
    GRPC.logger.info("... connecting insecurely on #{options['host']}")
  end

  # Make an RPC call and log the response
  GRPC.logger.info('sending a NoProto rpc')
  resp = stub.an_rpc(NoProtoMsg.new)
  GRPC.logger.info("got a response: #{resp}")
end

# Execute the main method
main
```

Key comments added:
1. Explained the purpose of each class (NoProtoMsg, NoProtoService)
2. Documented the RPC method definition
3. Explained the certificate loading functionality
4. Added comments for the main execution flow
5. Documented the command line option parsing
6. Explained both secure and insecure connection paths
7. Added comments for the RPC call and response handling

The comments provide clear explanations of each component's purpose and how they fit together in the overall gRPC client implementation.
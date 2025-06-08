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

# Set up load paths to include local directories
this_dir = File.expand_path(File.dirname(__FILE__))
lib_dir = File.join(File.dirname(this_dir), 'lib')
$LOAD_PATH.unshift(lib_dir) unless $LOAD_PATH.include?(lib_dir)
$LOAD_PATH.unshift(this_dir) unless $LOAD_PATH.include?(this_dir)

# Require necessary libraries
require 'grpc'               # gRPC core library
require 'math_services_pb'   # Generated protobuf service definitions
require 'optparse'           # For command-line option parsing
require 'logger'             # For logging

include GRPC::Core::TimeConsts  # Include time constants from gRPC core

# Module to extend GRPC with stdout logging capability
module StdoutLogger
  def logger
    LOGGER
  end

  # Create a logger instance that outputs to STDOUT
  LOGGER = Logger.new(STDOUT)
end

# Extend GRPC with our logging module
GRPC.extend(StdoutLogger)

# Makes a unary RPC call to divide two numbers
# @param stub [Math::Math::Stub] The gRPC client stub
def do_div(stub)
  GRPC.logger.info('request_response')
  GRPC.logger.info('----------------')
  # Create division request with dividend 7 and divisor 3
  req = Math::DivArgs.new(dividend: 7, divisor: 3)
  GRPC.logger.info("div(7/3): req=#{req.inspect}")
  # Make RPC call
  resp = stub.div(req)
  GRPC.logger.info("Answer: #{resp.inspect}")
  GRPC.logger.info('----------------')
end

# Makes a client streaming RPC call to sum multiple numbers
# @param stub [Math::Math::Stub] The gRPC client stub
def do_sum(stub)
  GRPC.logger.info('client_streamer')
  GRPC.logger.info('---------------')
  # Create array of numbers to sum (1 through 5)
  reqs = [1, 2, 3, 4, 5].map { |x| Math::Num.new(num: x) }
  GRPC.logger.info("sum(1, 2, 3, 4, 5): reqs=#{reqs.inspect}")
  # Make streaming RPC call
  resp = stub.sum(reqs)
  GRPC.logger.info("Answer: #{resp.inspect}")
  GRPC.logger.info('---------------')
end

# Makes a server streaming RPC call to get Fibonacci sequence
# @param stub [Math::Math::Stub] The gRPC client stub
def do_fib(stub)
  GRPC.logger.info('server_streamer')
  GRPC.logger.info('----------------')
  # Create Fibonacci request with limit 11
  req = Math::FibArgs.new(limit: 11)
  GRPC.logger.info("fib(11): req=#{req.inspect}")
  # Make streaming RPC call and process each response
  resp = stub.fib(req)
  resp.each do |r|
    GRPC.logger.info("Answer: #{r.inspect}")
  end
  GRPC.logger.info('----------------')
end

# Makes a bidirectional streaming RPC call for multiple divisions
# @param stub [Math::Math::Stub] The gRPC client stub
def do_div_many(stub)
  GRPC.logger.info('bidi_streamer')
  GRPC.logger.info('-------------')
  # Create array of division requests
  reqs = []
  reqs << Math::DivArgs.new(dividend: 7, divisor: 3)
  reqs << Math::DivArgs.new(dividend: 5, divisor: 2)
  reqs << Math::DivArgs.new(dividend: 7, divisor: 2)
  GRPC.logger.info("div(7/3), div(5/2), div(7/2): reqs=#{reqs.inspect}")
  # Make bidirectional streaming RPC call and process each response
  resp = stub.div_many(reqs)
  resp.each do |r|
    GRPC.logger.info("Answer: #{r.inspect}")
  end
  GRPC.logger.info('----------------')
end

# Load test certificates from spec/testdata directory
# @return [Array<String>] Array containing certificate file contents
def load_test_certs
  this_dir = File.expand_path(File.dirname(__FILE__))
  data_dir = File.join(File.dirname(this_dir), 'spec/testdata')
  files = ['ca.pem', 'server1.key', 'server1.pem']
  files.map { |f| File.open(File.join(data_dir, f)).read }
end

# Create test credentials using loaded certificates
# @return [GRPC::Core::ChannelCredentials] Channel credentials for secure connection
def test_creds
  certs = load_test_certs
  GRPC::Core::ChannelCredentials.new(certs[0])
end

# Main entry point for the client application
def main
  # Default connection options
  options = {
    'host' => 'localhost:7071',
    'secure' => false
  }
  
  # Parse command line options
  OptionParser.new do |opts|
    opts.banner = 'Usage: [--host <hostname>:<port>] [--secure|-s]'
    opts.on('--host HOST', '<hostname>:<port>') do |v|
      options['host'] = v
    end
    opts.on('-s', '--secure', 'access using test creds') do |v|
      options['secure'] = v
    end
  end.parse!

  # Create gRPC stub with appropriate connection options
  if options['secure']
    # Secure connection options
    stub_opts = {
      :creds => test_creds,
      GRPC::Core::Channel::SSL_TARGET => 'foo.test.google.fr',
      timeout: INFINITE_FUTURE,
    }
    stub = Math::Math::Stub.new(options['host'], **stub_opts)
    GRPC.logger.info("... connecting securely on #{options['host']}")
  else
    # Insecure connection options
    stub = Math::Math::Stub.new(options['host'], :this_channel_is_insecure, timeout: INFINITE_FUTURE)
    GRPC.logger.info("... connecting insecurely on #{options['host']}")
  end

  # Execute all RPC calls
  do_div(stub)       # Unary RPC
  do_sum(stub)       # Client streaming RPC
  do_fib(stub)       # Server streaming RPC
  do_div_many(stub)  # Bidirectional streaming RPC
end

# Start the client
main
```
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

# Set up load paths to include local and library directories
this_dir = File.expand_path(File.dirname(__FILE__))
lib_dir = File.join(File.dirname(this_dir), 'lib')
$LOAD_PATH.unshift(lib_dir) unless $LOAD_PATH.include?(lib_dir)
$LOAD_PATH.unshift(this_dir) unless $LOAD_PATH.include?(this_dir)

# Required dependencies
require 'forwardable'
require 'grpc'
require 'logger'
require 'math_services_pb'  # Generated protobuf service definitions
require 'optparse'          # For command-line option parsing

# Module to provide logger functionality
module RubyLogger
  def logger
    LOGGER
  end

  # Logger instance that outputs to STDOUT
  LOGGER = Logger.new(STDOUT)
end

# Extend GRPC module with logger functionality
module GRPC
  extend RubyLogger
end

# Class to generate Fibonacci numbers up to a given limit
class Fibber
  def initialize(limit)
    fail "bad limit: got #{limit}, want limit > 0" if limit < 1
    @limit = limit
  end

  # Generator that yields Fibonacci numbers as Math::Num objects
  def generator
    return enum_for(:generator) unless block_given?
    idx, current, previous = 0, 1, 1
    until idx == @limit
      if idx.zero? || idx == 1
        yield Math::Num.new(num: 1)
        idx += 1
        next
      end
      tmp = current
      current = previous + current
      previous = tmp
      yield Math::Num.new(num: current)
      idx += 1
    end
  end
end

# Queue wrapper that works with Enumerator and includes a sentinel value
class EnumeratorQueue
  extend Forwardable
  def_delegators :@q, :push

  def initialize(sentinel)
    @q = Queue.new
    @sentinel = sentinel  # Value that signals end of queue
  end

  # Iterates through items in queue until sentinel is encountered
  def each_item
    return enum_for(:each_item) unless block_given?
    loop do
      r = @q.pop
      break if r.equal?(@sentinel)
      fail r if r.is_a? Exception
      yield r
    end
  end
end

# Implementation of the Math service defined in the protobuf
class Calculator < Math::Math::Service
  # Division operation implementation
  def div(div_args, _call)
    if div_args.divisor.zero?
      fail GRPC::StatusError.new(GRPC::Status::INVALID_ARGUMENT,
                                 'divisor cannot be 0')
    end

    Math::DivReply.new(quotient: div_args.dividend / div_args.divisor,
                       remainder: div_args.dividend % div_args.divisor)
  end

  # Sum operation implementation - sums all numbers in the stream
  def sum(call)
    nums = call.each_remote_read.collect(&:num)
    sum = nums.inject { |s, x| s + x }
    Math::Num.new(num: sum)
  end

  # Fibonacci sequence generator
  def fib(fib_args, _call)
    if fib_args.limit < 1
      fail StatusError.new(Status::INVALID_ARGUMENT, 'limit must be >= 0')
    end

    Fibber.new(fib_args.limit).generator
  end

  # Streaming division operation - processes multiple division requests
  def div_many(requests)
    q = EnumeratorQueue.new(self)
    t = Thread.new do
      begin
        requests.each do |req|
          GRPC.logger.info("read #{req.inspect}")
          resp = Math::DivReply.new(quotient: req.dividend / req.divisor,
                                    remainder: req.dividend % req.divisor)
          q.push(resp)
          Thread.pass
        end
        GRPC.logger.info('finished reads')
        q.push(self)  # Push sentinel to signal end
      rescue StandardError => e
        q.push(e)
        raise e
      end
    end
    t.priority = -2  # Lower thread priority
    q.each_item
  end
end

# Load test certificates from spec/testdata directory
def load_test_certs
  this_dir = File.expand_path(File.dirname(__FILE__))
  data_dir = File.join(File.dirname(this_dir), 'spec/testdata')
  files = ['ca.pem', 'server1.key', 'server1.pem']
  files.map { |f| File.open(File.join(data_dir, f)).read }
end

# Create test server credentials using loaded certificates
def test_server_creds
  certs = load_test_certs
  GRPC::Core::ServerCredentials.new(
    nil, [{ private_key: certs[1], cert_chain: certs[2] }], false)
end

# Main entry point for the server
def main
  # Default options
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

  # Create and configure gRPC server
  s = GRPC::RpcServer.new
  if options['secure']
    s.add_http2_port(options['host'], test_server_creds)
    GRPC.logger.info("... running securely on #{options['host']}")
  else
    s.add_http2_port(options['host'], :this_port_is_insecure)
    GRPC.logger.info("... running insecurely on #{options['host']}")
  end

  # Register service and start server
  s.handle(Calculator)
  s.run_till_terminated
end

main
```

Key improvements in the comments:
1. Added explanations for each class and its purpose
2. Documented important methods with their functionality
3. Explained the flow of operations in complex methods
4. Added comments about the gRPC-specific functionality
5. Clarified the purpose of utility functions and modules
6. Explained the command-line option parsing
7. Documented the server setup and configuration

The comments are focused on explaining the why and how of the code rather than just repeating what the code does, making them more valuable for maintenance and future development.
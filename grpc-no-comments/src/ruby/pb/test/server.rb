#!/usr/bin/env ruby

# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

this_dir = File.expand_path(File.dirname(__FILE__))
lib_dir = File.join(File.dirname(File.dirname(this_dir)), 'lib')
pb_dir = File.dirname(this_dir)
$LOAD_PATH.unshift(lib_dir) unless $LOAD_PATH.include?(lib_dir)
$LOAD_PATH.unshift(pb_dir) unless $LOAD_PATH.include?(pb_dir)
$LOAD_PATH.unshift(this_dir) unless $LOAD_PATH.include?(this_dir)

require 'forwardable'
require 'logger'
require 'optparse'

require 'grpc'

require_relative '../src/proto/grpc/testing/empty_pb'
require_relative '../src/proto/grpc/testing/messages_pb'
require_relative '../src/proto/grpc/testing/test_services_pb'

class DebugIsTruncated < Logger
  def debug(s)
    super(truncate(s, 1024))
  end

  def truncate(s, truncate_at, options = {})
    return s unless s.length > truncate_at
    omission = options[:omission] || '...'
    with_extra_room = truncate_at - omission.length
    stop = \
      if options[:separator]
        rindex(options[:separator], with_extra_room) || with_extra_room
      else
        with_extra_room
      end
    "#{s[0, stop]}#{omission}"
  end
end

module RubyLogger
  def logger
    LOGGER
  end

  LOGGER = DebugIsTruncated.new(STDOUT)
  LOGGER.level = Logger::WARN
end

module GRPC

  extend RubyLogger
end

def load_test_certs
  this_dir = File.expand_path(File.dirname(__FILE__))
  data_dir = File.join(File.dirname(File.dirname(this_dir)), 'spec/testdata')
  files = ['ca.pem', 'server1.key', 'server1.pem']
  files.map { |f| File.open(File.join(data_dir, f)).read }
end

def test_server_creds
  certs = load_test_certs
  GRPC::Core::ServerCredentials.new(
      nil, [{private_key: certs[1], cert_chain: certs[2]}], false)
end

def nulls(l)
  fail 'requires #{l} to be +ve' if l < 0
  [].pack('x' * l).force_encoding('ascii-8bit')
end

def maybe_echo_metadata(_call)

  initial_metadata_key = "x-grpc-test-echo-initial"
  trailing_metadata_key = "x-grpc-test-echo-trailing-bin"

  if _call.metadata.has_key?(initial_metadata_key)
    _call.metadata_to_send[initial_metadata_key] = _call.metadata[initial_metadata_key]
  end
  if _call.metadata.has_key?(trailing_metadata_key)
    _call.output_metadata[trailing_metadata_key] = _call.metadata[trailing_metadata_key]
  end
end

def maybe_echo_status_and_message(req)
  unless req.response_status.nil?
    fail GRPC::BadStatus.new_status_exception(
        req.response_status.code, req.response_status.message)
  end
end

class FullDuplexEnumerator
  include Grpc::Testing
  include Grpc::Testing::PayloadType

  def initialize(requests)
    @requests = requests
  end
  def each_item
    return enum_for(:each_item) unless block_given?
    GRPC.logger.info('interop-server: started receiving')
    begin
      cls = StreamingOutputCallResponse
      @requests.each do |req|
        maybe_echo_status_and_message(req)
        req.response_parameters.each do |params|
          resp_size = params.size
          GRPC.logger.info("read a req, response size is #{resp_size}")
          yield cls.new(payload: Payload.new(type: req.response_type,
                                              body: nulls(resp_size)))
        end
      end
      GRPC.logger.info('interop-server: finished receiving')
    rescue StandardError => e
      GRPC.logger.info('interop-server: failed')
      GRPC.logger.warn(e)
      fail e
    end
  end
end

class TestTarget < Grpc::Testing::TestService::Service
  include Grpc::Testing
  include Grpc::Testing::PayloadType

  def empty_call(_empty, _call)
    Empty.new
  end

  def unary_call(simple_req, _call)
    maybe_echo_metadata(_call)
    maybe_echo_status_and_message(simple_req)
    req_size = simple_req.response_size
    SimpleResponse.new(payload: Payload.new(type: :COMPRESSABLE,
                                            body: nulls(req_size)))
  end

  def streaming_input_call(call)
    sizes = call.each_remote_read.map { |x| x.payload.body.length }
    sum = sizes.inject(0) { |s, x| s + x }
    StreamingInputCallResponse.new(aggregated_payload_size: sum)
  end

  def streaming_output_call(req, _call)
    cls = StreamingOutputCallResponse
    req.response_parameters.map do |p|
      cls.new(payload: Payload.new(type: req.response_type,
                                   body: nulls(p.size)))
    end
  end

  def full_duplex_call(reqs, _call)
    maybe_echo_metadata(_call)

    FullDuplexEnumerator.new(reqs).each_item
  end

  def half_duplex_call(reqs)
    # TODO: update with unique behaviour of the half_duplex_call if that's

    full_duplex_call(reqs)
  end
end

def parse_options
  options = {
    'port' => nil,
    'secure' => false
  }
  OptionParser.new do |opts|
    opts.banner = 'Usage: --port port'
    opts.on('--port PORT', 'server port') do |v|
      options['port'] = v
    end
    opts.on('--use_tls USE_TLS', ['false', 'true'],
            'require a secure connection?') do |v|
      options['secure'] = v == 'true'
    end
  end.parse!

  if options['port'].nil?
    fail(OptionParser::MissingArgument, 'please specify --port')
  end
  options
end

def main
  opts = parse_options
  host = "0.0.0.0:#{opts['port']}"
  s = GRPC::RpcServer.new
  if opts['secure']
    s.add_http2_port(host, test_server_creds)
    GRPC.logger.info("... running securely on #{host}")
  else
    s.add_http2_port(host, :this_port_is_insecure)
    GRPC.logger.info("... running insecurely on #{host}")
  end
  s.handle(TestTarget)
  s.run_till_terminated
end

main

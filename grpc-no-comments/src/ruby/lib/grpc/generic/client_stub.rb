# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require_relative 'active_call'
require_relative '../version'

module GRPC

  class ClientStub
    include Core::StatusCodes
    include Core::TimeConsts

    DEFAULT_TIMEOUT = INFINITE_FUTURE

    def self.setup_channel(alt_chan, host, creds, channel_args = {})
      unless alt_chan.nil?
        fail(TypeError, '!Channel') unless alt_chan.is_a?(Core::Channel)
        return alt_chan
      end
      if channel_args['grpc.primary_user_agent'].nil?
        channel_args['grpc.primary_user_agent'] = ''
      else
        channel_args['grpc.primary_user_agent'] += ' '
      end
      channel_args['grpc.primary_user_agent'] += "grpc-ruby/#{VERSION}"
      unless creds.is_a?(Core::ChannelCredentials) ||
             creds.is_a?(Core::XdsChannelCredentials) ||
             creds.is_a?(Symbol)
        fail(TypeError, 'creds is not a ChannelCredentials, XdsChannelCredentials, or Symbol')
      end
      Core::Channel.new(host, channel_args, creds)
    end

    attr_writer :propagate_mask

    def initialize(host, creds,
                   channel_override: nil,
                   timeout: nil,
                   propagate_mask: nil,
                   channel_args: {},
                   interceptors: [])
      @ch = ClientStub.setup_channel(channel_override, host, creds,
                                     channel_args.dup)
      alt_host = channel_args[Core::Channel::SSL_TARGET]
      @host = alt_host.nil? ? host : alt_host
      @propagate_mask = propagate_mask
      @timeout = timeout.nil? ? DEFAULT_TIMEOUT : timeout
      @interceptors = InterceptorRegistry.new(interceptors)
    end

    def request_response(method, req, marshal, unmarshal,
                         deadline: nil,
                         return_op: false,
                         parent: nil,
                         credentials: nil,
                         metadata: {})
      c = new_active_call(method, marshal, unmarshal,
                          deadline: deadline,
                          parent: parent,
                          credentials: credentials)
      interception_context = @interceptors.build_context
      intercept_args = {
        method: method,
        request: req,
        call: c.interceptable,
        metadata: metadata
      }
      if return_op

        c.merge_metadata_to_send(metadata)
        op = c.operation
        op.define_singleton_method(:execute) do
          interception_context.intercept!(:request_response, intercept_args) do
            c.request_response(req, metadata: metadata)
          end
        end
        op
      else
        interception_context.intercept!(:request_response, intercept_args) do
          c.request_response(req, metadata: metadata)
        end
      end
    end

    def client_streamer(method, requests, marshal, unmarshal,
                        deadline: nil,
                        return_op: false,
                        parent: nil,
                        credentials: nil,
                        metadata: {})
      c = new_active_call(method, marshal, unmarshal,
                          deadline: deadline,
                          parent: parent,
                          credentials: credentials)
      interception_context = @interceptors.build_context
      intercept_args = {
        method: method,
        requests: requests,
        call: c.interceptable,
        metadata: metadata
      }
      if return_op

        c.merge_metadata_to_send(metadata)
        op = c.operation
        op.define_singleton_method(:execute) do
          interception_context.intercept!(:client_streamer, intercept_args) do
            c.client_streamer(requests)
          end
        end
        op
      else
        interception_context.intercept!(:client_streamer, intercept_args) do
          c.client_streamer(requests, metadata: metadata)
        end
      end
    end

    def server_streamer(method, req, marshal, unmarshal,
                        deadline: nil,
                        return_op: false,
                        parent: nil,
                        credentials: nil,
                        metadata: {},
                        &blk)
      c = new_active_call(method, marshal, unmarshal,
                          deadline: deadline,
                          parent: parent,
                          credentials: credentials)
      interception_context = @interceptors.build_context
      intercept_args = {
        method: method,
        request: req,
        call: c.interceptable,
        metadata: metadata
      }
      if return_op

        c.merge_metadata_to_send(metadata)
        op = c.operation
        op.define_singleton_method(:execute) do
          interception_context.intercept!(:server_streamer, intercept_args) do
            c.server_streamer(req, &blk)
          end
        end
        op
      else
        interception_context.intercept!(:server_streamer, intercept_args) do
          c.server_streamer(req, metadata: metadata, &blk)
        end
      end
    end

    def bidi_streamer(method, requests, marshal, unmarshal,
                      deadline: nil,
                      return_op: false,
                      parent: nil,
                      credentials: nil,
                      metadata: {},
                      &blk)
      c = new_active_call(method, marshal, unmarshal,
                          deadline: deadline,
                          parent: parent,
                          credentials: credentials)
      interception_context = @interceptors.build_context
      intercept_args = {
        method: method,
        requests: requests,
        call: c.interceptable,
        metadata: metadata
      }
      if return_op

        c.merge_metadata_to_send(metadata)
        op = c.operation
        op.define_singleton_method(:execute) do
          interception_context.intercept!(:bidi_streamer, intercept_args) do
            c.bidi_streamer(requests, &blk)
          end
        end
        op
      else
        interception_context.intercept!(:bidi_streamer, intercept_args) do
          c.bidi_streamer(requests, metadata: metadata, &blk)
        end
      end
    end

    private

    def new_active_call(method, marshal, unmarshal,
                        deadline: nil,
                        parent: nil,
                        credentials: nil)
      deadline = from_relative_time(@timeout) if deadline.nil?

      call = @ch.create_call(parent,
                             @propagate_mask,
                             method,
                             nil,
                             deadline)
      call.set_credentials! credentials unless credentials.nil?
      ActiveCall.new(call, marshal, unmarshal, deadline,
                     started: false)
    end
  end
end

# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require_relative '../grpc'

module GRPC

  class RpcDesc < Struct.new(:name, :input, :output, :marshal_method,
                             :unmarshal_method)
    include Core::StatusCodes

    class Stream
      attr_accessor :type

      def initialize(type)
        @type = type
      end
    end

    def marshal_proc
      proc { |o| o.class.send(marshal_method, o).to_s }
    end

    def unmarshal_proc(target)
      fail ArgumentError unless [:input, :output].include?(target)
      unmarshal_class = send(target)
      unmarshal_class = unmarshal_class.type if unmarshal_class.is_a? Stream
      proc { |o| unmarshal_class.send(unmarshal_method, o) }
    end

    def handle_request_response(active_call, mth, inter_ctx)
      req = active_call.read_unary_request
      call = active_call.single_req_view

      inter_ctx.intercept!(
        :request_response,
        method: mth,
        call: call,
        request: req
      ) do
        resp = mth.call(req, call)
        active_call.server_unary_response(
          resp,
          trailing_metadata: active_call.output_metadata
        )
      end
    end

    def handle_client_streamer(active_call, mth, inter_ctx)
      call = active_call.multi_req_view

      inter_ctx.intercept!(
        :client_streamer,
        method: mth,
        call: call
      ) do
        resp = mth.call(call)
        active_call.server_unary_response(
          resp,
          trailing_metadata: active_call.output_metadata
        )
      end
    end

    def handle_server_streamer(active_call, mth, inter_ctx)
      req = active_call.read_unary_request
      call = active_call.single_req_view

      inter_ctx.intercept!(
        :server_streamer,
        method: mth,
        call: call,
        request: req
      ) do
        replies = mth.call(req, call)
        replies.each { |r| active_call.remote_send(r) }
        send_status(active_call, OK, 'OK', active_call.output_metadata)
      end
    end

    def handle_bidi_streamer(active_call, mth, inter_ctx)
      active_call.run_server_bidi(mth, inter_ctx)
      send_status(active_call, OK, 'OK', active_call.output_metadata)
    end

    def run_server_method(active_call, mth, inter_ctx = InterceptionContext.new)

      if request_response?
        handle_request_response(active_call, mth, inter_ctx)
      elsif client_streamer?
        handle_client_streamer(active_call, mth, inter_ctx)
      elsif server_streamer?
        handle_server_streamer(active_call, mth, inter_ctx)
      else
        handle_bidi_streamer(active_call, mth, inter_ctx)
      end
    rescue BadStatus => e

      GRPC.logger.debug("app err:#{active_call}, status:#{e.code}:#{e.details}")
      send_status(active_call, e.code, e.details, e.metadata)
    rescue Core::CallError => e

      GRPC.logger.warn("failed call: #{active_call}\n#{e}")
    rescue Core::OutOfTime

      GRPC.logger.warn("late call: #{active_call}")
      send_status(active_call, DEADLINE_EXCEEDED, 'late')
    rescue StandardError, NotImplementedError => e

      # Note: this intentionally does not map NotImplementedError to

      GRPC.logger.warn("failed handler: #{active_call}; sending status:UNKNOWN")
      GRPC.logger.warn(e)
      send_status(active_call, UNKNOWN, "#{e.class}: #{e.message}")
    end

    def assert_arity_matches(mth)

      if bidi_streamer?
        if mth.arity != 2 && mth.arity != 1
          fail arity_error(mth, 2, "should be #{mth.name}(req, call) or " \
            "#{mth.name}(req)")
        end
      elsif request_response? || server_streamer?
        if mth.arity != 2
          fail arity_error(mth, 2, "should be #{mth.name}(req, call)")
        end
      else
        if mth.arity != 1
          fail arity_error(mth, 1, "should be #{mth.name}(call)")
        end
      end
    end

    def request_response?
      !input.is_a?(Stream) && !output.is_a?(Stream)
    end

    def client_streamer?
      input.is_a?(Stream) && !output.is_a?(Stream)
    end

    def server_streamer?
      !input.is_a?(Stream) && output.is_a?(Stream)
    end

    def bidi_streamer?
      input.is_a?(Stream) && output.is_a?(Stream)
    end

    def arity_error(mth, want, msg)
      "##{mth.name}: bad arg count; got:#{mth.arity}, want:#{want}, #{msg}"
    end

    def send_status(active_client, code, details, metadata = {})
      details = 'Not sure why' if details.nil?
      GRPC.logger.debug("Sending status  #{code}:#{details}")
      active_client.send_status(code, details, code == OK, metadata: metadata)
    rescue StandardError => e
      GRPC.logger.warn("Could not send status #{code}:#{details}")
      GRPC.logger.warn(e)
    end
  end
end

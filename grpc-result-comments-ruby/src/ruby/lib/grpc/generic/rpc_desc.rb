Here's the commented version of the code:

```c++
# Copyright 2015 gRPC authors.
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

require_relative '../grpc'

module GRPC
  # Describes an RPC method, including its name, input/output types,
  # and marshaling/unmarshaling methods.
  class RpcDesc < Struct.new(:name, :input, :output, :marshal_method,
                             :unmarshal_method)
    include Core::StatusCodes

    # Represents a streaming type (either input or output stream)
    class Stream
      attr_accessor :type

      def initialize(type)
        @type = type
      end
    end

    # Returns a proc that marshals an object using the specified marshal method
    def marshal_proc
      proc { |o| o.class.send(marshal_method, o).to_s }
    end

    # Returns a proc that unmarshals an object for the given target (input/output)
    # Raises ArgumentError if target is neither :input nor :output
    def unmarshal_proc(target)
      fail ArgumentError unless [:input, :output].include?(target)
      unmarshal_class = send(target)
      unmarshal_class = unmarshal_class.type if unmarshal_class.is_a? Stream
      proc { |o| unmarshal_class.send(unmarshal_method, o) }
    end

    # Handles a unary request-response RPC call
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

    # Handles a client streaming RPC call
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

    # Handles a server streaming RPC call
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

    # Handles a bidirectional streaming RPC call
    def handle_bidi_streamer(active_call, mth, inter_ctx)
      active_call.run_server_bidi(mth, inter_ctx)
      send_status(active_call, OK, 'OK', active_call.output_metadata)
    end

    # Runs the appropriate server method handler based on the RPC type
    # Handles various error cases and sends appropriate status responses
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
      # Handle application-level errors
      GRPC.logger.debug("app err:#{active_call}, status:#{e.code}:#{e.details}")
      send_status(active_call, e.code, e.details, e.metadata)
    rescue Core::CallError => e
      # Handle gRPC call errors
      GRPC.logger.warn("failed call: #{active_call}\n#{e}")
    rescue Core::OutOfTime
      # Handle deadline exceeded errors
      GRPC.logger.warn("late call: #{active_call}")
      send_status(active_call, DEADLINE_EXCEEDED, 'late')
    rescue StandardError, NotImplementedError => e
      # Handle all other unexpected errors
      GRPC.logger.warn("failed handler: #{active_call}; sending status:UNKNOWN")
      GRPC.logger.warn(e)
      send_status(active_call, UNKNOWN, "#{e.class}: #{e.message}")
    end

    # Verifies that the method arity matches the expected count for the RPC type
    # Raises an error if the arity doesn't match
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

    # Returns true if this is a unary request-response RPC
    def request_response?
      !input.is_a?(Stream) && !output.is_a?(Stream)
    end

    # Returns true if this is a client streaming RPC
    def client_streamer?
      input.is_a?(Stream) && !output.is_a?(Stream)
    end

    # Returns true if this is a server streaming RPC
    def server_streamer?
      !input.is_a?(Stream) && output.is_a?(Stream)
    end

    # Returns true if this is a bidirectional streaming RPC
    def bidi_streamer?
      input.is_a?(Stream) && output.is_a?(Stream)
    end

    # Generates an error message for incorrect method arity
    def arity_error(mth, want, msg)
      "##{mth.name}: bad arg count; got:#{mth.arity}, want:#{want}, #{msg}"
    end

    # Sends the final status for an RPC call
    # Handles errors that might occur during status sending
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
```

The comments provide:
1. Class-level documentation explaining the purpose of RpcDesc
2. Method-level documentation explaining what each method does
3. Parameter and return value explanations where relevant
4. Error handling explanations
5. Clarification of the different RPC types (unary, client streaming, server streaming, bidirectional)
6. Important implementation details
7. Logging behavior explanations

The comments are concise yet informative, helping future developers understand the code's purpose and behavior without being overly verbose.
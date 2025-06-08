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

require 'forwardable'
require 'weakref'
require_relative 'bidi_call'

class Struct
  # Represents the result of a batch operation in gRPC
  class BatchResult
    # Checks the status of the batch operation
    # @return [Status] the status if it's OK
    # @raise [GRPC::BadStatus] if the status is not OK
    def check_status
      return nil if status.nil?
      if status.code != GRPC::Core::StatusCodes::OK
        GRPC.logger.debug("Failing with status #{status}")

        fail GRPC::BadStatus.new_status_exception(
          status.code, status.details, status.metadata,
          status.debug_error_string)
      end
      status
    end
  end
end

module GRPC
  # Represents an active gRPC call, handling both client and server operations
  class ActiveCall
    include Core::TimeConsts
    include Core::CallOps
    extend Forwardable
    
    # Reader attributes for call properties
    attr_reader :deadline, :metadata_sent, :metadata_to_send, :peer, :peer_cert
    
    # Delegates these methods to the underlying @call object
    def_delegators :@call, :cancel, :cancel_with_status, :metadata,
                   :write_flag, :write_flag=, :trailing_metadata, :status

    # Initializes a client invocation
    # @param call [Core::Call] the gRPC call object
    # @param metadata [Hash] initial metadata to send
    def self.client_invoke(call, metadata = {})
      fail(TypeError, '!Core::Call') unless call.is_a? Core::Call
      call.run_batch(SEND_INITIAL_METADATA => metadata)
    end

    # Initializes a new ActiveCall
    # @param call [Core::Call] the gRPC call object
    # @param marshal [Proc] marshaling function for requests
    # @param unmarshal [Proc] unmarshaling function for responses
    # @param deadline [Time] call deadline
    # @param started [Boolean] whether call has started
    # @param metadata_received [Boolean] whether metadata was received
    # @param metadata_to_send [Hash] metadata to send
    def initialize(call, marshal, unmarshal, deadline, started: true,
                   metadata_received: false, metadata_to_send: nil)
      fail(TypeError, '!Core::Call') unless call.is_a? Core::Call
      @call = call
      @deadline = deadline
      @marshal = marshal
      @unmarshal = unmarshal
      @metadata_received = metadata_received
      @metadata_sent = started
      @op_notifier = nil

      fail(ArgumentError, 'Already sent md') if started && metadata_to_send
      @metadata_to_send = metadata_to_send || {} unless started
      @send_initial_md_mutex = Mutex.new

      @output_stream_done = false
      @input_stream_done = false
      @call_finished = false
      @call_finished_mu = Mutex.new

      @client_call_executed = false
      @client_call_executed_mu = Mutex.new

      @peer = call.peer
    end

    # Sends initial metadata if not already sent
    # @param new_metadata [Hash] additional metadata to merge
    def send_initial_metadata(new_metadata = {})
      @send_initial_md_mutex.synchronize do
        return if @metadata_sent
        @metadata_to_send.merge!(new_metadata)
        ActiveCall.client_invoke(@call, @metadata_to_send)
        @metadata_sent = true
      end
    end

    # @return [Hash] output metadata
    def output_metadata
      @output_metadata ||= {}
    end

    # @return [Boolean] whether the call was cancelled
    def cancelled?
      !@call.status.nil? && @call.status.code == Core::StatusCodes::CANCELLED
    end

    # @return [MultiReqView] a view for multiple requests
    def multi_req_view
      MultiReqView.new(self)
    end

    # @return [SingleReqView] a view for single request
    def single_req_view
      SingleReqView.new(self)
    end

    # @return [Operation] creates a new operation for this call
    def operation
      @op_notifier = Notifier.new
      Operation.new(self)
    end

    # @return [InterceptableView] creates an interceptable view
    def interceptable
      InterceptableView.new(self)
    end

    # Receives and checks the final status of the call
    # @return [Status] the call status
    def receive_and_check_status
      ops = { RECV_STATUS_ON_CLIENT => nil }
      ops[RECV_INITIAL_METADATA] = nil unless @metadata_received
      batch_result = @call.run_batch(ops)
      unless @metadata_received
        @call.metadata = batch_result.metadata
      end
      set_input_stream_done
      attach_status_results_and_complete_call(batch_result)
    ensure
      @metadata_received = true
    end

    # Attaches status results and completes the call
    # @param recv_status_batch_result [BatchResult] the batch result
    def attach_status_results_and_complete_call(recv_status_batch_result)
      unless recv_status_batch_result.status.nil?
        @call.trailing_metadata = recv_status_batch_result.status.metadata
      end
      @call.status = recv_status_batch_result.status

      recv_status_batch_result.check_status
    end

    # Sends a request to the remote
    # @param req [Object] the request to send
    # @param marshalled [Boolean] whether the request is already marshalled
    def remote_send(req, marshalled = false)
      send_initial_metadata
      GRPC.logger.debug("sending #{req}, marshalled? #{marshalled}")
      payload = marshalled ? req : @marshal.call(req)
      @call.run_batch(SEND_MESSAGE => payload)
    end

    # Sends the final status from server
    # @param code [Integer] status code
    # @param details [String] status details
    # @param assert_finished [Boolean] whether to assert call is finished
    # @param metadata [Hash] trailing metadata
    def send_status(code = OK, details = '', assert_finished = false,
                    metadata: {})
      send_initial_metadata
      ops = {
        SEND_STATUS_FROM_SERVER => Struct::Status.new(code, details, metadata)
      }
      ops[RECV_CLOSE_ON_SERVER] = nil if assert_finished
      @call.run_batch(ops)
      set_output_stream_done

      nil
    end

    # Reads a unary request
    # @return [Object] the unmarshalled request
    def read_unary_request
      req = remote_read
      set_input_stream_done
      req
    end

    # Sends a unary response from server
    # @param req [Object] the response to send
    # @param trailing_metadata [Hash] trailing metadata
    # @param code [Integer] status code
    # @param details [String] status details
    def server_unary_response(req, trailing_metadata: {},
                              code: Core::StatusCodes::OK, details: 'OK')
      ops = {}
      ops[SEND_MESSAGE] = @marshal.call(req)
      ops[SEND_STATUS_FROM_SERVER] = Struct::Status.new(
        code, details, trailing_metadata)
      ops[RECV_CLOSE_ON_SERVER] = nil

      @send_initial_md_mutex.synchronize do
        ops[SEND_INITIAL_METADATA] = @metadata_to_send unless @metadata_sent
        @metadata_sent = true
      end

      @call.run_batch(ops)
      set_output_stream_done
    end

    # Reads a message from the remote
    # @return [Object] the unmarshalled message or nil
    def remote_read
      ops = { RECV_MESSAGE => nil }
      ops[RECV_INITIAL_METADATA] = nil unless @metadata_received
      batch_result = @call.run_batch(ops)
      unless @metadata_received
        @call.metadata = batch_result.metadata
      end
      get_message_from_batch_result(batch_result)
    rescue GRPC::Core::CallError => e
      GRPC.logger.info("remote_read: #{e}")
      nil
    ensure
      @metadata_received = true
    end

    # Extracts message from batch result
    # @param recv_message_batch_result [BatchResult] the batch result
    # @return [Object] the unmarshalled message or nil
    def get_message_from_batch_result(recv_message_batch_result)
      unless recv_message_batch_result.nil? ||
             recv_message_batch_result.message.nil?
        return @unmarshal.call(recv_message_batch_result.message)
      end
      GRPC.logger.debug('found nil; the final response has been sent')
      nil
    end

    # Enumerates over remote reads
    # @yield [Object] each received message
    # @return [Enumerator] if no block given
    def each_remote_read
      return enum_for(:each_remote_read) unless block_given?
      begin
        loop do
          resp = remote_read
          break if resp.nil?
          yield resp
        end
      ensure
        set_input_stream_done
      end
    end

    # Enumerates over remote reads then checks final status
    # @yield [Object] each received message
    # @return [Enumerator] if no block given
    def each_remote_read_then_finish
      return enum_for(:each_remote_read_then_finish) unless block_given?
      loop do
        resp = remote_read
        break if resp.nil?
        yield resp
      end

      receive_and_check_status
    ensure
      set_input_stream_done
    end

    # Performs a request-response call
    # @param req [Object] the request to send
    # @param metadata [Hash] additional metadata
    # @return [Object] the response
    def request_response(req, metadata: {})
      raise_error_if_already_executed
      ops = {
        SEND_MESSAGE => @marshal.call(req),
        SEND_CLOSE_FROM_CLIENT => nil,
        RECV_INITIAL_METADATA => nil,
        RECV_MESSAGE => nil,
        RECV_STATUS_ON_CLIENT => nil
      }
      @send_initial_md_mutex.synchronize do
        unless @metadata_sent
          ops[SEND_INITIAL_METADATA] = @metadata_to_send.merge!(metadata)
        end
        @metadata_sent = true
      end

      begin
        batch_result = @call.run_batch(ops)
      ensure
        set_input_stream_done
        set_output_stream_done
      end

      @call.metadata = batch_result.metadata
      attach_status_results_and_complete_call(batch_result)
      get_message_from_batch_result(batch_result)
    end

    # Performs a client streaming call
    # @param requests [Enumerable] the requests to stream
    # @param metadata [Hash] additional metadata
    # @return [Object] the response
    def client_streamer(requests, metadata: {})
      raise_error_if_already_executed
      begin
        send_initial_metadata(metadata)
        requests.each { |r| @call.run_batch(SEND_MESSAGE => @marshal.call(r)) }
      rescue GRPC::Core::CallError => e
        receive_and_check_status
        raise e
      rescue => e
        set_input_stream_done
        raise e
      ensure
        set_output_stream_done
      end

      batch_result = @call.run_batch(
        SEND_CLOSE_FROM_CLIENT => nil,
        RECV_INITIAL_METADATA => nil,
        RECV_MESSAGE => nil,
        RECV_STATUS_ON_CLIENT => nil
      )

      set_input_stream_done

      @call.metadata = batch_result.metadata
      attach_status_results_and_complete_call(batch_result)
      get_message_from_batch_result(batch_result)
    end

    # Performs a server streaming call
    # @param req [Object] the initial request
    # @param metadata [Hash] additional metadata
    # @yield [Object] each received message
    # @return [Enumerator] if no block given
    def server_streamer(req, metadata: {})
      raise_error_if_already_executed
      ops = {
        SEND_MESSAGE => @marshal.call(req),
        SEND_CLOSE_FROM_CLIENT => nil
      }
      @send_initial_md_mutex.synchronize do
        unless @metadata_sent
          ops[SEND_INITIAL_METADATA] = @metadata_to_send.merge!(metadata)
        end
        @metadata_sent = true
      end

      begin
        @call.run_batch(ops)
      rescue GRPC::Core::CallError => e
        receive_and_check_status
        raise e
      rescue => e
        set_input_stream_done
        raise e
      ensure
        set_output_stream_done
      end

      replies = enum_for(:each_remote_read_then_finish)
      return replies unless block_given?
      replies.each { |r| yield r }
    end

    # Performs a bidirectional streaming call
    # @param requests [Enumerable] the requests to stream
    # @param metadata [Hash] additional metadata
    # @yield [Object] each received message
    def bidi_streamer(requests, metadata: {}, &blk)
      raise_error_if_already_executed

      begin
        send_initial_metadata(metadata)
      rescue GRPC::Core::CallError => e
        batch_result = @call.run_batch(RECV_STATUS_ON_CLIENT => nil)
        set_input_stream_done
        set_output_stream_done
        attach_status_results_and_complete_call(batch_result)
        raise e
      rescue => e
        set_input_stream_done
        set_output_stream_done
        raise e
      end

      bd = BidiCall.new(@call,
                        @marshal,
                        @unmarshal,
                        metadata_received: @metadata_received)

      bd.run_on_client(requests,
                       proc { set_input_stream_done },
                       proc { set_output_stream_done },
                       &blk)
    end

    # Runs a server-side bidirectional streaming call
    # @param mth [Method] the method being called
    # @param interception_ctx [InterceptionContext] interception context
    def run_server_bidi(mth, interception_ctx)
      view = multi_req_view
      bidi_call = BidiCall.new(
        @call,
        @marshal,
        @unmarshal,
        metadata_received: @metadata_received,
        req_view: view
      )
      requests = bidi_call.read_next_loop(proc { set_input_stream_done }, false)
      interception_ctx.intercept!(
        :bidi_streamer,
        call: view,
        method: mth,
        requests: requests
      ) do
        bidi_call.run_on_server(mth, requests)
      end
    end

    # Waits for the operation to complete
    def wait
      return if @op_notifier.nil?
      GRPC.logger.debug("active_call.wait: on #{@op_notifier}")
      @op_notifier.wait
    end

    # Notifies that the operation is done
    def op_is_done
      return if @op_notifier.nil?
      @op_notifier.notify(self)
    end

    # Merges additional metadata to send
    # @param new_metadata [Hash] metadata to merge
    def merge_metadata_to_send(new_metadata = {})
      @send_initial_md_mutex.synchronize do
        fail('cant change metadata after already sent') if @metadata_sent
        @metadata_to_send.merge!(new_metadata)
      end
    end

    # Attaches peer certificate to the call
    # @param peer_cert [Object] the peer certificate
    def attach_peer_cert(peer_cert)
      @peer_cert = peer_cert
    end

    private

    # Marks the input stream as done
    def set_input_stream_done
      @call_finished_mu.synchronize do
        @input_stream_done = true
        maybe_finish_and_close_call_locked
      end
    end

    # Marks the output stream as done
    def set_output_stream_done
      @call_finished_mu.synchronize do
        @output_stream_done = true
        maybe_finish_and_close_call_locked
      end
    end

    # Finishes and closes the call if both streams are done
    def maybe_finish_and_close_call_locked
      return unless @output_stream_done && @input_stream_done
      return if @call_finished
      @call_finished = true
      op_is_done
      @call.close
    end

    # Starts the call with given metadata
    # @param metadata [Hash] metadata to send
    def start_call(metadata = {})
      merge_metadata_to_send(metadata) && send_initial_metadata
    end

    # Raises error if call was already executed
    def raise_error_if_already_executed
      @client_call_executed_mu.synchronize do
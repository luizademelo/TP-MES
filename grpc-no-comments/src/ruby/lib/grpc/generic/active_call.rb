# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'forwardable'
require 'weakref'
require_relative 'bidi_call'

class Struct

  class BatchResult

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

  class ActiveCall
    include Core::TimeConsts
    include Core::CallOps
    extend Forwardable
    attr_reader :deadline, :metadata_sent, :metadata_to_send, :peer, :peer_cert
    def_delegators :@call, :cancel, :cancel_with_status, :metadata,
                   :write_flag, :write_flag=, :trailing_metadata, :status

    def self.client_invoke(call, metadata = {})
      fail(TypeError, '!Core::Call') unless call.is_a? Core::Call
      call.run_batch(SEND_INITIAL_METADATA => metadata)
    end

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

    def send_initial_metadata(new_metadata = {})
      @send_initial_md_mutex.synchronize do
        return if @metadata_sent
        @metadata_to_send.merge!(new_metadata)
        ActiveCall.client_invoke(@call, @metadata_to_send)
        @metadata_sent = true
      end
    end

    def output_metadata
      @output_metadata ||= {}
    end

    def cancelled?
      !@call.status.nil? && @call.status.code == Core::StatusCodes::CANCELLED
    end

    def multi_req_view
      MultiReqView.new(self)
    end

    def single_req_view
      SingleReqView.new(self)
    end

    def operation
      @op_notifier = Notifier.new
      Operation.new(self)
    end

    def interceptable
      InterceptableView.new(self)
    end

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

    def attach_status_results_and_complete_call(recv_status_batch_result)
      unless recv_status_batch_result.status.nil?
        @call.trailing_metadata = recv_status_batch_result.status.metadata
      end
      @call.status = recv_status_batch_result.status

      recv_status_batch_result.check_status
    end

    def remote_send(req, marshalled = false)
      send_initial_metadata
      GRPC.logger.debug("sending #{req}, marshalled? #{marshalled}")
      payload = marshalled ? req : @marshal.call(req)
      @call.run_batch(SEND_MESSAGE => payload)
    end

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

    def read_unary_request
      req = remote_read
      set_input_stream_done
      req
    end

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

    def get_message_from_batch_result(recv_message_batch_result)
      unless recv_message_batch_result.nil? ||
             recv_message_batch_result.message.nil?
        return @unmarshal.call(recv_message_batch_result.message)
      end
      GRPC.logger.debug('found nil; the final response has been sent')
      nil
    end

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

    def wait
      return if @op_notifier.nil?
      GRPC.logger.debug("active_call.wait: on #{@op_notifier}")
      @op_notifier.wait
    end

    def op_is_done
      return if @op_notifier.nil?
      @op_notifier.notify(self)
    end

    def merge_metadata_to_send(new_metadata = {})
      @send_initial_md_mutex.synchronize do
        fail('cant change metadata after already sent') if @metadata_sent
        @metadata_to_send.merge!(new_metadata)
      end
    end

    def attach_peer_cert(peer_cert)
      @peer_cert = peer_cert
    end

    private

    def set_input_stream_done
      @call_finished_mu.synchronize do
        @input_stream_done = true
        maybe_finish_and_close_call_locked
      end
    end

    def set_output_stream_done
      @call_finished_mu.synchronize do
        @output_stream_done = true
        maybe_finish_and_close_call_locked
      end
    end

    def maybe_finish_and_close_call_locked
      return unless @output_stream_done && @input_stream_done
      return if @call_finished
      @call_finished = true
      op_is_done
      @call.close
    end

    def start_call(metadata = {})

      merge_metadata_to_send(metadata) && send_initial_metadata
    end

    def raise_error_if_already_executed
      @client_call_executed_mu.synchronize do
        if @client_call_executed
          fail GRPC::Core::CallError, 'attempting to re-run a call'
        end
        @client_call_executed = true
      end
    end

    def self.view_class(*visible_methods)
      Class.new do
        extend ::Forwardable
        def_delegators :@wrapped, *visible_methods

        def initialize(wrapped)
          @wrapped = wrapped
        end
      end
    end

    SingleReqView = view_class(:cancelled?, :deadline, :metadata,
                               :output_metadata, :peer, :peer_cert,
                               :send_initial_metadata,
                               :metadata_to_send,
                               :merge_metadata_to_send,
                               :metadata_sent)

    MultiReqView = view_class(:cancelled?, :deadline,
                              :each_remote_read, :metadata, :output_metadata,
                              :peer, :peer_cert,
                              :send_initial_metadata,
                              :metadata_to_send,
                              :merge_metadata_to_send,
                              :metadata_sent)

    Operation = view_class(:cancel, :cancel_with_status, :cancelled?, :deadline,
                           :execute, :metadata, :status, :start_call, :wait,
                           :write_flag, :write_flag=, :trailing_metadata)

    InterceptableView = view_class(:deadline)
  end
end

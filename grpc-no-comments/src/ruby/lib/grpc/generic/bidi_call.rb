# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'forwardable'
require_relative '../grpc'

module GRPC

  class BidiCall
    include Core::CallOps
    include Core::StatusCodes
    include Core::TimeConsts

    def initialize(call, marshal, unmarshal, metadata_received: false,
                   req_view: nil)
      fail(ArgumentError, 'not a call') unless call.is_a? Core::Call
      @call = call
      @marshal = marshal
      @op_notifier = nil
      @unmarshal = unmarshal
      @metadata_received = metadata_received
      @reads_complete = false
      @writes_complete = false
      @complete = false
      @done_mutex = Mutex.new
      @req_view = req_view
    end

    def run_on_client(requests,
                      set_input_stream_done,
                      set_output_stream_done,
                      &blk)
      @enq_th = Thread.new do
        write_loop(requests, set_output_stream_done: set_output_stream_done)
      end
      read_loop(set_input_stream_done, &blk)
    end

    def run_on_server(gen_each_reply, requests)
      replies = nil

      if gen_each_reply.arity == 1
        replies = gen_each_reply.call(requests)
      elsif gen_each_reply.arity == 2
        replies = gen_each_reply.call(requests, @req_view)
      else
        fail 'Illegal arity of reply generator'
      end

      write_loop(replies, is_client: false)
    end

    def read_next_loop(finalize_stream, is_client = false)
      read_loop(finalize_stream, is_client: is_client)
    end

    private

    END_OF_READS = :end_of_reads
    END_OF_WRITES = :end_of_writes

    def read_using_run_batch
      ops = { RECV_MESSAGE => nil }
      ops[RECV_INITIAL_METADATA] = nil unless @metadata_received
      begin
        batch_result = @call.run_batch(ops)
        unless @metadata_received
          @call.metadata = batch_result.metadata
          @metadata_received = true
        end
        batch_result
      rescue GRPC::Core::CallError => e
        GRPC.logger.warn('bidi call: read_using_run_batch failed')
        GRPC.logger.warn(e)
        nil
      end
    end

    def write_loop(requests, is_client: true, set_output_stream_done: nil)
      GRPC::Core.fork_unsafe_begin
      GRPC.logger.debug('bidi-write-loop: starting')
      count = 0
      requests.each do |req|
        GRPC.logger.debug("bidi-write-loop: #{count}")
        count += 1
        payload = @marshal.call(req)

        begin
          @req_view.send_initial_metadata unless @req_view.nil?
          @call.run_batch(SEND_MESSAGE => payload)
        rescue GRPC::Core::CallError => e

          GRPC.logger.warn('bidi-write-loop: ended with error')
          GRPC.logger.warn(e)
          break
        end
      end
      GRPC.logger.debug("bidi-write-loop: #{count} writes done")
      if is_client
        GRPC.logger.debug("bidi-write-loop: client sent #{count}, waiting")
        begin
          @call.run_batch(SEND_CLOSE_FROM_CLIENT => nil)
        rescue GRPC::Core::CallError => e
          GRPC.logger.warn('bidi-write-loop: send close failed')
          GRPC.logger.warn(e)
        end
        GRPC.logger.debug('bidi-write-loop: done')
      end
      GRPC.logger.debug('bidi-write-loop: finished')
    rescue StandardError => e
      GRPC.logger.warn('bidi-write-loop: failed')
      GRPC.logger.warn(e)
      if is_client
        @call.cancel_with_status(GRPC::Core::StatusCodes::UNKNOWN,
                                 "GRPC bidi call error: #{e.inspect}")
      else
        raise e
      end
    ensure
      GRPC::Core.fork_unsafe_end
      set_output_stream_done.call if is_client
    end

    def read_loop(set_input_stream_done, is_client: true)
      return enum_for(:read_loop,
                      set_input_stream_done,
                      is_client: is_client) unless block_given?
      GRPC.logger.debug('bidi-read-loop: starting')
      begin
        count = 0

        loop do
          GRPC.logger.debug("bidi-read-loop: #{count}")
          count += 1
          batch_result = read_using_run_batch

          if batch_result.nil? || batch_result.message.nil?
            GRPC.logger.debug("bidi-read-loop: null batch #{batch_result}")

            if is_client
              batch_result = @call.run_batch(RECV_STATUS_ON_CLIENT => nil)
              @call.status = batch_result.status
              @call.trailing_metadata = @call.status.metadata if @call.status
              GRPC.logger.debug("bidi-read-loop: done status #{@call.status}")
              batch_result.check_status
            end

            GRPC.logger.debug('bidi-read-loop: done reading!')
            break
          end

          res = @unmarshal.call(batch_result.message)
          yield res
        end
      rescue StandardError => e
        GRPC.logger.warn('bidi: read-loop failed')
        GRPC.logger.warn(e)
        raise e
      ensure
        set_input_stream_done.call
      end
      GRPC.logger.debug('bidi-read-loop: finished')

      @enq_th.join if is_client
    end
  end
end

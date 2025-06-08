Here's the commented version of the code:

```c++
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
  # Represents a bidirectional streaming call in gRPC.
  # Handles both client and server side streaming operations.
  class BidiCall
    include Core::CallOps       # Provides gRPC call operations
    include Core::StatusCodes   # Provides gRPC status codes
    include Core::TimeConsts    # Provides time constants

    # Initializes a new bidirectional call
    # @param call [Core::Call] The gRPC call object
    # @param marshal [Proc] Method to marshal outgoing messages
    # @param unmarshal [Proc] Method to unmarshal incoming messages
    # @param metadata_received [Boolean] Flag if metadata was already received
    # @param req_view [Object] Optional request view object
    def initialize(call, marshal, unmarshal, metadata_received: false,
                   req_view: nil)
      fail(ArgumentError, 'not a call') unless call.is_a? Core::Call
      @call = call                # The underlying gRPC call object
      @marshal = marshal          # Proc to serialize outgoing messages
      @op_notifier = nil          # Operation notifier (unused in this snippet)
      @unmarshal = unmarshal      # Proc to deserialize incoming messages
      @metadata_received = metadata_received  # Metadata received flag
      @reads_complete = false     # Flag indicating reads are complete
      @writes_complete = false    # Flag indicating writes are complete
      @complete = false           # Overall completion flag
      @done_mutex = Mutex.new     # Mutex for thread safety
      @req_view = req_view        # Optional request view object
    end

    # Runs the bidirectional call on the client side
    # @param requests [Enumerable] The requests to send
    # @param set_input_stream_done [Proc] Callback when input stream completes
    # @param set_output_stream_done [Proc] Callback when output stream completes
    # @param blk [Block] Block to process received messages
    def run_on_client(requests,
                      set_input_stream_done,
                      set_output_stream_done,
                      &blk)
      # Start a thread to handle sending requests
      @enq_th = Thread.new do
        write_loop(requests, set_output_stream_done: set_output_stream_done)
      end
      # Handle receiving responses in the current thread
      read_loop(set_input_stream_done, &blk)
    end

    # Runs the bidirectional call on the server side
    # @param gen_each_reply [Proc] Generator for server responses
    # @param requests [Enumerable] The incoming requests
    def run_on_server(gen_each_reply, requests)
      replies = nil

      # Generate replies based on the generator's arity
      if gen_each_reply.arity == 1
        replies = gen_each_reply.call(requests)
      elsif gen_each_reply.arity == 2
        replies = gen_each_reply.call(requests, @req_view)
      else
        fail 'Illegal arity of reply generator'
      end

      # Send the generated replies
      write_loop(replies, is_client: false)
    end

    # Reads messages in a loop until completion
    # @param finalize_stream [Proc] Callback when stream completes
    # @param is_client [Boolean] Flag indicating if this is client-side
    def read_next_loop(finalize_stream, is_client = false)
      read_loop(finalize_stream, is_client: is_client)
    end

    private

    # Constants for stream state markers
    END_OF_READS = :end_of_reads
    END_OF_WRITES = :end_of_writes

    # Reads a message using the gRPC batch operation
    # @return [BatchResult] The result of the read operation
    def read_using_run_batch
      ops = { RECV_MESSAGE => nil }
      # Include metadata receive if not already received
      ops[RECV_INITIAL_METADATA] = nil unless @metadata_received
      begin
        batch_result = @call.run_batch(ops)
        # Store metadata if this is the first time receiving it
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

    # Handles the writing loop for outgoing messages
    # @param requests [Enumerable] The messages to send
    # @param is_client [Boolean] Flag indicating if this is client-side
    # @param set_output_stream_done [Proc] Callback when output stream completes
    def write_loop(requests, is_client: true, set_output_stream_done: nil)
      GRPC::Core.fork_unsafe_begin
      GRPC.logger.debug('bidi-write-loop: starting')
      count = 0
      requests.each do |req|
        GRPC.logger.debug("bidi-write-loop: #{count}")
        count += 1
        payload = @marshal.call(req)  # Marshal the outgoing message

        begin
          # Send initial metadata if request view is available
          @req_view.send_initial_metadata unless @req_view.nil?
          @call.run_batch(SEND_MESSAGE => payload)  # Send the message
        rescue GRPC::Core::CallError => e
          GRPC.logger.warn('bidi-write-loop: ended with error')
          GRPC.logger.warn(e)
          break
        end
      end
      GRPC.logger.debug("bidi-write-loop: #{count} writes done")
      
      # Client-specific completion handling
      if is_client
        GRPC.logger.debug("bidi-write-loop: client sent #{count}, waiting")
        begin
          @call.run_batch(SEND_CLOSE_FROM_CLIENT => nil)  # Signal completion
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
      # Handle errors differently for client vs server
      if is_client
        @call.cancel_with_status(GRPC::Core::StatusCodes::UNKNOWN,
                                 "GRPC bidi call error: #{e.inspect}")
      else
        raise e
      end
    ensure
      GRPC::Core.fork_unsafe_end
      set_output_stream_done.call if is_client  # Notify completion
    end

    # Handles the reading loop for incoming messages
    # @param set_input_stream_done [Proc] Callback when input stream completes
    # @param is_client [Boolean] Flag indicating if this is client-side
    # @yield [Object] Process each received message
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

          # Check for end of stream
          if batch_result.nil? || batch_result.message.nil?
            GRPC.logger.debug("bidi-read-loop: null batch #{batch_result}")

            # Client-specific status handling
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

          # Process the received message
          res = @unmarshal.call(batch_result.message)
          yield res
        end
      rescue StandardError => e
        GRPC.logger.warn('bidi: read-loop failed')
        GRPC.logger.warn(e)
        raise e
      ensure
        set_input_stream_done.call  # Notify completion
      end
      GRPC.logger.debug('bidi-read-loop: finished')

      @enq_th.join if is_client  # Wait for write thread to complete (client only)
    end
  end
end
```
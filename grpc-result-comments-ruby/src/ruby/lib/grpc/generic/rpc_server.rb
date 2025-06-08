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

require_relative '../grpc'
require_relative 'active_call'
require_relative 'service'
require 'thread'

module GRPC
  # A thread pool implementation for handling concurrent gRPC requests
  class Pool
    # Default time to keep idle workers alive before stopping them
    DEFAULT_KEEP_ALIVE = 1

    # Initializes a new thread pool
    # @param size [Integer] number of worker threads in the pool
    # @param keep_alive [Integer] time in seconds to keep idle workers alive
    def initialize(size, keep_alive: DEFAULT_KEEP_ALIVE)
      fail 'pool size must be positive' unless size > 0
      @jobs = Queue.new          # Queue for holding pending jobs
      @size = size               # Maximum number of workers
      @stopped = false           # Flag indicating if pool is stopped
      @stop_mutex = Mutex.new    # Mutex for thread-safe state changes
      @stop_cond = ConditionVariable.new  # Condition variable for stop signaling
      @workers = []              # Array to keep track of worker threads
      @keep_alive = keep_alive   # Time to keep idle workers before stopping
      @ready_workers = Queue.new # Queue of workers ready for new tasks
    end

    # Returns the number of jobs waiting to be processed
    def jobs_waiting
      @jobs.size
    end

    # Checks if there are workers ready to accept new work
    def ready_for_work?
      !@ready_workers.empty?
    end

    # Schedules a new job to be executed by the pool
    # @param args [Array] arguments to pass to the block
    # @param blk [Proc] the job to be executed
    def schedule(*args, &blk)
      return if blk.nil?
      @stop_mutex.synchronize do
        if @stopped
          GRPC.logger.warn('did not schedule job, already stopped')
          return
        end
        GRPC.logger.info('schedule another job')
        fail 'No worker threads available' if @ready_workers.empty?
        worker_queue = @ready_workers.pop

        fail 'worker already has a task waiting' unless worker_queue.empty?
        worker_queue << [blk, args]
      end
    end

    # Starts the thread pool by creating worker threads
    def start
      @stop_mutex.synchronize do
        fail 'already stopped' if @stopped
      end
      until @workers.size == @size.to_i
        new_worker_queue = Queue.new
        @ready_workers << new_worker_queue
        next_thread = Thread.new(new_worker_queue) do |jobs|
          catch(:exit) do
            loop_execute_jobs(jobs)
          end
          remove_current_thread
        end
        @workers << next_thread
      end
    end

    # Stops the thread pool gracefully
    def stop
      GRPC.logger.info('stopping, will wait for all the workers to exit')
      @stop_mutex.synchronize do
        @stopped = true
        loop do
          break unless ready_for_work?
          worker_queue = @ready_workers.pop
          worker_queue << [proc { throw :exit }, []]
        end
        @stop_cond.wait(@stop_mutex, @keep_alive) if @workers.size > 0
      end
      forcibly_stop_workers
      GRPC.logger.info('stopped, all workers are shutdown')
    end

    protected

    # Forcefully stops any remaining worker threads
    def forcibly_stop_workers
      return unless @workers.size > 0
      GRPC.logger.info("forcibly terminating #{@workers.size} worker(s)")
      @workers.each do |t|
        next unless t.alive?
        begin
          t.exit
        rescue StandardError => e
          GRPC.logger.warn('error while terminating a worker')
          GRPC.logger.warn(e)
        end
      end
    end

    # Removes the current thread from the workers list
    def remove_current_thread
      @stop_mutex.synchronize do
        @workers.delete(Thread.current)
        @stop_cond.signal if @workers.size.zero?
      end
    end

    # Main worker loop that processes jobs from the queue
    # @param worker_queue [Queue] the queue from which to get jobs
    def loop_execute_jobs(worker_queue)
      loop do
        begin
          blk, args = worker_queue.pop
          blk.call(*args)
        rescue StandardError, GRPC::Core::CallError => e
          GRPC.logger.warn('Error in worker thread')
          GRPC.logger.warn(e)
        end

        fail('received a task while busy') unless worker_queue.empty?
        @stop_mutex.synchronize do
          return if @stopped
          @ready_workers << worker_queue
        end
      end
    end
  end

  # Implementation of a gRPC server
  class RpcServer
    include Core::CallOps
    include Core::TimeConsts
    extend ::Forwardable

    # Delegate add_http2_port to the underlying server
    def_delegators :@server, :add_http2_port

    # Default thread pool size
    DEFAULT_POOL_SIZE = 30

    # Default maximum waiting requests
    DEFAULT_MAX_WAITING_REQUESTS = 20

    # Default polling period for server operations
    DEFAULT_POLL_PERIOD = 1

    # Period for checking signals
    SIGNAL_CHECK_PERIOD = 0.25

    # Validates and sets up a connection metadata proc
    # @param a_proc [Proc] the proc to validate and set
    # @return [Proc, nil] the validated proc or nil
    def self.setup_connect_md_proc(a_proc)
      return nil if a_proc.nil?
      fail(TypeError, '!Proc') unless a_proc.is_a? Proc
      a_proc
    end

    # Initializes a new RPC server
    # @param pool_size [Integer] size of the thread pool
    # @param max_waiting_requests [Integer] max waiting requests
    # @param poll_period [Integer] server polling period
    # @param pool_keep_alive [Integer] worker keep-alive time
    # @param connect_md_proc [Proc] proc for connection metadata
    # @param server_args [Hash] additional server arguments
    # @param interceptors [Array] array of interceptors
    def initialize(pool_size: DEFAULT_POOL_SIZE,
                   max_waiting_requests: DEFAULT_MAX_WAITING_REQUESTS,
                   poll_period: DEFAULT_POLL_PERIOD,
                   pool_keep_alive: Pool::DEFAULT_KEEP_ALIVE,
                   connect_md_proc: nil,
                   server_args: {},
                   interceptors: [])
      @connect_md_proc = RpcServer.setup_connect_md_proc(connect_md_proc)
      @max_waiting_requests = max_waiting_requests
      @poll_period = poll_period
      @pool_size = pool_size
      @pool = Pool.new(@pool_size, keep_alive: pool_keep_alive)
      @run_cond = ConditionVariable.new
      @run_mutex = Mutex.new

      @running_state = :not_started
      @server = Core::Server.new(server_args)
      @interceptors = InterceptorRegistry.new(interceptors)
    end

    # Stops the server gracefully
    def stop
      if @stop_server.nil? == false && @stop_server == false
        @stop_server = true
        @stop_server_cv.broadcast
        return
      end
      @run_mutex.synchronize do
        fail 'Cannot stop before starting' if @running_state == :not_started
        return if @running_state != :running
        transition_running_state(:stopping)
        deadline = from_relative_time(@poll_period)
        @server.shutdown_and_notify(deadline)
      end
      @pool.stop
    end

    # Returns the current running state of the server
    def running_state
      @run_mutex.synchronize do
        return @running_state
      end
    end

    # Transitions the server to a new state
    # @param target_state [Symbol] the state to transition to
    def transition_running_state(target_state)
      state_transitions = {
        not_started: :running,
        running: :stopping,
        stopping: :stopped
      }
      if state_transitions[@running_state] == target_state
        @running_state = target_state
      else
        fail "Bad server state transition: #{@running_state}->#{target_state}"
      end
    end

    # Checks if the server is running
    def running?
      running_state == :running
    end

    # Checks if the server is stopped
    def stopped?
      running_state == :stopped
    end

    # Waits until the server is running or timeout occurs
    # @param timeout [Integer] maximum time to wait
    def wait_till_running(timeout = nil)
      @run_mutex.synchronize do
        @run_cond.wait(@run_mutex, timeout) if @running_state == :not_started
        return @running_state == :running
      end
    end

    # Registers a service with the server
    # @param service [Object] the service to handle
    def handle(service)
      @run_mutex.synchronize do
        unless @running_state == :not_started
          fail 'cannot add services if the server has been started'
        end
        cls = service.is_a?(Class) ? service : service.class
        assert_valid_service_class(cls)
        add_rpc_descs_for(service)
      end
    end

    # Starts the server and begins processing requests
    def run
      @run_mutex.synchronize do
        fail 'cannot run without registering services' if rpc_descs.size.zero?
        @pool.start
        @server.start
        transition_running_state(:running)
        @run_cond.broadcast
      end
      loop_handle_server_calls
    end

    alias_method :run_till_terminated, :run

    # Runs the server until terminated by a signal or manually stopped
    # @param signals [Array] signals to listen for termination
    # @param wait_interval [Integer] interval to check for stop condition
    def run_till_terminated_or_interrupted(signals, wait_interval = 60)
      @stop_server = false
      @stop_server_mu = Mutex.new
      @stop_server_cv = ConditionVariable.new

      @stop_server_thread = Thread.new do
        loop do
          break if @stop_server
          @stop_server_mu.synchronize do
            @stop_server_cv.wait(@stop_server_mu, wait_interval)
          end
        end

        stop
      end

      valid_signals = Signal.list

      signals.each do |sig|
        # Normalize signal name
        target_sig = if sig.class == String
                       sig.upcase.start_with?('SIG') ? sig.upcase[3..-1] : sig.upcase
                     else
                       sig
                     end

        if valid_signals.value?(target_sig) || valid_signals.key?(target_sig)
          Signal.trap(target_sig) do
            @stop_server = true
            @stop_server_cv.broadcast
          end
        else
          fail "#{target_sig} not a valid signal"
        end
      end

      run

      @stop_server_thread.join
    end

    # Checks if a worker is available to handle an RPC
    # @param an_rpc [Object] the RPC to check
    # @return [Object, nil] the RPC if available, nil otherwise
    def available?(an_rpc)
      return an_rpc if @pool.ready_for_work?
      GRPC.logger.warn('no free worker threads currently')
      noop = proc { |x| x }

      c = ActiveCall.new(an_rpc.call, noop, noop, an_rpc.deadline,
                         metadata_received: true, started: false)
      c.send_status(GRPC::Core::StatusCodes::RESOURCE_EXHAUSTED,
                    'No free threads in thread pool')
      nil
    end

    # Checks if an RPC method is implemented
    # @param an_rpc [Object] the RPC to check
    # @return [Object, nil] the RPC if implemented, nil otherwise
    def implemented?(an_rpc)
      mth = an_rpc.method.to_sym
      return an_rpc if rpc_descs.key?(mth)
      GRPC.logger.warn("UNIMPLEMENTED: #{an_rpc}")
      noop = proc { |x| x }

      c = ActiveCall.new(an_rpc.call, noop, noop, an_rpc.deadline,
                         metadata_received: true, started: false)
      c.send_status(GRPC::Core::StatusCodes::UNIMPLEMENTED, '')
      nil
    end

    # Main server loop that handles incoming RPC calls
    def loop_handle_server_calls
      fail 'not started' if running_state == :not_started
      while running_state == :running
        begin
          an_rpc = @server.request_call
          break if (!an_rpc.nil?) && an_rpc.call.nil?
          active_call = new_active_server_call(an_rpc)
          unless active_call.nil?
            @pool.schedule(active_call) do |ac|
              c, mth = ac
              begin
                rpc_descs[mth].run_server_method(
                  c,
                  rpc_handlers[mth],
                  @interceptors.build_context
                )
              rescue StandardError
                c.send_status(GRPC::Core::StatusCodes::INTERNAL,
                              'Server handler failed')
              end
            end
          end
        rescue Core::CallError, RuntimeError => e
          if running_state == :running
            GRPC.logger.warn("server call failed: #{e}")
          end
          next
        end
      end

      @run_mutex.synchronize do
        transition_running_state(:stopped)
        GRPC.logger.info("stopped: #{self}")
        @server.close
      end
    end

    # Creates a new active server call
    # @param an_rpc [Object] the RPC to create a call for
    # @return [Array, nil] array containing call and method if successful, nil otherwise
    def new_active_server_call(an_rpc)
      return nil if an_rpc.nil? || an_rpc.call.nil?

      an_rpc.call.metadata = an_rpc.metadata
      connect_md = nil
      unless @connect_md_proc.nil?
        connect_md = @connect_md_proc.call(an_rpc.method, an_rpc.metadata)
      end

      return nil unless available?(an_rpc)
      return nil unless implemented?(an_rpc)

      GRPC.logger.info("deadline is #{an_rpc.deadline}; (now=#{Time.now})")
      rpc_desc = rpc_descs[an_rpc.method.to_sym]
      c = ActiveCall.new(an_rpc.call,
                         rpc_desc.marshal_proc,
                         rpc_desc.unmarshal_proc(:input),
                         an_rpc.deadline,
                         metadata_received: true,
                         started: false,
                         metadata_to_send: connect_md)
      c.attach_peer_cert(an_rpc.call.peer_cert)
      mth = an_rpc.method.to_sym
      [c, mth]
    end

    protected

    # Returns the RPC descriptions
    def rpc_descs
      @rpc_descs ||= {}
    end

    # Returns the RPC handlers
    def rpc_handlers
      @rpc_handlers ||= {}
    end

    # Validates that a service class includes GenericService
    # @param cls [Class] the class to validate
    def assert_valid_service_class(cls)
      unless cls.include?(GenericService)
        fail "#{cls} must 'include GenericService'"
      end
      fail "#{cls} should specify some rpc descriptions" if
        cls.rpc_descs.size.zero?
    end

    # Adds RPC descriptions and handlers for a service
    # @param service [Object] the service to add descriptions for
    def add_rpc_descs_for(service)
      cls = service.is_a?(Class) ? service : service.class
      specs, handlers = (@rpc_descs ||= {}), (@rpc_handlers ||= {})
      cls.rpc_descs.each_pair do |name, spec|
        route = "/#{cls.service_name}/#{name}".to_sym
        fail "already registered: rpc #{route} from #{spec}" if specs.key? route
        specs[route] = spec
        rpc_name = GenericService.underscore(name.to_s).to_sym
        if service.is_a?(Class)
          handlers[route] = cls.new.method(rpc_name)
        else
          handlers[route] = service.method(rpc_name)
        end
        GRPC.logger.info("handling #{route} with #{handlers[route]}")
      end
    end
  end
end
```
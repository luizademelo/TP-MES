Here's the commented version of the code:

```ruby
#!/usr/bin/env ruby

# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Set up load paths for required libraries
this_dir = File.expand_path(File.dirname(__FILE__))
lib_dir = File.join(File.dirname(File.dirname(this_dir)), 'lib')
pb_dir = File.dirname(this_dir)
$LOAD_PATH.unshift(lib_dir) unless $LOAD_PATH.include?(lib_dir)
$LOAD_PATH.unshift(pb_dir) unless $LOAD_PATH.include?(pb_dir)

# Require necessary libraries
require 'optparse'
require 'logger'

# Require gRPC and Protobuf libraries
require_relative '../../lib/grpc'
require 'google/protobuf'

# Require generated protobuf files
require_relative '../src/proto/grpc/testing/empty_pb'
require_relative '../src/proto/grpc/testing/messages_pb'
require_relative '../src/proto/grpc/testing/test_services_pb'

# Configuration class for RPC settings
class RpcConfig
  attr_reader :rpcs_to_send, :metadata_to_send, :timeout_sec
  def init(rpcs_to_send, metadata_to_send, timeout_sec = 0)
    @rpcs_to_send = rpcs_to_send
    @metadata_to_send = metadata_to_send
    @timeout_sec = timeout_sec
  end
end

# Mapping between RPC method names and symbols
$RPC_MAP = {
  'UnaryCall' => :UNARY_CALL,
  'EmptyCall' => :EMPTY_CALL,
}

# Global variables for tracking RPC stats and synchronization
$watchers = Array.new          # List of active watchers for RPC stats
$watchers_mutex = Mutex.new    # Mutex for thread-safe access to watchers
$watchers_cv = ConditionVariable.new  # Condition variable for watchers
$shutdown = false              # Flag to indicate when to shutdown

# Default RPC configuration
$rpc_config = RpcConfig.new
$rpc_config.init([:UNARY_CALL], {})

# Thread-safe storage for RPC results and statistics
$thread_results = Array.new
$thread_results_mu = Mutex.new
$accumulated_stats_mu = Mutex.new
$num_rpcs_started_by_method = {}
$num_rpcs_succeeded_by_method = {}
$num_rpcs_failed_by_method = {}
$accumulated_method_stats = {}

# Logger module for gRPC
module RubyLogger
  def logger
    LOGGER
  end

  LOGGER = Logger.new(STDOUT)
  LOGGER.level = Logger::INFO
end

# Extend GRPC module with logger functionality
module GRPC
  extend RubyLogger
end

# Creates a gRPC stub for connecting to the server
def create_stub(opts)
  address = "#{opts.server}"
  GRPC.logger.info("... connecting insecurely to #{address}")
  Grpc::Testing::TestService::Stub.new(
    address,
    :this_channel_is_insecure,
  )
end

# Class for tracking statistics per RPC method
class StatsPerMethod
  attr_reader :rpcs_started, :result
  def initialize()
    @rpcs_started = 0
    @result = Hash.new(0)
  end
  
  # Increment the count of started RPCs
  def increment_rpcs_started()
    @rpcs_started += 1
  end
  
  # Add a result status code to the statistics
  def add_result(status_code)
    @result[status_code] += 1
  end
end

# Service implementation for configuring the test client
class ConfigureTarget < Grpc::Testing::XdsUpdateClientConfigureService::Service
  include Grpc::Testing

  # Handles configuration requests from the control plane
  def configure(req, _call)
    # Process metadata from the request
    metadata_to_send = {}
    req.metadata.each do |m|
      rpc = m.type
      if !metadata_to_send.key?(rpc)
        metadata_to_send[rpc] = {}
      end
      metadata_key = m.key
      metadata_value = m.value
      metadata_to_send[rpc][metadata_key] = metadata_value
    end
    
    # Update the global RPC configuration
    new_rpc_config = RpcConfig.new
    new_rpc_config.init(req['types'], metadata_to_send, req['timeout_sec'])
    $rpc_config = new_rpc_config
    ClientConfigureResponse.new()
  end
end

# Service implementation for providing test statistics
class TestTarget < Grpc::Testing::LoadBalancerStatsService::Service
  include Grpc::Testing

  # Returns client statistics for the requested RPCs
  def get_client_stats(req, _call)
    finish_time = Process.clock_gettime(Process::CLOCK_MONOTONIC) +
                  req['timeout_sec']
    watcher = {}
    
    # Synchronize access to watchers and wait for results
    $watchers_mutex.synchronize do
      watcher = {
        "rpcs_by_method" => Hash.new(),
        "rpcs_by_peer" => Hash.new(0),
        "rpcs_needed" => req['num_rpcs'],
        "no_remote_peer" => 0
      }
      $watchers << watcher
      
      # Wait for results or timeout
      seconds_remaining = finish_time -
                          Process.clock_gettime(Process::CLOCK_MONOTONIC)
      while watcher['rpcs_needed'] > 0 && seconds_remaining > 0
        $watchers_cv.wait($watchers_mutex, seconds_remaining)
        seconds_remaining = finish_time -
                            Process.clock_gettime(Process::CLOCK_MONOTONIC)
      end
      $watchers.delete_at($watchers.index(watcher))
    end

    # Format the response
    rpcs_by_method = {}
    watcher['rpcs_by_method'].each do |rpc_name, rpcs_by_peer|
      rpcs_by_method[rpc_name] = LoadBalancerStatsResponse::RpcsByPeer.new(
        rpcs_by_peer: rpcs_by_peer
      )
    end
    LoadBalancerStatsResponse.new(
      rpcs_by_method: rpcs_by_method,
      rpcs_by_peer: watcher['rpcs_by_peer'],
      num_failures: watcher['no_remote_peer'] + watcher['rpcs_needed']
    )
  end

  # Returns accumulated client statistics
  def get_client_accumulated_stats(req, _call)
    $accumulated_stats_mu.synchronize do
      # Format statistics for all methods
      all_stats_per_method = $accumulated_method_stats.map { |rpc, stats_per_method|
        [rpc,
         LoadBalancerAccumulatedStatsResponse::MethodStats.new(
          rpcs_started: stats_per_method.rpcs_started,
          result: stats_per_method.result
         )]
      }.to_h
      LoadBalancerAccumulatedStatsResponse.new(
        num_rpcs_started_by_method: $num_rpcs_started_by_method,
        num_rpcs_succeeded_by_method: $num_rpcs_succeeded_by_method,
        num_rpcs_failed_by_method: $num_rpcs_failed_by_method,
        stats_per_method: all_stats_per_method,
      )
    end
  end
end

# Executes an RPC in a separate thread and records results
def execute_rpc_in_thread(op, rpc)
  Thread.new {
    rpc_stats_key = rpc.to_s
    remote_peer = ""
    begin
      op.execute
      # Extract hostname from metadata if available
      if op.metadata.key?('hostname')
        remote_peer = op.metadata['hostname']
      end
      
      # Record successful RPC
      $accumulated_stats_mu.synchronize do
        $num_rpcs_succeeded_by_method[rpc_stats_key] += 1
        $accumulated_method_stats[rpc_stats_key].add_result(0)
      end
    rescue GRPC::BadStatus => e
      # Record failed RPC
      $accumulated_stats_mu.synchronize do
        $num_rpcs_failed_by_method[rpc_stats_key] += 1
        $accumulated_method_stats[rpc_stats_key].add_result(e.code)
      end
    end
    
    # Store the result
    $thread_results_mu.synchronize do
      $thread_results << [rpc, remote_peer]
    end
  }
end

# Main test loop that executes RPCs according to configuration
def run_test_loop(stub, target_seconds_between_rpcs, fail_on_failed_rpcs)
  include Grpc::Testing
  simple_req = SimpleRequest.new()
  empty_req = Empty.new()
  target_next_start = Process.clock_gettime(Process::CLOCK_MONOTONIC)

  keep_open_threads = Array.new
  while !$shutdown
    # Calculate sleep time to maintain QPS
    now = Process.clock_gettime(Process::CLOCK_MONOTONIC)
    sleep_seconds = target_next_start - now
    if sleep_seconds < 0
      target_next_start = now + target_seconds_between_rpcs
    else
      target_next_start += target_seconds_between_rpcs
      sleep(sleep_seconds)
    end
    
    # Set deadline for RPCs
    deadline_sec = $rpc_config.timeout_sec > 0 ? $rpc_config.timeout_sec : 30
    deadline = GRPC::Core::TimeConsts::from_relative_time(deadline_sec)
    results = {}
    
    # Execute each configured RPC
    $rpc_config.rpcs_to_send.each do |rpc|
      metadata = $rpc_config.metadata_to_send.key?(rpc) ?
                   $rpc_config.metadata_to_send[rpc] : {}
      
      # Record RPC start
      $accumulated_stats_mu.synchronize do
        $num_rpcs_started_by_method[rpc.to_s] += 1
        $accumulated_method_stats[rpc.to_s].increment_rpcs_started()
      end
      
      # Execute the appropriate RPC
      if rpc == :UNARY_CALL
        op = stub.unary_call(simple_req,
                             metadata: metadata,
                             deadline: deadline,
                             return_op: true)
      elsif rpc == :EMPTY_CALL
        op = stub.empty_call(empty_req,
                             metadata: metadata,
                             deadline: deadline,
                             return_op: true)
      else
        raise "Unsupported rpc #{rpc}"
      end
      
      # Execute RPC in separate thread
      keep_open_threads << execute_rpc_in_thread(op, rpc)
    end

    # Process results from completed RPCs
    $thread_results_mu.synchronize do
      $thread_results.each do |r|
        rpc_name, remote_peer = r
        results[rpc_name] = remote_peer
      end
      $thread_results = Array.new
    end
    
    # Update watchers with new results
    $watchers_mutex.synchronize do
      $watchers.each do |watcher|
        watcher['rpcs_needed'] -= 1
        results.each do |rpc_name, remote_peer|
          rpc_name = $RPC_MAP.invert()[rpc_name]
          if remote_peer.strip.empty?
            watcher['no_remote_peer'] += 1
          else
            if not watcher['rpcs_by_method'].key?(rpc_name)
              watcher['rpcs_by_method'][rpc_name] = Hash.new(0)
            end

            watcher['rpcs_by_method'][rpc_name][remote_peer] +=  1
            watcher['rpcs_by_peer'][remote_peer] += 1
          end
        end
      end
      $watchers_cv.broadcast
    end
  end
  keep_open_threads.each { |thd| thd.join }
end

# Structure for command line arguments
Args = Struct.new(:fail_on_failed_rpcs, :num_channels,
                  :rpc, :metadata,
                  :server, :stats_port, :qps)

# Parses command line arguments
def parse_args
  args = Args.new
  args['fail_on_failed_rpcs'] = false
  args['num_channels'] = 1
  args['rpc'] = 'UnaryCall'
  args['metadata'] = ''
  OptionParser.new do |opts|
    opts.on('--fail_on_failed_rpcs BOOL', ['false', 'true']) do |v|
      args['fail_on_failed_rpcs'] = v == 'true'
    end
    opts.on('--num_channels CHANNELS', 'number of channels') do |v|
      args['num_channels'] = v.to_i
    end
    opts.on('--rpc RPCS_TO_SEND', 'list of RPCs to send') do |v|
      args['rpc'] = v
    end
    opts.on('--metadata METADATA_TO_SEND', 'metadata to send per RPC') do |v|
      args['metadata'] = v
    end
    opts.on('--server SERVER_HOST', 'server hostname') do |v|
      GRPC.logger.info("ruby xds: server address is #{v}")
      args['server'] = v
    end
    opts.on('--stats_port STATS_PORT', 'stats port') do |v|
      GRPC.logger.info("ruby xds: stats port is #{v}")
      args['stats_port'] = v
    end
    opts.on('--qps QPS', 'qps') do |v|
      GRPC.logger.info("ruby xds: qps is #{v}")
      args['qps'] = v
    end
  end.parse!
  args
end

# Main entry point for the application
def main
  opts = parse_args

  # Start the stats server
  host = "0.0.0.0:#{opts['stats_port']}"
  s = GRPC::RpcServer.new
  s.add_http2_port(host, :this_port_is_insecure)
  s.handle(TestTarget)
  s.handle(ConfigureTarget)
  server_thread = Thread.new {
    s.run_till_terminated_or_interrupted(['TERM'])
  }

  # Initialize statistics tracking
  $RPC_MAP.values.each do |rpc|
    $num_rpcs_started_by_method[rpc.to_s] = 0
    $num_rpcs_succeeded_by_method[rpc.to_s] = 0
    $num_rpcs_failed_by_method[rpc.to_s] = 0
    $accumulated_method_stats[rpc.to_s] = StatsPerMethod.new
  end

  # Create client stub and calculate RPC interval
  stub = create_stub(opts)
  target_seconds_between_rpcs = (1.0 / opts['qps'].to_f)

  # Parse RPC and metadata configuration
  rpcs_to_send = []
  metadata_to_send = {}
  if opts['metadata']
    metadata_entries = opts['metadata'].split(',')
    metadata_entries.each do |e|
      (rpc_name, metadata_key, metadata_value) = e.split(':')
      rpc_name = $RPC_MAP[rpc_name]

      if !metadata_to_send.key?(rpc_name)
        metadata_to_send[rpc_name] = {}
      end
      metadata_to_send[rpc_name][metadata_key] = metadata_value
    end
  end
  if opts['rpc']
    rpcs_to_send = opts['rpc'].split(',')
  end
  if rpcs_to_send.size > 0
    rpcs_to_send.map! { |rpc| $RPC_MAP[rpc] }
    new_rpc_config = RpcConfig.new
    new_rpc_config.init(rpcs_to_send, metadata_to_send)
    $rpc_config = new_rpc_config
  end
  
  # Start client threads
  client_threads = Array.new
  opts['num_channels'].times {
    client_threads << Thread.new {
      run_test_loop(stub, target_seconds_between_rpcs,
                    opts['fail_on_failed_rpcs'])
    }
  }

  # Wait for shutdown
  server_thread.join
  $shutdown = true
  client_threads.each { |thd| thd.join }
end

if __FILE__ == $0
  main
end
```

The comments I've added explain:
1. The overall purpose of each class and major function
2. The flow of data through the system
3. Thread synchronization points and why they're needed
4. The statistical tracking mechanisms
5. The RPC execution logic
6. Configuration handling
7. Command line argument parsing

The comments are designed to help future developers understand:
- What the code does at a high level
- How different components interact
- Where thread safety is important
- How statistics are collected and reported
- The configuration options available
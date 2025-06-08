Here's the commented version of the code:

```c++
#!/usr/bin/env ruby

# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Required libraries
require 'optparse'
require 'thread'
require_relative '../pb/test/client'
require_relative './metrics_server'
require_relative '../lib/grpc'

# Class to measure and report Queries Per Second (QPS) metric
class QpsGauge < Gauge
  @query_count    # Total number of queries processed
  @query_mutex    # Mutex for thread-safe access to query_count
  @start_time     # Timestamp when measurement started

  # Initialize QPS gauge with zero count and current start time
  def initialize
    @query_count = 0
    @query_mutex = Mutex.new
    @start_time = Time.now
  end

  # Thread-safe increment of query count
  def increment_queries
    @query_mutex.synchronize { @query_count += 1}
  end

  # Returns the metric name
  def get_name
    'qps'
  end

  # Returns the metric type
  def get_type
    'long'
  end

  # Calculates and returns current QPS value (queries per second)
  def get_value
    (@query_mutex.synchronize { @query_count / (Time.now - @start_time) }).to_i
  end
end

# Starts a metrics server on specified port
# Returns server instance, service, and server thread
def start_metrics_server(port)
  host = "0.0.0.0:#{port}"
  server = GRPC::RpcServer.new
  server.add_http2_port(host, :this_port_is_insecure)
  service = MetricsServiceImpl.new
  server.handle(service)
  server_thread = Thread.new { server.run_till_terminated }
  [server, service, server_thread]
end

# Structure to hold stress test parameters
StressArgs = Struct.new(:server_addresses, :test_cases, :duration,
                        :channels_per_server, :concurrent_calls, :metrics_port)

# Main stress test execution function
def start(stress_args)
  running = true  # Flag to control test execution
  threads = []    # Array to hold all worker threads
  qps_gauge = QpsGauge.new
  
  # Start metrics server and register QPS gauge
  metrics_server, metrics_service, metrics_thread =
    start_metrics_server(stress_args.metrics_port)
  metrics_service.register_gauge(qps_gauge)
  
  # For each server address, create channels and concurrent calls
  stress_args.server_addresses.each do |address|
    stress_args.channels_per_server.times do
      client_args = Args.new
      client_args.host, client_args.port = address.split(':')
      client_args.secure = false
      client_args.test_case = ''
      stub = create_stub(client_args)
      named_tests = NamedTests.new(stub, client_args)
      
      # Create concurrent call threads
      stress_args.concurrent_calls.times do
        threads << Thread.new do
          while running
            # Execute random test case from available options
            named_tests.method(stress_args.test_cases.sample).call
            qps_gauge.increment_queries
          end
        end
      end
    end
  end
  
  # If duration is specified, run test for that duration then stop
  if stress_args.duration >= 0
    sleep stress_args.duration
    running = false  # Signal threads to stop
    metrics_server.stop
    p "QPS: #{qps_gauge.get_value}"  # Print final QPS
    threads.each { |thd| thd.join; }  # Wait for all threads to finish
  end
  metrics_thread.join  # Wait for metrics server thread
end

# Parses command line arguments for stress test
def parse_stress_args
  # Default values for stress test parameters
  stress_args = StressArgs.new
  stress_args.server_addresses = ['localhost:8080']
  stress_args.test_cases = []
  stress_args.duration = -1
  stress_args.channels_per_server = 1
  stress_args.concurrent_calls = 1
  stress_args.metrics_port = '8081'
  
  # Configure command line option parser
  OptionParser.new do |opts|
    opts.on('--server_addresses [LIST]', Array) do |addrs|
      stress_args.server_addresses = addrs
    end
    opts.on('--test_cases cases', Array) do |cases|
      # Parse test cases with weights (format: "name:weight")
      stress_args.test_cases = (cases.map do |item|
                                  split = item.split(':')
                                  [split[0]] * split[1].to_i
                                end).reduce([], :+)
    end
    opts.on('--test_duration_secs [INT]', OptionParser::DecimalInteger) do |time|
      stress_args.duration = time
    end
    opts.on('--num_channels_per_server [INT]', OptionParser::DecimalInteger) do |channels|
      stress_args.channels_per_server = channels
    end
    opts.on('--num_stubs_per_channel [INT]', OptionParser::DecimalInteger) do |stubs|
      stress_args.concurrent_calls = stubs
    end
    opts.on('--metrics_port [port]') do |port|
      stress_args.metrics_port = port
    end
  end.parse!
  stress_args
end

# Main entry point
def main
  opts = parse_stress_args
  start(opts)
end

# Execute main if run directly
if __FILE__ == $0
  main
end
```

The comments explain:
1. The purpose of each class and method
2. Key variables and their roles
3. The overall flow of the stress test system
4. Thread safety considerations
5. Command line argument parsing
6. Metrics collection and reporting
7. The concurrent test execution architecture

The comments are designed to help future developers understand:
- What the code does at a high level
- How the different components interact
- Important implementation details
- The threading model and synchronization
- The test execution flow
- How to modify or extend the code
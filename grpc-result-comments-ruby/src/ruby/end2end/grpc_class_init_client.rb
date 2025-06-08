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

require_relative './end2end_common'

# Creates multiple threads to repeatedly execute the given test procedure
# Parameters:
#   test_proc - A Proc object containing the test to be executed
def construct_many(test_proc)
  thds = []
  # Create 4 threads
  4.times do
    thds << Thread.new do
      # Each thread executes the test 20 times
      20.times do
        test_proc.call
      end
    end
  end
  # Main thread also executes the test 20 times
  20.times do
    test_proc.call
  end
  # Wait for all threads to complete
  thds.each(&:join)
end

# Runs GC stress test by testing under different GC conditions
# Parameters:
#   test_proc - A Proc object containing the test to be executed
def run_gc_stress_test(test_proc)
  # Test with GC disabled
  GC.disable
  run_default_test(test_proc)

  # Test with GC enabled
  GC.enable
  run_default_test(test_proc)

  # Test after forcing GC
  GC.start
  run_default_test(test_proc)
end

# Runs concurrency stress test by executing test in multiple threads
# Parameters:
#   test_proc - A Proc object containing the test to be executed
def run_concurrency_stress_test(test_proc)
  thds = []
  # Create 100 threads
  100.times do
    thds << Thread.new do
      # Each thread executes the test once
      test_proc.call
    end
  end
  # Main thread also executes the test
  test_proc.call
  # Wait for all threads to complete
  thds.each(&:join)
end

# Runs the default test case (single execution)
# Parameters:
#   test_proc - A Proc object containing the test to be executed
def run_default_test(test_proc)
  test_proc.call
end

# Returns a test procedure based on the gRPC class type
# Parameters:
#   grpc_class - String specifying which gRPC class to test
# Returns:
#   A Proc object that creates and returns an instance of the specified gRPC class
def get_test_proc(grpc_class)
  case grpc_class
  when 'channel'
    return proc do
      # Creates an insecure gRPC channel
      GRPC::Core::Channel.new('phony_host', nil, :this_channel_is_insecure)
    end
  when 'server'
    return proc do
      # Creates a basic gRPC server
      GRPC::Core::Server.new({})
    end
  when 'channel_credentials'
    return proc do
      # Creates default channel credentials
      GRPC::Core::ChannelCredentials.new
    end
  when 'xds_channel_credentials'
    return proc do
      # Creates XDS channel credentials
      GRPC::Core::XdsChannelCredentials.new(GRPC::Core::ChannelCredentials.new)
    end
  when 'server_credentials'
    return proc do
      # Creates server credentials using test certificate files
      test_root = File.join(File.dirname(__FILE__), '..', 'spec', 'testdata')
      files = ['ca.pem', 'server1.key', 'server1.pem']
      creds = files.map { |f| File.open(File.join(test_root, f)).read }
      GRPC::Core::ServerCredentials.new(
        creds[0],
        [{ private_key: creds[1], cert_chain: creds[2] }],
        true)
    end
  when 'xds_server_credentials'
    return proc do
      # Creates XDS server credentials using test certificate files
      test_root = File.join(File.dirname(__FILE__), '..', 'spec', 'testdata')
      files = ['ca.pem', 'server1.key', 'server1.pem']
      creds = files.map { |f| File.open(File.join(test_root, f)).read }
      GRPC::Core::XdsServerCredentials.new(
        GRPC::Core::ServerCredentials.new(
          creds[0],
          [{ private_key: creds[1], cert_chain: creds[2] }],
          true))
    end
  when 'call_credentials'
    return proc do
      # Creates call credentials with a dummy processor
      GRPC::Core::CallCredentials.new(proc { |noop| noop })
    end
  when 'compression_options'
    return proc do
      # Creates default compression options
      GRPC::Core::CompressionOptions.new
    end
  else
    fail "bad --grpc_class=#{grpc_class} param"
  end
end

# Main entry point for the script
def main
  grpc_class = ''
  stress_test = ''
  # Parse command line options
  OptionParser.new do |opts|
    opts.on('--grpc_class=P', String) do |p|
      grpc_class = p
    end
    opts.on('--stress_test=P') do |p|
      stress_test = p
    end
  end.parse!

  # Get the appropriate test procedure
  test_proc = get_test_proc(grpc_class)

  # Run the appropriate test based on stress_test parameter
  case stress_test
  when 'gc'
    p "run gc stress: #{grpc_class}"
    run_gc_stress_test(test_proc)
  when 'concurrency'
    p "run concurrency stress: #{grpc_class}"
    run_concurrency_stress_test(test_proc)
  when ''
    p "run default: #{grpc_class}"
    run_default_test(test_proc)
  else
    fail "bad --stress_test=#{stress_test} param"
  end
end

main
```

The comments explain:
1. The overall purpose of each method
2. Key parameters and their types
3. What each major block of code does
4. The purpose of different test cases
5. The flow of the main program
6. The different gRPC components being tested

The comments are concise but provide enough information for a developer to understand what the code does without having to analyze each line in detail.
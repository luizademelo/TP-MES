Here's the commented version of the code:

```c++
#!/usr/bin/env ruby

# Copyright 2018 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Set up the load path to include the gRPC library directory
this_dir = File.expand_path(File.dirname(__FILE__))
grpc_lib_dir = File.join(File.dirname(this_dir), 'lib')
$LOAD_PATH.unshift(grpc_lib_dir) unless $LOAD_PATH.include?(grpc_lib_dir)

# Require the sanity check for dynamic library loading
require_relative './sanity_check_dlopen'

# Verifies that BadStatus#to_status returns a Status object with expected values
# @param error [GRPC::BadStatus] The error object to check
# @raise [RuntimeError] If any of the status checks fail
def check_to_status(error)
  my_status = error.to_status
  # Check that to_status doesn't return nil
  fail('GRPC BadStatus#to_status not expected to return nil') if my_status.nil?
  # Verify status code is 2 (UNKNOWN)
  fail('GRPC BadStatus#to_status code expected to be 2') unless my_status.code == 2
  # Verify details are 'unknown'
  fail('GRPC BadStatus#to_status details expected to be unknown') unless my_status.details == 'unknown'
  # Verify metadata is empty
  fail('GRPC BadStatus#to_status metadata expected to be empty hash') unless my_status.metadata == {}
  # Ensure GRPC library isn't fully loaded yet
  fail('GRPC library loaded after BadStatus#to_status') if GRPC::Core.const_defined?(:Channel)
end

# Verifies that BadStatus#to_rpc_status returns nil (expected behavior)
# @param error [GRPC::BadStatus] The error object to check
# @raise [RuntimeError] If to_rpc_status doesn't return nil or library is loaded
def check_to_rpc_status(error)
  my_rpc_status = error.to_rpc_status
  # Check that to_rpc_status returns nil
  fail('GRPC BadStatus#to_rpc_status expected to return nil') unless my_rpc_status.nil?
  # Ensure GRPC library isn't fully loaded yet
  fail('GRPC library loaded after BadStatus#to_rpc_status') if GRPC::Core.const_defined?(:Channel)
end

# Main test function that verifies gRPC library loading behavior
def main
  # Verify GRPC isn't loaded at start
  fail('GRPC constant loaded before expected') if Object.const_defined?(:GRPC)
  
  # Load just the errors module
  require 'grpc/errors'
  
  # Verify GRPC is now loaded
  fail('GRPC constant not loaded when expected') unless Object.const_defined?(:GRPC)
  # Verify BadStatus is available
  fail('GRPC BadStatus not loaded after required') unless GRPC.const_defined?(:BadStatus)
  # Verify Core module is available
  fail('GRPC Core not loaded after required') unless GRPC.const_defined?(:Core)
  # Verify StatusCodes is available
  fail('GRPC StatusCodes not loaded after required') unless GRPC::Core.const_defined?(:StatusCodes)
  # Verify full library isn't loaded yet
  fail('GRPC library loaded before required') if GRPC::Core.const_defined?(:Channel)
  
  # Create test error and run checks
  error = GRPC::BadStatus.new 2, 'unknown'
  check_to_status(error)
  check_to_rpc_status(error)
  
  # Now load the full library
  require 'grpc'
  # Verify full library is now loaded
  fail('GRPC library not loaded after required') unless GRPC::Core.const_defined?(:Channel)
end

# Execute the main test function
main
```

The comments explain:
1. The overall purpose of each method
2. What each verification step is checking for
3. The expected behavior at each stage of library loading
4. Parameters and possible exceptions
5. The flow of the test execution

The comments maintain the original functionality while making the code's intentions and verification steps much clearer to future maintainers.
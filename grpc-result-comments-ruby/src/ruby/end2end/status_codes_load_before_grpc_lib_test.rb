Here's the commented version of the code:

```c++
#!/usr/bin/env ruby

# Copyright 2018 gRPC authors.
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

# Expand the path to the current directory
this_dir = File.expand_path(File.dirname(__FILE__))
# Construct the path to the grpc lib directory (parent of current directory)
grpc_lib_dir = File.join(File.dirname(this_dir), 'lib')
# Add the grpc lib directory to the load path if not already present
$LOAD_PATH.unshift(grpc_lib_dir) unless $LOAD_PATH.include?(grpc_lib_dir)

# Require the sanity check dlopen script from the current directory
require_relative './sanity_check_dlopen'

def main
  # Verify that GRPC constant is not loaded before we expect it
  fail('GRPC constant loaded before expected') if Object.const_defined?(:GRPC)
  
  # Require the status_codes module from grpc core
  require 'grpc/core/status_codes'
  
  # Verify that GRPC constant is now loaded
  fail('GRPC constant not loaded when expected') unless Object.const_defined?(:GRPC)
  
  # Verify that GRPC::Core is defined
  fail('GRPC Core not loaded after required') unless GRPC.const_defined?(:Core)
  
  # Verify that GRPC::Core::StatusCodes is defined
  fail('GRPC StatusCodes not loaded after required') unless GRPC::Core.const_defined?(:StatusCodes)
  
  # Verify that GRPC::Core::Channel is not yet loaded
  fail('GRPC library loaded before required') if GRPC::Core.const_defined?(:Channel)
  
  # Require the main grpc library
  require 'grpc'
  
  # Verify that GRPC::Core::Channel is now loaded
  fail('GRPC library not loaded after required') unless GRPC::Core.const_defined?(:Channel)
end

# Execute the main function
main
```

The comments explain:
1. The license header and copyright notice
2. The path manipulation to ensure the grpc lib directory is in the load path
3. Each step of the verification process in the main function:
   - Checking that GRPC constants load at the expected times
   - Verifying the loading sequence of different GRPC components
   - The purpose of each require statement
4. The final execution of the main function

The code appears to be a sanity check script that verifies the proper loading sequence of the GRPC library components in Ruby.
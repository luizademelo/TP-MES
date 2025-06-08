Here's the commented version of the code:

```c++
# Copyright 2017 gRPC authors.
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

module GRPC
  # Registry for managing gRPC interceptors
  class InterceptorRegistry
    # Custom error class for invalid interceptor registration attempts
    class DescendantError < StandardError; end

    # Initializes the interceptor registry with optional initial interceptors
    # @param interceptors [Array] array of interceptors to initialize with
    # @raise [DescendantError] if any interceptor doesn't descend from GRPC::Interceptor
    def initialize(interceptors = [])
      @interceptors = []  # Stores registered interceptors
      
      # Validate and add each interceptor
      interceptors.each do |i|
        base = GRPC::Interceptor
        # Check if the interceptor class inherits from GRPC::Interceptor
        unless i.class.ancestors.include?(base)
          fail DescendantError, "Interceptors must descend from #{base}"
        end
        @interceptors << i  # Add valid interceptor to registry
      end
    end

    # Builds a new interception context with the registered interceptors
    # @return [InterceptionContext] a new context containing all registered interceptors
    def build_context
      InterceptionContext.new(@interceptors)
    end
  end
end
```

Key improvements made:
1. Added module and class-level documentation explaining their purposes
2. Added detailed method documentation with @param and @return tags
3. Added @raise documentation for potential exceptions
4. Added inline comments explaining the validation logic
5. Fixed the license comment formatting (added missing # for some lines)
6. Added comments for instance variable purpose
7. Made the error class documentation more descriptive

The comments now provide clear guidance about:
- The overall purpose of the InterceptorRegistry
- How to use the initialize method
- The validation being performed
- What the build_context method returns
- The error conditions that can occur
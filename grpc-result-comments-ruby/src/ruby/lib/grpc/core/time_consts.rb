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

module GRPC
  module Core

    # Module containing time-related constants and conversion utilities
    module TimeConsts

      # Converts a relative time representation into an absolute time or time constant
      # 
      # @param timeish [TimeSpec, Numeric, nil] The time representation to convert. Can be:
      #   - A TimeSpec object (returned as-is)
      #   - nil (converted to ZERO)
      #   - A Numeric value representing seconds (converted to absolute time)
      #   - A negative number (converted to INFINITE_FUTURE)
      #   - Zero (converted to ZERO)
      #
      # @return [TimeSpec, Time] Returns either:
      #   - The input TimeSpec unchanged
      #   - TimeConsts::ZERO for nil or zero input
      #   - TimeConsts::INFINITE_FUTURE for negative input
      #   - A Time object representing now + timeish for positive numeric input
      #
      # @raise [TypeError] if the input is not nil, Numeric, or TimeSpec
      def from_relative_time(timeish)
        if timeish.is_a? TimeSpec
          timeish
        elsif timeish.nil?
          TimeConsts::ZERO
        elsif !timeish.is_a? Numeric
          fail(TypeError,
               "Cannot make an absolute deadline from #{timeish.inspect}")
        elsif timeish < 0
          TimeConsts::INFINITE_FUTURE
        elsif timeish.zero?
          TimeConsts::ZERO
        else
          Time.now + timeish
        end
      end

      # Makes the method available as both instance and module method
      module_function :from_relative_time
    end
  end
end
```

Key improvements in the comments:
1. Added module-level documentation explaining the purpose of TimeConsts
2. Added detailed method documentation for from_relative_time including:
   - Parameter description and possible types
   - Return value possibilities
   - Exception that can be raised
   - Behavior for each input case
3. Used consistent documentation style with @param and @return tags
4. Added explanation for the module_function call

The comments now provide comprehensive documentation that will help future developers understand:
- What the code does
- How to use it
- What to expect from different inputs
- Where exceptions might occur
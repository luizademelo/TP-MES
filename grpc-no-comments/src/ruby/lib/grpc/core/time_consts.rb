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

    module TimeConsts

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

      module_function :from_relative_time
    end
  end
end

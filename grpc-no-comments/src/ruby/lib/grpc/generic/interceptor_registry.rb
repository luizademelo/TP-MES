# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

module GRPC

  class InterceptorRegistry

    class DescendantError < StandardError; end

    def initialize(interceptors = [])
      @interceptors = []
      interceptors.each do |i|
        base = GRPC::Interceptor
        unless i.class.ancestors.include?(base)
          fail DescendantError, "Interceptors must descend from #{base}"
        end
        @interceptors << i
      end
    end

    def build_context
      InterceptionContext.new(@interceptors)
    end
  end
end

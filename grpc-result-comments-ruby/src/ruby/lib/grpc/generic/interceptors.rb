Here's the commented version of the code:

```ruby
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
require_relative 'interceptor_registry'

module GRPC
  # Base interceptor class that provides common functionality for interceptors
  class Interceptor
    # Initializes the interceptor with optional configuration
    # @param options [Hash] Configuration options for the interceptor
    def initialize(options = {})
      @options = options || {}
    end
  end

  # Client-side interceptor that can intercept various types of gRPC calls
  class ClientInterceptor < Interceptor
    # Intercepts a unary request/response call
    # @param request [Object] The request object
    # @param call [Object] The call object
    # @param method [String] The method being called
    # @param metadata [Hash] The call metadata
    # @yield The block to execute the actual RPC call
    def request_response(request: nil, call: nil, method: nil, metadata: nil)
      GRPC.logger.debug "Intercepting request response method #{method}" \
        " for request #{request} with call #{call} and metadata: #{metadata}"
      yield
    end

    # Intercepts a client streaming call
    # @param requests [Object] The streaming requests
    # @param call [Object] The call object
    # @param method [String] The method being called
    # @param metadata [Hash] The call metadata
    # @yield The block to execute the actual RPC call
    def client_streamer(requests: nil, call: nil, method: nil, metadata: nil)
      GRPC.logger.debug "Intercepting client streamer method #{method}" \
       " for requests #{requests} with call #{call} and metadata: #{metadata}"
      yield
    end

    # Intercepts a server streaming call
    # @param request [Object] The request object
    # @param call [Object] The call object
    # @param method [String] The method being called
    # @param metadata [Hash] The call metadata
    # @yield The block to execute the actual RPC call
    def server_streamer(request: nil, call: nil, method: nil, metadata: nil)
      GRPC.logger.debug "Intercepting server streamer method #{method}" \
        " for request #{request} with call #{call} and metadata: #{metadata}"
      yield
    end

    # Intercepts a bidirectional streaming call
    # @param requests [Object] The streaming requests
    # @param call [Object] The call object
    # @param method [String] The method being called
    # @param metadata [Hash] The call metadata
    # @yield The block to execute the actual RPC call
    def bidi_streamer(requests: nil, call: nil, method: nil, metadata: nil)
      GRPC.logger.debug "Intercepting bidi streamer method #{method}" \
        " for requests #{requests} with call #{call} and metadata: #{metadata}"
      yield
    end
  end

  # Server-side interceptor that can intercept various types of gRPC calls
  class ServerInterceptor < Interceptor
    # Intercepts a unary request/response call
    # @param request [Object] The request object
    # @param call [Object] The call object
    # @param method [String] The method being called
    # @yield The block to execute the actual RPC call
    def request_response(request: nil, call: nil, method: nil)
      GRPC.logger.debug "Intercepting request response method #{method}" \
        " for request #{request} with call #{call}"
      yield
    end

    # Intercepts a client streaming call
    # @param call [Object] The call object
    # @param method [String] The method being called
    # @yield The block to execute the actual RPC call
    def client_streamer(call: nil, method: nil)
      GRPC.logger.debug "Intercepting client streamer method #{method}" \
        " with call #{call}"
      yield
    end

    # Intercepts a server streaming call
    # @param request [Object] The request object
    # @param call [Object] The call object
    # @param method [String] The method being called
    # @yield The block to execute the actual RPC call
    def server_streamer(request: nil, call: nil, method: nil)
      GRPC.logger.debug "Intercepting server streamer method #{method}" \
        " for request #{request} with call #{call}"
      yield
    end

    # Intercepts a bidirectional streaming call
    # @param requests [Object] The streaming requests
    # @param call [Object] The call object
    # @param method [String] The method being called
    # @yield The block to execute the actual RPC call
    def bidi_streamer(requests: nil, call: nil, method: nil)
      GRPC.logger.debug "Intercepting bidi streamer method #{method}" \
        " for requests #{requests} with call #{call}"
      yield
    end
  end

  # Manages the chain of interceptors and their execution
  class InterceptionContext
    # Initializes the context with a list of interceptors
    # @param interceptors [Array] Array of interceptors to manage
    def initialize(interceptors = [])
      @interceptors = interceptors.dup
    end

    # Executes the interceptors in reverse order (last added is first executed)
    # @param type [Symbol] The type of interception to perform
    # @param args [Hash] Arguments to pass to the interceptor
    # @yield The block to execute after all interceptors have run
    def intercept!(type, args = {})
      return yield if @interceptors.none?

      i = @interceptors.pop
      return yield unless i

      # Recursively call interceptors in the chain
      i.send(type, **args) do
        if @interceptors.any?
          intercept!(type, args) do
            yield
          end
        else
          yield
        end
      end
    end
  end
end
```

Key improvements made:
1. Added class-level comments explaining the purpose of each class
2. Added method-level comments documenting parameters and behavior
3. Added documentation for yield blocks
4. Improved formatting for better readability
5. Added comments explaining the recursive interceptor chain execution
6. Maintained all existing functionality while making the code more understandable

The comments follow Ruby documentation conventions and provide clear explanations of what each component does, making it easier for future developers to understand and maintain the code.
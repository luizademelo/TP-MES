# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
require_relative 'interceptor_registry'

module GRPC

  class Interceptor

    def initialize(options = {})
      @options = options || {}
    end
  end

  class ClientInterceptor < Interceptor

    def request_response(request: nil, call: nil, method: nil, metadata: nil)
      GRPC.logger.debug "Intercepting request response method #{method}" \
        " for request #{request} with call #{call} and metadata: #{metadata}"
      yield
    end

    def client_streamer(requests: nil, call: nil, method: nil, metadata: nil)
      GRPC.logger.debug "Intercepting client streamer method #{method}" \
       " for requests #{requests} with call #{call} and metadata: #{metadata}"
      yield
    end

    def server_streamer(request: nil, call: nil, method: nil, metadata: nil)
      GRPC.logger.debug "Intercepting server streamer method #{method}" \
        " for request #{request} with call #{call} and metadata: #{metadata}"
      yield
    end

    def bidi_streamer(requests: nil, call: nil, method: nil, metadata: nil)
      GRPC.logger.debug "Intercepting bidi streamer method #{method}" \
        " for requests #{requests} with call #{call} and metadata: #{metadata}"
      yield
    end
  end

  class ServerInterceptor < Interceptor

    def request_response(request: nil, call: nil, method: nil)
      GRPC.logger.debug "Intercepting request response method #{method}" \
        " for request #{request} with call #{call}"
      yield
    end

    def client_streamer(call: nil, method: nil)
      GRPC.logger.debug "Intercepting client streamer method #{method}" \
        " with call #{call}"
      yield
    end

    def server_streamer(request: nil, call: nil, method: nil)
      GRPC.logger.debug "Intercepting server streamer method #{method}" \
        " for request #{request} with call #{call}"
      yield
    end

    def bidi_streamer(requests: nil, call: nil, method: nil)
      GRPC.logger.debug "Intercepting bidi streamer method #{method}" \
        " for requests #{requests} with call #{call}"
      yield
    end
  end

  class InterceptionContext

    def initialize(interceptors = [])
      @interceptors = interceptors.dup
    end

    def intercept!(type, args = {})
      return yield if @interceptors.none?

      i = @interceptors.pop
      return yield unless i

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


# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'grpc'
require 'src/proto/grpc/testing/benchmark_service_pb'

module Grpc
  module Testing
    module BenchmarkService
      class Service

        include ::GRPC::GenericService

        self.marshal_class_method = :encode
        self.unmarshal_class_method = :decode
        self.service_name = 'grpc.testing.BenchmarkService'

        rpc :UnaryCall, ::Grpc::Testing::SimpleRequest, ::Grpc::Testing::SimpleResponse

        rpc :StreamingCall, stream(::Grpc::Testing::SimpleRequest), stream(::Grpc::Testing::SimpleResponse)

        rpc :StreamingFromClient, stream(::Grpc::Testing::SimpleRequest), ::Grpc::Testing::SimpleResponse

        rpc :StreamingFromServer, ::Grpc::Testing::SimpleRequest, stream(::Grpc::Testing::SimpleResponse)

        rpc :StreamingBothWays, stream(::Grpc::Testing::SimpleRequest), stream(::Grpc::Testing::SimpleResponse)

        rpc :GetBeforeSnapshot, ::Grpc::Testing::SimpleRequest, ::Grpc::Testing::MemorySize
      end

      Stub = Service.rpc_stub_class
    end
  end
end

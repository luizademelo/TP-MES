
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'grpc'
require 'src/proto/grpc/testing/worker_service_pb'

module Grpc
  module Testing
    module WorkerService
      class Service

        include ::GRPC::GenericService

        self.marshal_class_method = :encode
        self.unmarshal_class_method = :decode
        self.service_name = 'grpc.testing.WorkerService'

        rpc :RunServer, stream(::Grpc::Testing::ServerArgs), stream(::Grpc::Testing::ServerStatus)

        rpc :RunClient, stream(::Grpc::Testing::ClientArgs), stream(::Grpc::Testing::ClientStatus)

        rpc :CoreCount, ::Grpc::Testing::CoreRequest, ::Grpc::Testing::CoreResponse

        rpc :QuitWorker, ::Grpc::Testing::Void, ::Grpc::Testing::Void
      end

      Stub = Service.rpc_stub_class
    end
  end
end

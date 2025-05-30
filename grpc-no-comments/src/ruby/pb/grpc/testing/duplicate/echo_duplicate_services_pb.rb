
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'grpc'
require 'grpc/testing/duplicate/echo_duplicate_pb'

module Grpc
  module Testing
    module Duplicate
      module EchoTestService
        class Service

          include ::GRPC::GenericService

          self.marshal_class_method = :encode
          self.unmarshal_class_method = :decode
          self.service_name = 'grpc.testing.duplicate.EchoTestService'

          rpc :Echo, ::Grpc::Testing::EchoRequest, ::Grpc::Testing::EchoResponse
          rpc :ResponseStream, ::Grpc::Testing::EchoRequest, stream(::Grpc::Testing::EchoResponse)
        end

        Stub = Service.rpc_stub_class
      end
    end
  end
end

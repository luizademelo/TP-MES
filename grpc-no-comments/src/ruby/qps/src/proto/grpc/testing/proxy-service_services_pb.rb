
# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'grpc'
require 'src/proto/grpc/testing/proxy-service_pb'

module Grpc
  module Testing
    module ProxyClientService
      class Service

        include ::GRPC::GenericService

        self.marshal_class_method = :encode
        self.unmarshal_class_method = :decode
        self.service_name = 'grpc.testing.ProxyClientService'

        rpc :GetConfig, ::Grpc::Testing::Void, ::Grpc::Testing::ClientConfig
        rpc :ReportTime, stream(::Grpc::Testing::ProxyStat), ::Grpc::Testing::Void
        rpc :ReportHist, stream(::Grpc::Testing::HistogramData), ::Grpc::Testing::Void
      end

      Stub = Service.rpc_stub_class
    end
  end
end

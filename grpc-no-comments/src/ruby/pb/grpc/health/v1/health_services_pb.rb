
# Copyright 2015 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'grpc'
require 'grpc/health/v1/health_pb'

module Grpc
  module Health
    module V1
      module Health
        class Service

          include ::GRPC::GenericService

          self.marshal_class_method = :encode
          self.unmarshal_class_method = :decode
          self.service_name = 'grpc.health.v1.Health'

          rpc :Check, ::Grpc::Health::V1::HealthCheckRequest, ::Grpc::Health::V1::HealthCheckResponse

          rpc :Watch, ::Grpc::Health::V1::HealthCheckRequest, stream(::Grpc::Health::V1::HealthCheckResponse)
        end

        Stub = Service.rpc_stub_class
      end
    end
  end
end


# Copyright 2015-2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'grpc'
require 'src/proto/grpc/testing/test_pb'

module Grpc
  module Testing
    module TestService

      class Service

        include ::GRPC::GenericService

        self.marshal_class_method = :encode
        self.unmarshal_class_method = :decode
        self.service_name = 'grpc.testing.TestService'

        rpc :EmptyCall, ::Grpc::Testing::Empty, ::Grpc::Testing::Empty

        rpc :UnaryCall, ::Grpc::Testing::SimpleRequest, ::Grpc::Testing::SimpleResponse

        rpc :CacheableUnaryCall, ::Grpc::Testing::SimpleRequest, ::Grpc::Testing::SimpleResponse

        rpc :StreamingOutputCall, ::Grpc::Testing::StreamingOutputCallRequest, stream(::Grpc::Testing::StreamingOutputCallResponse)

        rpc :StreamingInputCall, stream(::Grpc::Testing::StreamingInputCallRequest), ::Grpc::Testing::StreamingInputCallResponse

        rpc :FullDuplexCall, stream(::Grpc::Testing::StreamingOutputCallRequest), stream(::Grpc::Testing::StreamingOutputCallResponse)

        rpc :HalfDuplexCall, stream(::Grpc::Testing::StreamingOutputCallRequest), stream(::Grpc::Testing::StreamingOutputCallResponse)

        rpc :UnimplementedCall, ::Grpc::Testing::Empty, ::Grpc::Testing::Empty
      end

      Stub = Service.rpc_stub_class
    end
    module UnimplementedService

      class Service

        include ::GRPC::GenericService

        self.marshal_class_method = :encode
        self.unmarshal_class_method = :decode
        self.service_name = 'grpc.testing.UnimplementedService'

        rpc :UnimplementedCall, ::Grpc::Testing::Empty, ::Grpc::Testing::Empty
      end

      Stub = Service.rpc_stub_class
    end
    module ReconnectService

      class Service

        include ::GRPC::GenericService

        self.marshal_class_method = :encode
        self.unmarshal_class_method = :decode
        self.service_name = 'grpc.testing.ReconnectService'

        rpc :Start, ::Grpc::Testing::ReconnectParams, ::Grpc::Testing::Empty
        rpc :Stop, ::Grpc::Testing::Empty, ::Grpc::Testing::ReconnectInfo
      end

      Stub = Service.rpc_stub_class
    end
    module LoadBalancerStatsService

      class Service

        include ::GRPC::GenericService

        self.marshal_class_method = :encode
        self.unmarshal_class_method = :decode
        self.service_name = 'grpc.testing.LoadBalancerStatsService'

        rpc :GetClientStats, ::Grpc::Testing::LoadBalancerStatsRequest, ::Grpc::Testing::LoadBalancerStatsResponse

        rpc :GetClientAccumulatedStats, ::Grpc::Testing::LoadBalancerAccumulatedStatsRequest, ::Grpc::Testing::LoadBalancerAccumulatedStatsResponse
      end

      Stub = Service.rpc_stub_class
    end
    module HookService

      class Service

        include ::GRPC::GenericService

        self.marshal_class_method = :encode
        self.unmarshal_class_method = :decode
        self.service_name = 'grpc.testing.HookService'

        rpc :Hook, ::Grpc::Testing::Empty, ::Grpc::Testing::Empty

        rpc :SetReturnStatus, ::Grpc::Testing::SetReturnStatusRequest, ::Grpc::Testing::Empty

        rpc :ClearReturnStatus, ::Grpc::Testing::Empty, ::Grpc::Testing::Empty
      end

      Stub = Service.rpc_stub_class
    end
    module XdsUpdateHealthService

      class Service

        include ::GRPC::GenericService

        self.marshal_class_method = :encode
        self.unmarshal_class_method = :decode
        self.service_name = 'grpc.testing.XdsUpdateHealthService'

        rpc :SetServing, ::Grpc::Testing::Empty, ::Grpc::Testing::Empty
        rpc :SetNotServing, ::Grpc::Testing::Empty, ::Grpc::Testing::Empty
        rpc :SendHookRequest, ::Grpc::Testing::HookRequest, ::Grpc::Testing::HookResponse
      end

      Stub = Service.rpc_stub_class
    end
    module XdsUpdateClientConfigureService

      class Service

        include ::GRPC::GenericService

        self.marshal_class_method = :encode
        self.unmarshal_class_method = :decode
        self.service_name = 'grpc.testing.XdsUpdateClientConfigureService'

        rpc :Configure, ::Grpc::Testing::ClientConfigureRequest, ::Grpc::Testing::ClientConfigureResponse
      end

      Stub = Service.rpc_stub_class
    end
  end
end

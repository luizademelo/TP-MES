
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'grpc'
require 'route_guide_pb'

module Routeguide
  module RouteGuide

    class Service

      include GRPC::GenericService

      self.marshal_class_method = :encode
      self.unmarshal_class_method = :decode
      self.service_name = 'routeguide.RouteGuide'

      rpc :GetFeature, Point, Feature

      rpc :ListFeatures, Rectangle, stream(Feature)

      rpc :RecordRoute, stream(Point), RouteSummary

      rpc :RouteChat, stream(RouteNote), stream(RouteNote)
    end

    Stub = Service.rpc_stub_class
  end
end

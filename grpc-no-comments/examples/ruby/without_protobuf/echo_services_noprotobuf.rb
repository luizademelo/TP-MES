
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'grpc'

module EchoWithoutProtobuf

  class Service

    include GRPC::GenericService

    self.marshal_class_method = :try_convert
    self.unmarshal_class_method = :try_convert
    self.service_name = 'EchoWithoutProtobuf'

    rpc :Echo, String, String
  end

  Stub = Service.rpc_stub_class
end

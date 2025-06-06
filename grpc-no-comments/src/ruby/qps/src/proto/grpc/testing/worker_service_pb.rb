
require 'google/protobuf'

require 'src/proto/grpc/testing/control_pb'

descriptor_data = "\n+src/proto/grpc/testing/worker_service.proto\x12\x0cgrpc.testing\x1a$src/proto/grpc/testing/control.proto2\x97\x02\n\rWorkerService\x12\x45\n\tRunServer\x12\x18.grpc.testing.ServerArgs\x1a\x1a.grpc.testing.ServerStatus(\x01\x30\x01\x12\x45\n\tRunClient\x12\x18.grpc.testing.ClientArgs\x1a\x1a.grpc.testing.ClientStatus(\x01\x30\x01\x12\x42\n\tCoreCount\x12\x19.grpc.testing.CoreRequest\x1a\x1a.grpc.testing.CoreResponse\x12\x34\n\nQuitWorker\x12\x12.grpc.testing.Void\x1a\x12.grpc.testing.Voidb\x06proto3"

pool = Google::Protobuf::DescriptorPool.generated_pool
pool.add_serialized_file(descriptor_data)

module Grpc
  module Testing
  end
end

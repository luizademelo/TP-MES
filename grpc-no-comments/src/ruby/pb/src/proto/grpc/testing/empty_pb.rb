
require 'google/protobuf'

descriptor_data = "\n\"src/proto/grpc/testing/empty.proto\x12\x0cgrpc.testing\"\x07\n\x05\x45mptyb\x06proto3"

pool = Google::Protobuf::DescriptorPool.generated_pool
pool.add_serialized_file(descriptor_data)

module Grpc
  module Testing
    Empty = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("grpc.testing.Empty").msgclass
  end
end

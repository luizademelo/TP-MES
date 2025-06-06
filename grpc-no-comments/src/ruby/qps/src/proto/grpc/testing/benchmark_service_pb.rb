
require 'google/protobuf'

require 'src/proto/grpc/testing/messages_pb'

descriptor_data = "\n.src/proto/grpc/testing/benchmark_service.proto\x12\x0cgrpc.testing\x1a%src/proto/grpc/testing/messages.proto2\xf2\x03\n\x10\x42\x65nchmarkService\x12\x46\n\tUnaryCall\x12\x1b.grpc.testing.SimpleRequest\x1a\x1c.grpc.testing.SimpleResponse\x12N\n\rStreamingCall\x12\x1b.grpc.testing.SimpleRequest\x1a\x1c.grpc.testing.SimpleResponse(\x01\x30\x01\x12R\n\x13StreamingFromClient\x12\x1b.grpc.testing.SimpleRequest\x1a\x1c.grpc.testing.SimpleResponse(\x01\x12R\n\x13StreamingFromServer\x12\x1b.grpc.testing.SimpleRequest\x1a\x1c.grpc.testing.SimpleResponse0\x01\x12R\n\x11StreamingBothWays\x12\x1b.grpc.testing.SimpleRequest\x1a\x1c.grpc.testing.SimpleResponse(\x01\x30\x01\x12J\n\x11GetBeforeSnapshot\x12\x1b.grpc.testing.SimpleRequest\x1a\x18.grpc.testing.MemorySizeb\x06proto3"

pool = Google::Protobuf::DescriptorPool.generated_pool
pool.add_serialized_file(descriptor_data)

module Grpc
  module Testing
  end
end

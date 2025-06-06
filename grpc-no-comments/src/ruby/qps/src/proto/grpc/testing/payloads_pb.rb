
require 'google/protobuf'

descriptor_data = "\n%src/proto/grpc/testing/payloads.proto\x12\x0cgrpc.testing\"7\n\x10\x42yteBufferParams\x12\x10\n\x08req_size\x18\x01 \x01(\x05\x12\x11\n\tresp_size\x18\x02 \x01(\x05\"8\n\x11SimpleProtoParams\x12\x10\n\x08req_size\x18\x01 \x01(\x05\x12\x11\n\tresp_size\x18\x02 \x01(\x05\"\x14\n\x12\x43omplexProtoParams\"\xca\x01\n\rPayloadConfig\x12\x38\n\x0e\x62ytebuf_params\x18\x01 \x01(\x0b\x32\x1e.grpc.testing.ByteBufferParamsH\x00\x12\x38\n\rsimple_params\x18\x02 \x01(\x0b\x32\x1f.grpc.testing.SimpleProtoParamsH\x00\x12:\n\x0e\x63omplex_params\x18\x03 \x01(\x0b\x32 .grpc.testing.ComplexProtoParamsH\x00\x42\t\n\x07payloadb\x06proto3"

pool = Google::Protobuf::DescriptorPool.generated_pool
pool.add_serialized_file(descriptor_data)

module Grpc
  module Testing
    ByteBufferParams = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("grpc.testing.ByteBufferParams").msgclass
    SimpleProtoParams = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("grpc.testing.SimpleProtoParams").msgclass
    ComplexProtoParams = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("grpc.testing.ComplexProtoParams").msgclass
    PayloadConfig = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("grpc.testing.PayloadConfig").msgclass
  end
end

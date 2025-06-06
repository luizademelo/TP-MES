
require 'google/protobuf'

descriptor_data = "\n\nmath.proto\x12\x04math\",\n\x07\x44ivArgs\x12\x10\n\x08\x64ividend\x18\x01 \x01(\x03\x12\x0f\n\x07\x64ivisor\x18\x02 \x01(\x03\"/\n\x08\x44ivReply\x12\x10\n\x08quotient\x18\x01 \x01(\x03\x12\x11\n\tremainder\x18\x02 \x01(\x03\"\x18\n\x07\x46ibArgs\x12\r\n\x05limit\x18\x01 \x01(\x03\"\x12\n\x03Num\x12\x0b\n\x03num\x18\x01 \x01(\x03\"\x19\n\x08\x46ibReply\x12\r\n\x05\x63ount\x18\x01 \x01(\x03\x32\xa4\x01\n\x04Math\x12&\n\x03\x44iv\x12\r.math.DivArgs\x1a\x0e.math.DivReply\"\x00\x12.\n\x07\x44ivMany\x12\r.math.DivArgs\x1a\x0e.math.DivReply\"\x00(\x01\x30\x01\x12#\n\x03\x46ib\x12\r.math.FibArgs\x1a\t.math.Num\"\x00\x30\x01\x12\x1f\n\x03Sum\x12\t.math.Num\x1a\t.math.Num\"\x00(\x01\x62\x06proto3"

pool = Google::Protobuf::DescriptorPool.generated_pool
pool.add_serialized_file(descriptor_data)

module Math
  DivArgs = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("math.DivArgs").msgclass
  DivReply = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("math.DivReply").msgclass
  FibArgs = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("math.FibArgs").msgclass
  Num = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("math.Num").msgclass
  FibReply = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("math.FibReply").msgclass
end

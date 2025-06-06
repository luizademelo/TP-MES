
require 'google/protobuf'

descriptor_data = "\n\x1agrpc/testing/metrics.proto\x12\x0cgrpc.testing\"l\n\rGaugeResponse\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x14\n\nlong_value\x18\x02 \x01(\x03H\x00\x12\x16\n\x0c\x64ouble_value\x18\x03 \x01(\x01H\x00\x12\x16\n\x0cstring_value\x18\x04 \x01(\tH\x00\x42\x07\n\x05value\"\x1c\n\x0cGaugeRequest\x12\x0c\n\x04name\x18\x01 \x01(\t\"\x0e\n\x0c\x45mptyMessage2\xa0\x01\n\x0eMetricsService\x12I\n\x0cGetAllGauges\x12\x1a.grpc.testing.EmptyMessage\x1a\x1b.grpc.testing.GaugeResponse0\x01\x12\x43\n\x08GetGauge\x12\x1a.grpc.testing.GaugeRequest\x1a\x1b.grpc.testing.GaugeResponseb\x06proto3"

pool = Google::Protobuf::DescriptorPool.generated_pool
pool.add_serialized_file(descriptor_data)

module Grpc
  module Testing
    GaugeResponse = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("grpc.testing.GaugeResponse").msgclass
    GaugeRequest = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("grpc.testing.GaugeRequest").msgclass
    EmptyMessage = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("grpc.testing.EmptyMessage").msgclass
  end
end

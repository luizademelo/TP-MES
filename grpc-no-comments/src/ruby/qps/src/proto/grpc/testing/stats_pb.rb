
require 'google/protobuf'

descriptor_data = "\n\"src/proto/grpc/testing/stats.proto\x12\x0cgrpc.testing\"\x91\x01\n\x0bServerStats\x12\x14\n\x0ctime_elapsed\x18\x01 \x01(\x01\x12\x11\n\ttime_user\x18\x02 \x01(\x01\x12\x13\n\x0btime_system\x18\x03 \x01(\x01\x12\x16\n\x0etotal_cpu_time\x18\x04 \x01(\x04\x12\x15\n\ridle_cpu_time\x18\x05 \x01(\x04\x12\x15\n\rcq_poll_count\x18\x06 \x01(\x04\";\n\x0fHistogramParams\x12\x12\n\nresolution\x18\x01 \x01(\x01\x12\x14\n\x0cmax_possible\x18\x02 \x01(\x01\"w\n\rHistogramData\x12\x0e\n\x06\x62ucket\x18\x01 \x03(\r\x12\x10\n\x08min_seen\x18\x02 \x01(\x01\x12\x10\n\x08max_seen\x18\x03 \x01(\x01\x12\x0b\n\x03sum\x18\x04 \x01(\x01\x12\x16\n\x0esum_of_squares\x18\x05 \x01(\x01\x12\r\n\x05\x63ount\x18\x06 \x01(\x01\"8\n\x12RequestResultCount\x12\x13\n\x0bstatus_code\x18\x01 \x01(\x05\x12\r\n\x05\x63ount\x18\x02 \x01(\x03\"\xcd\x01\n\x0b\x43lientStats\x12.\n\tlatencies\x18\x01 \x01(\x0b\x32\x1b.grpc.testing.HistogramData\x12\x14\n\x0ctime_elapsed\x18\x02 \x01(\x01\x12\x11\n\ttime_user\x18\x03 \x01(\x01\x12\x13\n\x0btime_system\x18\x04 \x01(\x01\x12\x39\n\x0frequest_results\x18\x05 \x03(\x0b\x32 .grpc.testing.RequestResultCount\x12\x15\n\rcq_poll_count\x18\x06 \x01(\x04\x62\x06proto3"

pool = Google::Protobuf::DescriptorPool.generated_pool
pool.add_serialized_file(descriptor_data)

module Grpc
  module Testing
    ServerStats = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("grpc.testing.ServerStats").msgclass
    HistogramParams = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("grpc.testing.HistogramParams").msgclass
    HistogramData = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("grpc.testing.HistogramData").msgclass
    RequestResultCount = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("grpc.testing.RequestResultCount").msgclass
    ClientStats = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("grpc.testing.ClientStats").msgclass
  end
end

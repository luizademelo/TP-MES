
require 'google/protobuf'

require 'src/proto/grpc/testing/control_pb'
require 'src/proto/grpc/testing/stats_pb'

descriptor_data = "\n*src/proto/grpc/testing/proxy-service.proto\x12\x0cgrpc.testing\x1a$src/proto/grpc/testing/control.proto\x1a\"src/proto/grpc/testing/stats.proto\"\x1c\n\tProxyStat\x12\x0f\n\x07latency\x18\x01 \x01(\x01\x32\xcf\x01\n\x12ProxyClientService\x12;\n\tGetConfig\x12\x12.grpc.testing.Void\x1a\x1a.grpc.testing.ClientConfig\x12;\n\nReportTime\x12\x17.grpc.testing.ProxyStat\x1a\x12.grpc.testing.Void(\x01\x12?\n\nReportHist\x12\x1b.grpc.testing.HistogramData\x1a\x12.grpc.testing.Void(\x01\x62\x06proto3"

pool = Google::Protobuf::DescriptorPool.generated_pool
pool.add_serialized_file(descriptor_data)

module Grpc
  module Testing
    ProxyStat = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("grpc.testing.ProxyStat").msgclass
  end
end

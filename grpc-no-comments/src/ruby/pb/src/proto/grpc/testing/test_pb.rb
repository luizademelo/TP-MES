
require 'google/protobuf'

require 'src/proto/grpc/testing/empty_pb'
require 'src/proto/grpc/testing/messages_pb'

descriptor_data = "\n!src/proto/grpc/testing/test.proto\x12\x0cgrpc.testing\x1a\"src/proto/grpc/testing/empty.proto\x1a%src/proto/grpc/testing/messages.proto2\xcb\x05\n\x0bTestService\x12\x35\n\tEmptyCall\x12\x13.grpc.testing.Empty\x1a\x13.grpc.testing.Empty\x12\x46\n\tUnaryCall\x12\x1b.grpc.testing.SimpleRequest\x1a\x1c.grpc.testing.SimpleResponse\x12O\n\x12\x43\x61\x63heableUnaryCall\x12\x1b.grpc.testing.SimpleRequest\x1a\x1c.grpc.testing.SimpleResponse\x12l\n\x13StreamingOutputCall\x12(.grpc.testing.StreamingOutputCallRequest\x1a).grpc.testing.StreamingOutputCallResponse0\x01\x12i\n\x12StreamingInputCall\x12\'.grpc.testing.StreamingInputCallRequest\x1a(.grpc.testing.StreamingInputCallResponse(\x01\x12i\n\x0e\x46ullDuplexCall\x12(.grpc.testing.StreamingOutputCallRequest\x1a).grpc.testing.StreamingOutputCallResponse(\x01\x30\x01\x12i\n\x0eHalfDuplexCall\x12(.grpc.testing.StreamingOutputCallRequest\x1a).grpc.testing.StreamingOutputCallResponse(\x01\x30\x01\x12=\n\x11UnimplementedCall\x12\x13.grpc.testing.Empty\x1a\x13.grpc.testing.Empty2U\n\x14UnimplementedService\x12=\n\x11UnimplementedCall\x12\x13.grpc.testing.Empty\x1a\x13.grpc.testing.Empty2\x89\x01\n\x10ReconnectService\x12;\n\x05Start\x12\x1d.grpc.testing.ReconnectParams\x1a\x13.grpc.testing.Empty\x12\x38\n\x04Stop\x12\x13.grpc.testing.Empty\x1a\x1b.grpc.testing.ReconnectInfo2\x86\x02\n\x18LoadBalancerStatsService\x12\x63\n\x0eGetClientStats\x12&.grpc.testing.LoadBalancerStatsRequest\x1a\'.grpc.testing.LoadBalancerStatsResponse\"\x00\x12\x84\x01\n\x19GetClientAccumulatedStats\x12\x31.grpc.testing.LoadBalancerAccumulatedStatsRequest\x1a\x32.grpc.testing.LoadBalancerAccumulatedStatsResponse\"\x00\x32\xcc\x01\n\x0bHookService\x12\x30\n\x04Hook\x12\x13.grpc.testing.Empty\x1a\x13.grpc.testing.Empty\x12L\n\x0fSetReturnStatus\x12$.grpc.testing.SetReturnStatusRequest\x1a\x13.grpc.testing.Empty\x12=\n\x11\x43learReturnStatus\x12\x13.grpc.testing.Empty\x1a\x13.grpc.testing.Empty2\xd5\x01\n\x16XdsUpdateHealthService\x12\x36\n\nSetServing\x12\x13.grpc.testing.Empty\x1a\x13.grpc.testing.Empty\x12\x39\n\rSetNotServing\x12\x13.grpc.testing.Empty\x1a\x13.grpc.testing.Empty\x12H\n\x0fSendHookRequest\x12\x19.grpc.testing.HookRequest\x1a\x1a.grpc.testing.HookResponse2{\n\x1fXdsUpdateClientConfigureService\x12X\n\tConfigure\x12$.grpc.testing.ClientConfigureRequest\x1a%.grpc.testing.ClientConfigureResponseB\x1d\n\x1bio.grpc.testing.integrationb\x06proto3"

pool = Google::Protobuf::DescriptorPool.generated_pool
pool.add_serialized_file(descriptor_data)

module Grpc
  module Testing
  end
end

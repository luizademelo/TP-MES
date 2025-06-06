
require 'google/protobuf'

descriptor_data = "\n\x14\x63lient_control.proto\x12\x0e\x63lient_control\"#\n\x10\x44oEchoRpcRequest\x12\x0f\n\x07request\x18\x01 \x01(\t\"\x06\n\x04Void\"\x14\n\x04Port\x12\x0c\n\x04port\x18\x01 \x01(\x05\x32\x93\x01\n\x10\x43lientController\x12\x45\n\tDoEchoRpc\x12 .client_control.DoEchoRpcRequest\x1a\x14.client_control.Void\"\x00\x12\x38\n\x08Shutdown\x12\x14.client_control.Void\x1a\x14.client_control.Void\"\x00\x32[\n\x10ParentController\x12G\n\x17SetClientControllerPort\x12\x14.client_control.Port\x1a\x14.client_control.Void\"\x00\x62\x06proto3"

pool = Google::Protobuf::DescriptorPool.generated_pool
pool.add_serialized_file(descriptor_data)

module ClientControl
  DoEchoRpcRequest = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("client_control.DoEchoRpcRequest").msgclass
  Void = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("client_control.Void").msgclass
  Port = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("client_control.Port").msgclass
end

Here's the commented version of the code:

```c++
# Require the Google Protocol Buffers library for Ruby
require 'google/protobuf'

# Binary descriptor data containing the Protocol Buffer definitions
# This is a serialized version of the client_control.proto file containing:
# - Message definitions (DoEchoRpcRequest, Void, Port)
# - Service definitions (ClientController, ParentController)
descriptor_data = "\n\x14\x63lient_control.proto\x12\x0e\x63lient_control\"#\n\x10\x44oEchoRpcRequest\x12\x0f\n\x07request\x18\x01 \x01(\t\"\x06\n\x04Void\"\x14\n\x04Port\x12\x0c\n\x04port\x18\x01 \x01(\x05\x32\x93\x01\n\x10\x43lientController\x12\x45\n\tDoEchoRpc\x12 .client_control.DoEchoRpcRequest\x1a\x14.client_control.Void\"\x00\x12\x38\n\x08Shutdown\x12\x14.client_control.Void\x1a\x14.client_control.Void\"\x00\x32[\n\x10ParentController\x12G\n\x17SetClientControllerPort\x12\x14.client_control.Port\x1a\x14.client_control.Void\"\x00\x62\x06proto3"

# Get the generated descriptor pool and add the serialized file to it
# This makes the protocol buffer definitions available for use
pool = Google::Protobuf::DescriptorPool.generated_pool
pool.add_serialized_file(descriptor_data)

# Module namespace for the client control protocol buffer messages
module ClientControl
  # Message class for DoEchoRpcRequest containing a single string field 'request'
  DoEchoRpcRequest = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("client_control.DoEchoRpcRequest").msgclass
  
  # Empty message class (Void) used for RPC methods that don't need parameters or return values
  Void = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("client_control.Void").msgclass
  
  # Message class for Port containing a single integer field 'port'
  Port = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("client_control.Port").msgclass
end
```

The comments explain:
1. The overall purpose of the code (Protocol Buffer definitions loading)
2. The structure of the serialized descriptor data
3. Each component's role in the system
4. The purpose of each message type
5. The module organization of the generated classes

The code appears to be part of an RPC (Remote Procedure Call) system where:
- ClientController service provides DoEchoRpc and Shutdown methods
- ParentController service provides SetClientControllerPort method
- Various message types are used as parameters and return values for these RPC methods
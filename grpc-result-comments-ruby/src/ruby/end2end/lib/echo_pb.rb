Here's the commented version of the code:

```c++
# Require the Google Protocol Buffers library for Ruby
require 'google/protobuf'

# Binary descriptor data containing the compiled Protocol Buffer definition
# This is a serialized version of the echo.proto file containing:
# - A service named EchoServer with an Echo RPC method
# - Message types EchoRequest (with 'request' string field)
# - Message type EchoReply (with 'response' string field)
descriptor_data = "\n\necho.proto\x12\x04\x65\x63ho\"\x1e\n\x0b\x45\x63hoRequest\x12\x0f\n\x07request\x18\x01 \x01(\t\"\x1d\n\tEchoReply\x12\x10\n\x08response\x18\x01 \x01(\t2:\n\nEchoServer\x12,\n\x04\x45\x63ho\x12\x11.echo.EchoRequest\x1a\x0f.echo.EchoReply\"\x00\x62\x06proto3"

# Get the generated descriptor pool (which holds all message and service descriptors)
pool = Google::Protobuf::DescriptorPool.generated_pool

# Add the serialized file descriptor to the pool
# This makes the message types and services available for use
pool.add_serialized_file(descriptor_data)

# Define the Echo module to namespace our Protocol Buffer classes
module Echo
  # Look up and create a Ruby class for the EchoRequest message type
  # This allows creating and manipulating EchoRequest protocol buffer messages
  EchoRequest = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("echo.EchoRequest").msgclass
  
  # Look up and create a Ruby class for the EchoReply message type
  # This allows creating and manipulating EchoReply protocol buffer messages
  EchoReply = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("echo.EchoReply").msgclass
end
```

The comments explain:
1. The required dependencies
2. The purpose of the binary descriptor data
3. The descriptor pool operations
4. The module and class definitions for the Protocol Buffer messages
5. How the message classes are created from the descriptor pool

The code essentially defines a Protocol Buffer service called EchoServer with:
- An Echo method that takes EchoRequest and returns EchoReply
- Message types for request/response with string fields
- Ruby classes to work with these Protocol Buffer messages
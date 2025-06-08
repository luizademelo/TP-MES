Here's the commented version of the code:

```c++
# Require the Google Protocol Buffers library for Ruby
require 'google/protobuf'

# Binary descriptor data for the Protocol Buffer definitions
# This is a serialized version of the math.proto file containing:
# - DivArgs message (dividend and divisor fields)
# - DivReply message (quotient and remainder fields)
# - FibArgs message (limit field)
# - Num message (single num field)
# - FibReply message (count field)
# - Math service with RPC methods (Div, DivMany, Fib, Sum)
descriptor_data = "\n\nmath.proto\x12\x04math\",\n\x07\x44ivArgs\x12\x10\n\x08\x64ividend\x18\x01 \x01(\x03\x12\x0f\n\x07\x64ivisor\x18\x02 \x01(\x03\"/\n\x08\x44ivReply\x12\x10\n\x08quotient\x18\x01 \x01(\x03\x12\x11\n\tremainder\x18\x02 \x01(\x03\"\x18\n\x07\x46ibArgs\x12\r\n\x05limit\x18\x01 \x01(\x03\"\x12\n\x03Num\x12\x0b\n\x03num\x18\x01 \x01(\x03\"\x19\n\x08\x46ibReply\x12\r\n\x05\x63ount\x18\x01 \x01(\x03\x32\xa4\x01\n\x04Math\x12&\n\x03\x44iv\x12\r.math.DivArgs\x1a\x0e.math.DivReply\"\x00\x12.\n\x07\x44ivMany\x12\r.math.DivArgs\x1a\x0e.math.DivReply\"\x00(\x01\x30\x01\x12#\n\x03\x46ib\x12\r.math.FibArgs\x1a\t.math.Num\"\x00\x30\x01\x12\x1f\n\x03Sum\x12\t.math.Num\x1a\t.math.Num\"\x00(\x01\x62\x06proto3"

# Get the generated descriptor pool and add the serialized file
# This loads the protocol buffer definitions into memory
pool = Google::Protobuf::DescriptorPool.generated_pool
pool.add_serialized_file(descriptor_data)

# Define a Math module that contains Ruby classes for each Protocol Buffer message
module Math
  # Ruby class for DivArgs protocol buffer message
  DivArgs = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("math.DivArgs").msgclass
  
  # Ruby class for DivReply protocol buffer message
  DivReply = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("math.DivReply").msgclass
  
  # Ruby class for FibArgs protocol buffer message
  FibArgs = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("math.FibArgs").msgclass
  
  # Ruby class for Num protocol buffer message
  Num = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("math.Num").msgclass
  
  # Ruby class for FibReply protocol buffer message
  FibReply = ::Google::Protobuf::DescriptorPool.generated_pool.lookup("math.FibReply").msgclass
end
```

The comments explain:
1. The Protocol Buffers library requirement
2. The purpose of the binary descriptor data
3. The message types and service defined in the proto file
4. The descriptor pool loading process
5. Each generated Ruby class that corresponds to a Protocol Buffer message type

The code appears to be setting up Protocol Buffer message classes for a math service that includes division and Fibonacci sequence operations.
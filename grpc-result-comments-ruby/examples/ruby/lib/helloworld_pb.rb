Here's the commented version of the code:

```c++
# Require the Google Protocol Buffers library for Ruby
require 'google/protobuf'

# Build protocol buffer message definitions in the generated descriptor pool
Google::Protobuf::DescriptorPool.generated_pool.build do
  # Define a HelloRequest message type with:
  # - A single optional field 'name' of type string
  # - Field tag number 1 (Protocol Buffers uses tag numbers for binary encoding)
  add_message "helloworld.HelloRequest" do
    optional :name, :string, 1
  end

  # Define a HelloReply message type with:
  # - A single optional field 'message' of type string
  # - Field tag number 1
  add_message "helloworld.HelloReply" do
    optional :message, :string, 1
  end
end

# Module namespace for the HelloWorld protocol buffer messages
module Helloworld
  # Retrieve and store the message class for HelloRequest from the descriptor pool
  HelloRequest = Google::Protobuf::DescriptorPool.generated_pool.lookup("helloworld.HelloRequest").msgclass
  
  # Retrieve and store the message class for HelloReply from the descriptor pool
  HelloReply = Google::Protobuf::DescriptorPool.generated_pool.lookup("helloworld.HelloReply").msgclass
end
```

The comments explain:
1. The overall purpose of the code (Protocol Buffer message definition)
2. Each message type and its fields
3. The meaning of the field parameters (name, type, tag number)
4. The module organization
5. The message class retrieval process

This appears to be part of a gRPC service definition where HelloRequest would be the request message and HelloReply would be the response message in a simple greeting service.
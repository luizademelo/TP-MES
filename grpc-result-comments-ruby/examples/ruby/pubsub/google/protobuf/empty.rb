Here's the commented version of the code:

```c++
# Copyright 2015 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Require the Google Protocol Buffers library
require 'google/protobuf'

# Build a descriptor pool for Protocol Buffer messages
Google::Protobuf::DescriptorPool.generated_pool.build do
  # Define an empty message type in the protocol buffers format
  # This represents a message with no fields, often used as a placeholder
  # or for void return types in RPC services
  add_message "google.protobuf.Empty" do
  end
end

module Google
  module Protobuf
    # Create a Ruby class that represents the Empty message type
    # This allows for easy instantiation and handling of Empty messages
    # in Ruby code while maintaining Protocol Buffers compatibility
    Empty = Google::Protobuf::DescriptorPool.generated_pool.lookup("google.protobuf.Empty").msgclass
  end
end
```

Key points explained in the comments:
1. The license header is preserved as it's important legal information
2. The `require` statement is explained as loading the Protocol Buffers library
3. The descriptor pool creation is documented as the container for Protocol Buffer message definitions
4. The `Empty` message is explained as a message with no fields and its common use cases
5. The module definition shows how the message type is made available as a Ruby class

The comments maintain a balance between explaining the what and the why, without being overly verbose about implementation details that are clear from the code itself.
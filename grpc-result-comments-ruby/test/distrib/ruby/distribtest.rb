Here's the commented version of the code snippet:

```c++
#!/usr/bin/env ruby

# Copyright 2016 gRPC authors.
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

# Require the gRPC Ruby library to enable gRPC functionality
require 'grpc'

# Create a new insecure gRPC channel to connect to localhost on port 1000
# Parameters:
#   'localhost:1000' - The server address and port to connect to
#   nil - Channel arguments (none specified in this case)
#   :this_channel_is_insecure - Specifies that the channel should not use TLS/SSL
ch = GRPC::Core::Channel.new('localhost:1000', nil, :this_channel_is_insecure)

# Properly shut down and clean up the channel resources
ch.destroy

# Print success message indicating the script completed without errors
puts "Success!"
```

Key improvements made:
1. Fixed the license comment formatting (added missing # and fixed line breaks)
2. Added clear explanations for each functional part of the code
3. Documented the parameters for the Channel.new constructor
4. Explained the purpose of each operation
5. Maintained the original functionality while making it more understandable
6. Added context about what the script is doing at each step

The comments now provide a clear understanding of what the code does, why each operation is performed, and how the gRPC channel is being used.
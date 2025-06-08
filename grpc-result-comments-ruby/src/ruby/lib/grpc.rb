Here's the commented version of the code snippet:

```c++
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Define the path to the SSL root certificates file
# The path is expanded relative to the current file's location
ssl_roots_path = File.expand_path('../../../../etc/roots.pem', __FILE__)

# Require all necessary gRPC Ruby library components
require_relative 'grpc/errors'           # gRPC error classes
require_relative 'grpc/structs'          # gRPC data structures
require_relative 'grpc/grpc'             # Core gRPC functionality
require_relative 'grpc/logconfig'        # Logging configuration
require_relative 'grpc/notifier'         # Notification system
require_relative 'grpc/version'          # Version information
require_relative 'grpc/core/status_codes' # gRPC status codes
require_relative 'grpc/core/time_consts'  # Time constants
require_relative 'grpc/generic/active_call'  # Active call handling
require_relative 'grpc/generic/client_stub'  # Client stub implementation
require_relative 'grpc/generic/service'      # Service definitions
require_relative 'grpc/generic/rpc_server'   # RPC server implementation
require_relative 'grpc/generic/interceptors' # Interceptor functionality

# Load and set default SSL root certificates
begin
  # Open the SSL roots file
  file = File.open(ssl_roots_path)
  # Read the contents of the file
  roots = file.read
  # Set the default root certificates for gRPC channel credentials
  GRPC::Core::ChannelCredentials.set_default_roots_pem roots
ensure
  # Ensure the file is always closed, even if an error occurs
  file.close
end
```

Key comments added:
1. Explained the SSL roots path configuration
2. Documented each required gRPC component
3. Added detailed comments about the SSL certificate loading process
4. Explained the begin/ensure block for proper file handling
5. Noted the purpose of each major operation

The comments provide clear explanations of what each part of the code does while maintaining readability.
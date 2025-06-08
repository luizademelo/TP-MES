Here's the commented version of the code:

```c++
# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require_relative './structs'

module GRPC
  # Utility class for working with Google RPC status messages in gRPC
  class GoogleRpcStatusUtils
    # Extracts and decodes a Google RPC status from a gRPC status object
    #
    # @param status [Struct::Status] The gRPC status object containing metadata
    # @return [Google::Rpc::Status, nil] The decoded Google RPC status or nil if not present
    # @raise [ArgumentError] If the input is not a Struct::Status object
    def self.extract_google_rpc_status(status)
      # Validate input type
      fail ArgumentError, 'bad type' unless status.is_a? Struct::Status
      
      # Key for the status details in the metadata
      grpc_status_details_bin_trailer = 'grpc-status-details-bin'
      
      # Get the binary status from metadata
      binstatus = status.metadata[grpc_status_details_bin_trailer]
      
      # Return nil if no status details are present
      return nil if binstatus.nil?

      # Load required dependencies
      require_relative './grpc'
      require 'google/rpc/status_pb'

      # Decode and return the Google RPC status
      Google::Rpc::Status.decode(binstatus)
    end
  end
end
```

The comments explain:
1. The overall purpose of the class (Google RPC status utility)
2. The method's purpose, parameters, return value, and possible exceptions
3. The validation step
4. The metadata key being used
5. The early return case
6. The dependency loading
7. The final decoding operation

The comments are kept concise while providing all the essential information a developer would need to understand and use this code. They follow Ruby documentation conventions and explain both the "what" and the "why" of the implementation.
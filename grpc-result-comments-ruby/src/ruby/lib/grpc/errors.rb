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

require_relative './structs'
require_relative './core/status_codes'
require_relative './google_rpc_status_utils'

module GRPC
  # Custom exception class for gRPC bad status errors
  # Includes status code, details, metadata, and debug error string
  class BadStatus < StandardError
    attr_reader :code, :details, :metadata, :debug_error_string

    include GRPC::Core::StatusCodes  # Mixin for status code constants

    # Initialize a BadStatus exception
    # @param code [Integer] The gRPC status code
    # @param details [String] Error details (default: 'unknown cause')
    # @param metadata [Hash] Additional metadata (default: {})
    # @param debug_error_string [String] Debug error information (default: nil)
    def initialize(code,
                   details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      # Construct the exception message combining all available information
      exception_message = "#{code}:#{details}"
      if debug_error_string
        exception_message += ". debug_error_string:{#{debug_error_string}}"
      end
      super(exception_message)
      @code = code
      @details = details
      @metadata = metadata
      @debug_error_string = debug_error_string
    end

    # Convert the exception to a Status struct
    # @return [Struct::Status] The status representation of this exception
    def to_status
      Struct::Status.new(code, details, metadata, debug_error_string)
    end

    # Convert the exception to a Google RPC status
    # @return [Google::Rpc::Status] The Google RPC status representation
    # @note Logs warnings if parsing fails
    def to_rpc_status
      GoogleRpcStatusUtils.extract_google_rpc_status(to_status)
    rescue Google::Protobuf::ParseError => parse_error
      GRPC.logger.warn('parse error: to_rpc_status failed')
      GRPC.logger.warn(parse_error)
      nil
    end

    # Factory method to create appropriate status exception based on code
    # @param code [Integer] The gRPC status code
    # @param details [String] Error details (default: 'unknown cause')
    # @param metadata [Hash] Additional metadata (default: {})
    # @param debug_error_string [String] Debug error information (default: nil)
    # @return [BadStatus] An instance of BadStatus or one of its subclasses
    def self.new_status_exception(code,
                                  details = 'unknown cause',
                                  metadata = {},
                                  debug_error_string = nil)
      # Mapping of status codes to their corresponding exception classes
      codes = {}
      codes[OK] = Ok
      codes[CANCELLED] = Cancelled
      codes[UNKNOWN] = Unknown
      codes[INVALID_ARGUMENT] = InvalidArgument
      codes[DEADLINE_EXCEEDED] = DeadlineExceeded
      codes[NOT_FOUND] = NotFound
      codes[ALREADY_EXISTS] = AlreadyExists
      codes[PERMISSION_DENIED] = PermissionDenied
      codes[UNAUTHENTICATED] = Unauthenticated
      codes[RESOURCE_EXHAUSTED] = ResourceExhausted
      codes[FAILED_PRECONDITION] = FailedPrecondition
      codes[ABORTED] = Aborted
      codes[OUT_OF_RANGE] = OutOfRange
      codes[UNIMPLEMENTED] = Unimplemented
      codes[INTERNAL] = Internal
      codes[UNAVAILABLE] = Unavailable
      codes[DATA_LOSS] = DataLoss

      # Return specific exception class if mapped, otherwise generic BadStatus
      if codes[code].nil?
        BadStatus.new(code, details, metadata, debug_error_string)
      else
        codes[code].new(details, metadata, debug_error_string)
      end
    end
  end

  # Following are specialized exception classes for each gRPC status code
  # Each class inherits from BadStatus and sets its specific status code
  
  # OK status (0)
  class Ok < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::OK,
            details, metadata, debug_error_string)
    end
  end

  # CANCELLED status (1)
  class Cancelled < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::CANCELLED,
            details, metadata, debug_error_string)
    end
  end

  # UNKNOWN status (2)
  class Unknown < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::UNKNOWN,
            details, metadata, debug_error_string)
    end
  end

  # INVALID_ARGUMENT status (3)
  class InvalidArgument < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::INVALID_ARGUMENT,
            details, metadata, debug_error_string)
    end
  end

  # DEADLINE_EXCEEDED status (4)
  class DeadlineExceeded < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::DEADLINE_EXCEEDED,
            details, metadata, debug_error_string)
    end
  end

  # NOT_FOUND status (5)
  class NotFound < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::NOT_FOUND,
            details, metadata, debug_error_string)
    end
  end

  # ALREADY_EXISTS status (6)
  class AlreadyExists < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::ALREADY_EXISTS,
            details, metadata, debug_error_string)
    end
  end

  # PERMISSION_DENIED status (7)
  class PermissionDenied < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::PERMISSION_DENIED,
            details, metadata, debug_error_string)
    end
  end

  # UNAUTHENTICATED status (16)
  class Unauthenticated < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::UNAUTHENTICATED,
            details, metadata, debug_error_string)
    end
  end

  # RESOURCE_EXHAUSTED status (8)
  class ResourceExhausted < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::RESOURCE_EXHAUSTED,
            details, metadata, debug_error_string)
    end
  end

  # FAILED_PRECONDITION status (9)
  class FailedPrecondition < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::FAILED_PRECONDITION,
            details, metadata, debug_error_string)
    end
  end

  # ABORTED status (10)
  class Aborted < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::ABORTED,
            details, metadata, debug_error_string)
    end
  end

  # OUT_OF_RANGE status (11)
  class OutOfRange < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::OUT_OF_RANGE,
            details, metadata, debug_error_string)
    end
  end

  # UNIMPLEMENTED status (12)
  class Unimplemented < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::UNIMPLEMENTED,
            details, metadata, debug_error_string)
    end
  end

  # INTERNAL status (13)
  class Internal < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::INTERNAL,
            details, metadata, debug_error_string)
    end
  end

  # UNAVAILABLE status (14)
  class Unavailable < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::UNAVAILABLE,
            details, metadata, debug_error_string)
    end
  end

  # DATA_LOSS status (15)
  class DataLoss < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::DATA_LOSS,
            details, metadata, debug_error_string)
    end
  end
end
```

The comments I've added:
1. Explain the overall purpose of the BadStatus class and its components
2. Document all method parameters and return values
3. Explain the factory method pattern used in new_status_exception
4. Added specific comments for each status code subclass
5. Included notes about error handling and logging
6. Added the numeric status codes in comments for each subclass for quick reference
7. Explained the mixin usage for status codes

The comments follow a consistent style and provide enough information for future maintainers to understand the code's purpose and behavior without being overly verbose.
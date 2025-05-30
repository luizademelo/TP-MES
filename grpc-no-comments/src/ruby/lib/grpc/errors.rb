# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require_relative './structs'
require_relative './core/status_codes'
require_relative './google_rpc_status_utils'

module GRPC

  class BadStatus < StandardError
    attr_reader :code, :details, :metadata, :debug_error_string

    include GRPC::Core::StatusCodes

    def initialize(code,
                   details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
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

    def to_status
      Struct::Status.new(code, details, metadata, debug_error_string)
    end

    def to_rpc_status
      GoogleRpcStatusUtils.extract_google_rpc_status(to_status)
    rescue Google::Protobuf::ParseError => parse_error
      GRPC.logger.warn('parse error: to_rpc_status failed')
      GRPC.logger.warn(parse_error)
      nil
    end

    def self.new_status_exception(code,
                                  details = 'unknown cause',
                                  metadata = {},
                                  debug_error_string = nil)
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

      if codes[code].nil?
        BadStatus.new(code, details, metadata, debug_error_string)
      else
        codes[code].new(details, metadata, debug_error_string)
      end
    end
  end

  class Ok < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::OK,
            details, metadata, debug_error_string)
    end
  end

  class Cancelled < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::CANCELLED,
            details, metadata, debug_error_string)
    end
  end

  class Unknown < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::UNKNOWN,
            details, metadata, debug_error_string)
    end
  end

  class InvalidArgument < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::INVALID_ARGUMENT,
            details, metadata, debug_error_string)
    end
  end

  class DeadlineExceeded < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::DEADLINE_EXCEEDED,
            details, metadata, debug_error_string)
    end
  end

  class NotFound < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::NOT_FOUND,
            details, metadata, debug_error_string)
    end
  end

  class AlreadyExists < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::ALREADY_EXISTS,
            details, metadata, debug_error_string)
    end
  end

  # GRPC status code corresponding to status PERMISSION_DENIED
  class PermissionDenied < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::PERMISSION_DENIED,
            details, metadata, debug_error_string)
    end
  end

  class Unauthenticated < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::UNAUTHENTICATED,
            details, metadata, debug_error_string)
    end
  end

  class ResourceExhausted < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::RESOURCE_EXHAUSTED,
            details, metadata, debug_error_string)
    end
  end

  class FailedPrecondition < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::FAILED_PRECONDITION,
            details, metadata, debug_error_string)
    end
  end

  class Aborted < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::ABORTED,
            details, metadata, debug_error_string)
    end
  end

  class OutOfRange < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::OUT_OF_RANGE,
            details, metadata, debug_error_string)
    end
  end

  class Unimplemented < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::UNIMPLEMENTED,
            details, metadata, debug_error_string)
    end
  end

  class Internal < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::INTERNAL,
            details, metadata, debug_error_string)
    end
  end

  class Unavailable < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::UNAVAILABLE,
            details, metadata, debug_error_string)
    end
  end

  class DataLoss < BadStatus
    def initialize(details = 'unknown cause',
                   metadata = {},
                   debug_error_string = nil)
      super(Core::StatusCodes::DATA_LOSS,
            details, metadata, debug_error_string)
    end
  end
end

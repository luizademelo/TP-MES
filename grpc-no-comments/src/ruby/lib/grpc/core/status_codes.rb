# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

module GRPC
  module Core

    module StatusCodes

      OK = 0

      CANCELLED = 1

      UNKNOWN = 2

      INVALID_ARGUMENT = 3

      DEADLINE_EXCEEDED = 4

      NOT_FOUND = 5

      ALREADY_EXISTS = 6

      # PermissionDenied indicates the caller does not have permission to

      PERMISSION_DENIED = 7

      RESOURCE_EXHAUSTED = 8

      FAILED_PRECONDITION = 9

      ABORTED = 10

      OUT_OF_RANGE = 11

      UNIMPLEMENTED = 12

      INTERNAL = 13

      UNAVAILABLE = 14

      DATA_LOSS = 15

      UNAUTHENTICATED = 16
    end
  end
end

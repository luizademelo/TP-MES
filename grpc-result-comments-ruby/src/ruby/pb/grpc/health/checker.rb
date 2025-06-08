Here's the commented version of the code:

```c++
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'grpc'
require 'grpc/health/v1/health_services_pb'

module Grpc
  module Health
    # Implementation of the gRPC Health Checking Protocol.
    # This class provides methods to manage and check the health status of services.
    class Checker < V1::Health::Service
      # Status codes from gRPC core
      StatusCodes = GRPC::Core::StatusCodes
      # Response message type for health checks
      HealthCheckResponse = V1::HealthCheckResponse

      # Initializes a new health checker with empty statuses and a mutex for thread safety.
      def initialize
        # Hash to store service statuses (service_name => status)
        @statuses = {}
        # Mutex to ensure thread-safe access to @statuses
        @status_mutex = Mutex.new
      end

      # Checks the health status of a service.
      # @param req [HealthCheckRequest] The request containing the service name to check
      # @param _call [GRPC::ActiveCall] The gRPC call object (unused)
      # @return [HealthCheckResponse] The health status response
      # @raise [GRPC::BadStatus] if the service is not found
      def check(req, _call)
        status = nil
        # Thread-safe access to the statuses
        @status_mutex.synchronize do
          status = @statuses["#{req.service}"]
        end
        if status.nil?
          fail GRPC::BadStatus.new_status_exception(StatusCodes::NOT_FOUND)
        end
        HealthCheckResponse.new(status: status)
      end

      # Adds or updates the health status for a single service.
      # @param service [String] The name of the service
      # @param status [Symbol] The health status to set
      def add_status(service, status)
        @status_mutex.synchronize { @statuses["#{service}"] = status }
      end

      # Sets the same health status for multiple services.
      # @param status [Symbol] The health status to set
      # @param services [Array<String>] List of service names to update
      def set_status_for_services(status, *services)
        @status_mutex.synchronize do
          services.each { |service| @statuses["#{service}"] = status }
        end
      end

      # Adds or updates health statuses for multiple services from a hash.
      # @param service_statuses [Hash] Map of service names to statuses
      def add_statuses(service_statuses = {})
        @status_mutex.synchronize do
          service_statuses.each_pair { |service, status| @statuses["#{service}"] = status }
        end
      end

      # Clears the health status for a specific service.
      # @param service [String] The name of the service to clear
      def clear_status(service)
        @status_mutex.synchronize { @statuses.delete("#{service}") }
      end

      # Clears all health statuses.
      def clear_all
        @status_mutex.synchronize { @statuses = {} }
      end
    end
  end
end
```

The comments provide:
1. A class-level description explaining the purpose of the Health Checker
2. Method-level documentation explaining each method's purpose, parameters, and return values
3. Explanation of instance variables and their roles
4. Notes about thread-safety where relevant
5. Clarification about the gRPC-specific components being used

The comments maintain a consistent style and provide enough detail to understand the code's functionality without being overly verbose. They also highlight important aspects like thread-safety and error conditions.
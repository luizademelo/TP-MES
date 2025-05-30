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

    class Checker < V1::Health::Service
      StatusCodes = GRPC::Core::StatusCodes
      HealthCheckResponse = V1::HealthCheckResponse

      def initialize
        @statuses = {}
        @status_mutex = Mutex.new
      end

      def check(req, _call)
        status = nil
        @status_mutex.synchronize do
          status = @statuses["#{req.service}"]
        end
        if status.nil?
          fail GRPC::BadStatus.new_status_exception(StatusCodes::NOT_FOUND)
        end
        HealthCheckResponse.new(status: status)
      end

      def add_status(service, status)
        @status_mutex.synchronize { @statuses["#{service}"] = status }
      end

      def set_status_for_services(status, *services)
        @status_mutex.synchronize do
          services.each { |service| @statuses["#{service}"] = status }
        end
      end

      def add_statuses(service_statuses = {})
        @status_mutex.synchronize do
          service_statuses.each_pair { |service, status| @statuses["#{service}"] = status }
        end
      end

      def clear_status(service)
        @status_mutex.synchronize { @statuses.delete("#{service}") }
      end

      def clear_all
        @status_mutex.synchronize { @statuses = {} }
      end
    end
  end
end

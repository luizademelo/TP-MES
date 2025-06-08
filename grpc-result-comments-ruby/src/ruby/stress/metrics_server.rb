Here's the commented version of the code:

```c++
# Copyright 2016 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# distributed under the License is distributed on an "AS IS" BASIS,
#
# See the License for the specific language governing permissions and
# limitations under the License.

# Require the generated Protocol Buffer files for metrics service
require_relative '../pb/grpc/testing/metrics_pb.rb'
require_relative '../pb/grpc/testing/metrics_services_pb.rb'

# Abstract base class for gauge implementations
# All methods must be implemented by subclasses
class Gauge
  # Abstract method to get the gauge name
  def get_name
    raise NoMethodError.new
  end

  # Abstract method to get the gauge type
  def get_type
    raise NoMethodError.new
  end

  # Abstract method to get the gauge value
  def get_value
    raise NoMethodError.new
  end
end

# Implementation of the gRPC Metrics Service
class MetricsServiceImpl < Grpc::Testing::MetricsService::Service
  include Grpc::Testing
  @gauges  # Instance variable to store registered gauges

  # Initialize the service with an empty hash to store gauges
  def initialize
    @gauges = {}
  end

  # Register a gauge in the service
  # @param gauge [Gauge] The gauge to register
  def register_gauge(gauge)
    @gauges[gauge.get_name] = gauge
  end

  # Create a GaugeResponse protobuf message from a gauge
  # @param gauge [Gauge] The gauge to convert to a response
  # @return [GaugeResponse] The protobuf response message
  def make_gauge_response(gauge)
    response = GaugeResponse.new(:name => gauge.get_name)
    value = gauge.get_value
    
    # Set the appropriate value field based on the gauge type
    case gauge.get_type
    when 'long'
      response.long_value = value
    when 'double'
      response.double_value = value
    when 'string'
      response.string_value = value
    end
    response
  end

  # gRPC service method to get all registered gauges
  # @param _empty [Empty] Empty request parameter (unused)
  # @param _call [GRPC::ActiveCall] The gRPC call object (unused)
  # @return [Array<GaugeResponse>] Array of gauge responses
  def get_all_gauges(_empty, _call)
    @gauges.values.map do |gauge|
      make_gauge_response gauge
    end
  end

  # gRPC service method to get a specific gauge by name
  # @param gauge_req [GaugeRequest] The request containing the gauge name
  # @param _call [GRPC::ActiveCall] The gRPC call object (unused)
  # @return [GaugeResponse] The response for the requested gauge
  def get_gauge(gauge_req, _call)
    gauge = @gauges[gauge_req.name]
    make_gauge_response gauge
  end
end
```

Key improvements made:
1. Added class-level documentation for both classes
2. Added method-level documentation for all methods
3. Documented parameters and return values
4. Explained the purpose of the abstract methods in Gauge class
5. Added comments about the gauge type handling in make_gauge_response
6. Clarified the purpose of unused parameters in gRPC methods
7. Maintained consistent comment style throughout

The comments now provide clear guidance for future developers about:
- The purpose of each component
- How to use the classes and methods
- What parameters are expected
- What values are returned
- The internal logic of key methods
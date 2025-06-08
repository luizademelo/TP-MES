Here's the commented version of the code:

```ruby
#!/usr/bin/env ruby

# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Set up the load path to include the library directory
this_dir = File.expand_path(File.dirname(__FILE__))
lib_dir = File.join(File.dirname(this_dir), 'lib')
$LOAD_PATH.unshift(lib_dir) unless $LOAD_PATH.include?(lib_dir)

# Require necessary libraries
require 'grpc'
require 'multi_json'
require 'route_guide_services_pb'

include Routeguide

# Constants for coordinate conversion and Earth's radius in meters
COORD_FACTOR = 1e7  # Conversion factor for coordinates
RADIUS = 637_100    # Earth's radius in meters

# Calculates the distance between two geographic points using the Haversine formula
# @param point_a [Point] First geographic point
# @param point_b [Point] Second geographic point
# @return [Integer] Distance between points in meters
def calculate_distance(point_a, point_b)
  to_radians = proc { |x| x * Math::PI / 180 }
  # Convert latitude and longitude to radians
  lat_a = to_radians.call(point_a.latitude / COORD_FACTOR)
  lat_b = to_radians.call(point_b.latitude / COORD_FACTOR)
  lon_a = to_radians.call(point_a.longitude / COORD_FACTOR)
  lon_b = to_radians.call(point_b.longitude / COORD_FACTOR)
  
  # Calculate differences
  delta_lat = lat_a - lat_b
  delta_lon = lon_a - lon_b
  
  # Haversine formula
  a = Math.sin(delta_lat / 2)**2 +
      Math.cos(lat_a) * Math.cos(lat_b) +
      Math.sin(delta_lon / 2)**2
  (2 * RADIUS * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a))).to_i
end

# Enumerator for features within a rectangular boundary
class RectangleEnum
  def initialize(feature_db, bounds)
    @feature_db = feature_db  # Database of features
    @bounds = bounds          # Boundary rectangle
    
    # Determine min/max latitude and longitude from bounds
    lats = [@bounds.lo.latitude, @bounds.hi.latitude]
    longs = [@bounds.lo.longitude, @bounds.hi.longitude]
    @lo_lat, @hi_lat = lats.min, lats.max
    @lo_long, @hi_long = longs.min, longs.max
  end

  # Checks if a location is within the rectangle bounds
  # @param location [Hash] Location with 'latitude' and 'longitude' keys
  # @return [Boolean] True if location is within bounds
  def in?(location)
    location['longitude'] >= @lo_long &&
      location['longitude'] <= @hi_long &&
      location['latitude'] >= @lo_lat &&
      location['latitude'] <= @hi_lat
  end

  # Enumerates features within the rectangle bounds
  # @yield [Feature] Yields each feature within bounds
  # @return [Enumerator] Returns enumerator if no block given
  def each
    return enum_for(:each) unless block_given?
    @feature_db.each_pair do |location, name|
      next unless in?(location)
      next if name.nil? || name == ''
      pt = Point.new(
        Hash[location.each_pair.map { |k, v| [k.to_sym, v] }])
      yield Feature.new(location: pt, name: name)
    end
  end
end

# Implementation of RouteGuide service
class ServerImpl < RouteGuide::Service
  def initialize(feature_db)
    @feature_db = feature_db  # Database of features
    @received_notes = Hash.new { |h, k| h[k] = [] }  # Stores received route notes
  end

  # Gets the feature at the given point
  # @param point [Point] The geographic point to check
  # @param _call [GRPC::ActiveCall] The gRPC call object
  # @return [Feature] The feature at the given point
  def get_feature(point, _call)
    name = @feature_db[{
      'longitude' => point.longitude,
      'latitude' => point.latitude }] || ''
    Feature.new(location: point, name: name)
  end

  # Lists features within the given rectangle
  # @param rectangle [Rectangle] The area to search
  # @param _call [GRPC::ActiveCall] The gRPC call object
  # @return [Enumerator] Enumerator of features in the rectangle
  def list_features(rectangle, _call)
    RectangleEnum.new(@feature_db, rectangle).each
  end

  # Records a route and calculates statistics
  # @param call [GRPC::ActiveCall] The gRPC call object
  # @return [RouteSummary] Summary of the route
  def record_route(call)
    started, elapsed_time = 0, 0
    distance, count, features, last = 0, 0, 0, nil
    
    call.each_remote_read do |point|
      count += 1
      name = @feature_db[{
        'longitude' => point.longitude,
        'latitude' => point.latitude }] || ''
      features += 1 unless name == ''
      
      if last.nil?
        last = point
        started = Time.now.to_i
        next
      end
      
      elapsed_time = Time.now.to_i - started
      distance += calculate_distance(point, last)
      last = point
    end
    
    RouteSummary.new(point_count: count,
                     feature_count: features,
                     distance: distance,
                     elapsed_time: elapsed_time)
  end

  # Handles bidirectional streaming for route chat
  # @param notes [Enumerator] Incoming route notes
  # @return [Enumerator] Enumerator of route notes
  def route_chat(notes)
    RouteChatEnumerator.new(notes, @received_notes).each_item
  end
end

# Enumerator for route chat messages
class RouteChatEnumerator
  def initialize(notes, received_notes)
    @notes = notes            # Incoming notes
    @received_notes = received_notes  # Storage for all received notes
  end
  
  # Enumerates chat messages and stores new ones
  # @yield [RouteNote] Yields each relevant note
  # @return [Enumerator] Returns enumerator if no block given
  def each_item
    return enum_for(:each_item) unless block_given?
    begin
      @notes.each do |n|
        key = {
          'latitude' => n.location.latitude,
          'longitude' => n.location.longitude
        }
        earlier_msgs = @received_notes[key]
        @received_notes[key] << n.message

        earlier_msgs.each do |r|
          yield RouteNote.new(location: n.location, message: r)
        end
      end
    rescue StandardError => e
      fail e
    end
  end
end

# Main entry point for the server
def main
  if ARGV.length == 0
    fail 'Please specify the path to the route_guide json database'
  end
  
  # Load feature database from JSON file
  raw_data = []
  File.open(ARGV[0]) do |f|
    raw_data = MultiJson.load(f.read)
  end
  feature_db = Hash[raw_data.map { |x| [x['location'], x['name']] }]
  
  # Configure and start gRPC server
  port = '0.0.0.0:50051'
  s = GRPC::RpcServer.new
  s.add_http2_port(port, :this_port_is_insecure)
  GRPC.logger.info("... running insecurely on #{port}")
  s.handle(ServerImpl.new(feature_db))
  
  # Run server until interrupted
  s.run_till_terminated_or_interrupted([1, 'int', 'SIGTERM'])
end

main
```

The comments I've added:
1. Explain the purpose of each major section and class
2. Document method parameters and return values
3. Clarify complex calculations (like the distance formula)
4. Note important implementation details
5. Maintain a consistent style throughout
6. Include both high-level overviews and specific details where needed

The comments are designed to help future developers understand:
- What the code does
- Why it does it that way
- How to use the various components
- Important implementation details
- The overall architecture of the service
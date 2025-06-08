Here's the commented version of the code:

```c++
#!/usr/bin/env ruby

# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Set up the load path to include the lib directory
this_dir = File.expand_path(File.dirname(__FILE__))
lib_dir = File.join(File.dirname(this_dir), 'lib')
$LOAD_PATH.unshift(lib_dir) unless $LOAD_PATH.include?(lib_dir)

# Require necessary libraries
require 'grpc'            # gRPC library
require 'multi_json'      # JSON parsing library
require 'route_guide_services_pb'  # Generated protobuf service definitions

include Routeguide  # Include the Routeguide module for generated protobuf classes

# Predefined points for GetFeature requests
GET_FEATURE_POINTS = [
  Point.new(latitude:  409_146_138, longitude: -746_188_906),
  Point.new(latitude:  0, longitude: 0)
]

# Makes GetFeature RPC calls for each predefined point
# @param stub [RouteGuide::Stub] the gRPC client stub
def run_get_feature(stub)
  p 'GetFeature'
  p '----------'
  GET_FEATURE_POINTS.each do |pt|
    resp = stub.get_feature(pt)
    if resp.name != ''
      p "- found '#{resp.name}' at #{pt.inspect}"
    else
      p "- found nothing at #{pt.inspect}"
    end
  end
end

# Defines a rectangle area for ListFeatures requests
LIST_FEATURES_RECT = Rectangle.new(
  lo: Point.new(latitude: 400_000_000, longitude: -750_000_000),
  hi: Point.new(latitude: 420_000_000, longitude: -730_000_000))

# Makes ListFeatures RPC call for the predefined rectangle
# @param stub [RouteGuide::Stub] the gRPC client stub
def run_list_features(stub)
  p 'ListFeatures'
  p '------------'
  resps = stub.list_features(LIST_FEATURES_RECT)
  resps.each do |r|
    p "- found '#{r.name}' at #{r.location.inspect}"
  end
end

# Generates random route points from a feature database
class RandomRoute
  # @param features [Array] array of feature data
  # @param size [Integer] number of points to generate
  def initialize(features, size)
    @features = features
    @size = size
  end

  # Enumerates random route points with delays
  def each
    return enum_for(:each) unless block_given?
    @size.times do
      json_feature = @features[rand(0..@features.length)]
      next if json_feature.nil?
      location = json_feature['location']
      pt = Point.new(
        Hash[location.each_pair.map { |k, v| [k.to_sym, v] }])
      p "- next point is #{pt.inspect}"
      yield pt
      sleep(rand(0..1))
    end
  end
end

# Makes RecordRoute RPC call with random route points
# @param stub [RouteGuide::Stub] the gRPC client stub
# @param features [Array] feature database to generate route from
def run_record_route(stub, features)
  p 'RecordRoute'
  p '-----------'
  points_on_route = 10
  reqs = RandomRoute.new(features, points_on_route)
  resp = stub.record_route(reqs.each)
  p "summary: #{resp.inspect}"
end

# Predefined route notes for RouteChat
ROUTE_CHAT_NOTES = [
  RouteNote.new(message: 'doh - a deer',
                location: Point.new(latitude: 0, longitude: 0)),
  RouteNote.new(message: 'ray - a drop of golden sun',
                location: Point.new(latitude: 0, longitude: 1)),
  RouteNote.new(message: 'me - the name I call myself',
                location: Point.new(latitude: 1, longitude: 0)),
  RouteNote.new(message: 'fa - a longer way to run',
                location: Point.new(latitude: 1, longitude: 1)),
  RouteNote.new(message: 'soh - with needle and a thread',
                location: Point.new(latitude: 0, longitude: 1))
]

# Makes RouteChat RPC call with predefined notes
# @param stub [RouteGuide::Stub] the gRPC client stub
def run_route_chat(stub)
  p 'Route Chat'
  p '----------'
  sleeping_enumerator = SleepingEnumerator.new(ROUTE_CHAT_NOTES, 1)
  stub.route_chat(sleeping_enumerator.each_item) { |r| p "received #{r.inspect}" }
end

# Enumerator that adds delays between items
class SleepingEnumerator
  # @param items [Array] items to enumerate
  # @param delay [Numeric] delay between items in seconds
  def initialize(items, delay)
    @items = items
    @delay = delay
  end

  # Enumerates items with delays
  def each_item
    return enum_for(:each_item) unless block_given?
    @items.each do |item|
      sleep @delay
      p "next item to send is #{item.inspect}"
      yield item
    end
  end
end

# Main execution function
def main
  # Create insecure channel to localhost:50051
  stub = RouteGuide::Stub.new('localhost:50051', :this_channel_is_insecure)
  
  # Run all demo RPC calls
  run_get_feature(stub)
  run_list_features(stub)
  run_route_chat(stub)
  
  # Skip record_route if no feature database provided
  if ARGV.length == 0
    p 'no feature database; skipping record_route'
    exit
  end
  
  # Load feature database from JSON file
  raw_data = []
  File.open(ARGV[0]) do |f|
    raw_data = MultiJson.load(f.read)
  end
  
  # Run record_route with loaded features
  run_record_route(stub, raw_data)
end

# Start the program
main
```

The comments added:
1. File header and license information
2. Load path setup explanation
3. Library requirements
4. Module inclusion
5. Constants documentation
6. Method documentation with parameters and purposes
7. Class documentation with initialization parameters
8. Main execution flow explanation
9. Important logic explanations
10. Parameter and return value documentation where applicable

The comments follow Ruby conventions and provide clear explanations of the code's functionality while maintaining readability. They focus on the "why" rather than just the "what" of the code implementation.
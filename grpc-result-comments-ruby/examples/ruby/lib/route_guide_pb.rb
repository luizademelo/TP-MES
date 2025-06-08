Here's the commented version of the code:

```c++
# Require the Google Protocol Buffers library for Ruby
require 'google/protobuf'

# Build a descriptor pool for Protocol Buffer messages in the 'routeguide' namespace
Google::Protobuf::DescriptorPool.generated_pool.build do
  # Define a Point message with latitude and longitude as 32-bit integers
  # - Field numbers 1 and 2 are used for protocol buffer binary encoding
  add_message "routeguide.Point" do
    optional :latitude, :int32, 1   # Latitude coordinate
    optional :longitude, :int32, 2  # Longitude coordinate
  end

  # Define a Rectangle message composed of two Points (lo and hi)
  # - Represents a rectangular area bounded by two diagonal points
  add_message "routeguide.Rectangle" do
    optional :lo, :message, 1, "routeguide.Point"  # Lower-left corner point
    optional :hi, :message, 2, "routeguide.Point"  # Upper-right corner point
  end

  # Define a Feature message representing a point of interest
  add_message "routeguide.Feature" do
    optional :name, :string, 1            # Name of the feature
    optional :location, :message, 2, "routeguide.Point"  # Geographic location
  end

  # Define a RouteNote message for location-based notes
  add_message "routeguide.RouteNote" do
    optional :location, :message, 1, "routeguide.Point"  # Note location
    optional :message, :string, 2                       # Note content
  end

  # Define a RouteSummary message containing statistics about a route
  add_message "routeguide.RouteSummary" do
    optional :point_count, :int32, 1    # Total number of points visited
    optional :feature_count, :int32, 2  # Number of features encountered
    optional :distance, :int32, 3       # Total distance traveled
    optional :elapsed_time, :int32, 4   # Time taken to complete route
  end
end

# Create a Routeguide module with classes for each protocol buffer message type
module Routeguide
  # Point class generated from the protocol buffer definition
  Point = Google::Protobuf::DescriptorPool.generated_pool.lookup("routeguide.Point").msgclass
  
  # Rectangle class generated from the protocol buffer definition
  Rectangle = Google::Protobuf::DescriptorPool.generated_pool.lookup("routeguide.Rectangle").msgclass
  
  # Feature class generated from the protocol buffer definition
  Feature = Google::Protobuf::DescriptorPool.generated_pool.lookup("routeguide.Feature").msgclass
  
  # RouteNote class generated from the protocol buffer definition
  RouteNote = Google::Protobuf::DescriptorPool.generated_pool.lookup("routeguide.RouteNote").msgclass
  
  # RouteSummary class generated from the protocol buffer definition
  RouteSummary = Google::Protobuf::DescriptorPool.generated_pool.lookup("routeguide.RouteSummary").msgclass
end
```
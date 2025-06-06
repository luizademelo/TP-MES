
require 'google/protobuf'

Google::Protobuf::DescriptorPool.generated_pool.build do
  add_message "routeguide.Point" do
    optional :latitude, :int32, 1
    optional :longitude, :int32, 2
  end
  add_message "routeguide.Rectangle" do
    optional :lo, :message, 1, "routeguide.Point"
    optional :hi, :message, 2, "routeguide.Point"
  end
  add_message "routeguide.Feature" do
    optional :name, :string, 1
    optional :location, :message, 2, "routeguide.Point"
  end
  add_message "routeguide.RouteNote" do
    optional :location, :message, 1, "routeguide.Point"
    optional :message, :string, 2
  end
  add_message "routeguide.RouteSummary" do
    optional :point_count, :int32, 1
    optional :feature_count, :int32, 2
    optional :distance, :int32, 3
    optional :elapsed_time, :int32, 4
  end
end

module Routeguide
  Point = Google::Protobuf::DescriptorPool.generated_pool.lookup("routeguide.Point").msgclass
  Rectangle = Google::Protobuf::DescriptorPool.generated_pool.lookup("routeguide.Rectangle").msgclass
  Feature = Google::Protobuf::DescriptorPool.generated_pool.lookup("routeguide.Feature").msgclass
  RouteNote = Google::Protobuf::DescriptorPool.generated_pool.lookup("routeguide.RouteNote").msgclass
  RouteSummary = Google::Protobuf::DescriptorPool.generated_pool.lookup("routeguide.RouteSummary").msgclass
end

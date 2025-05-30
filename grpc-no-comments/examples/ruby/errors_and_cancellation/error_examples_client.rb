#!/usr/bin/env ruby

# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

this_dir = File.expand_path(File.dirname(__FILE__))
lib_dir = File.join(File.dirname(this_dir), 'lib')
$LOAD_PATH.unshift(lib_dir) unless $LOAD_PATH.include?(lib_dir)

require 'grpc'
require 'route_guide_services_pb'

include Routeguide

def run_get_feature_expect_error(stub)
  resp = stub.get_feature(Point.new)
end

def run_list_features_expect_error(stub)
  resps = stub.list_features(Rectangle.new)

  resps.each { }
end

def run_record_route_expect_error(stub)
  stub.record_route([])
end

def run_route_chat_expect_error(stub)
  resps = stub.route_chat([])

  resps.each { }
end

def main
  stub = RouteGuide::Stub.new('localhost:50051', :this_channel_is_insecure)

  begin
    run_get_feature_expect_error(stub)
  rescue GRPC::BadStatus => e
    puts "===== GetFeature exception: ====="
    puts e.inspect
    puts "e.code: #{e.code}"
    puts "e.details: #{e.details}"
    puts "e.metadata: #{e.metadata}"
    puts "================================="
  end

  begin
    run_list_features_expect_error(stub)
  rescue GRPC::BadStatus => e
    error = true
    puts "===== ListFeatures exception: ====="
    puts e.inspect
    puts "e.code: #{e.code}"
    puts "e.details: #{e.details}"
    puts "e.metadata: #{e.metadata}"
    puts "================================="
  end

  begin
    run_route_chat_expect_error(stub)
  rescue GRPC::BadStatus => e
    puts "==== RouteChat exception: ===="
    puts e.inspect
    puts "e.code: #{e.code}"
    puts "e.details: #{e.details}"
    puts "e.metadata: #{e.metadata}"
    puts "================================="
  end

  begin
    run_record_route_expect_error(stub)
  rescue GRPC::BadStatus => e
    puts "==== RecordRoute exception: ===="
    puts e.inspect
    puts "e.code: #{e.code}"
    puts "e.details: #{e.details}"
    puts "e.metadata: #{e.metadata}"
    puts "================================="
  end
end

main

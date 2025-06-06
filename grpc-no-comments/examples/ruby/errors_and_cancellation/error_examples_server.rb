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

include GRPC::Core::StatusCodes

class CancellingAndErrorReturningServerImpl < RouteGuide::Service

  def list_features(rectangle, _call)
    raise "string appears on the client in the 'details' field of a 'GRPC::Unknown' exception"
  end

  def record_route(call)
    raise GRPC::BadStatus.new_status_exception(CANCELLED)
  end

  def route_chat(notes)
    raise GRPC::BadStatus.new_status_exception(ABORTED, details = 'arbitrary', metadata = {somekey: 'val'})
  end
end

def main
  port = '0.0.0.0:50051'
  s = GRPC::RpcServer.new
  s.add_http2_port(port, :this_port_is_insecure)
  GRPC.logger.info("... running insecurely on #{port}")
  s.handle(CancellingAndErrorReturningServerImpl.new)
  s.run_till_terminated
end

main

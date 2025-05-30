# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

module GRPC

  module Spec

    module Helpers

      RpcServer = GRPC::RpcServer

      def build_rpc_server(server_opts: {},
                           client_opts: {})
        @server = new_rpc_server_for_testing({ poll_period: 1 }.merge(server_opts))
        @port = @server.add_http2_port('0.0.0.0:0', :this_port_is_insecure)
        @host = "0.0.0.0:#{@port}"
        @client_opts = client_opts
        @server
      end

      def run_services_on_server(server, services: [])
        services.each do |s|
          server.handle(s)
        end
        t = Thread.new { server.run }
        server.wait_till_running

        yield

        server.stop
        t.join
      end

      def build_insecure_stub(klass, host: nil, opts: nil)
        host ||= @host
        opts ||= @client_opts
        klass.new(host, :this_channel_is_insecure, **opts)
      end

      def new_rpc_server_for_testing(server_opts = {})
        server_opts[:server_args] ||= {}
        update_server_args_hash(server_opts[:server_args])
        RpcServer.new(**server_opts)
      end

      def new_core_server_for_testing(server_args)
        server_args.nil? && server_args = {}
        update_server_args_hash(server_args)
        GRPC::Core::Server.new(server_args)
      end

      def update_server_args_hash(server_args)
        so_reuseport_arg = 'grpc.so_reuseport'
        unless server_args[so_reuseport_arg].nil?
          fail 'Unexpected. grpc.so_reuseport already set.'
        end

        server_args[so_reuseport_arg] = 0
      end
    end
  end
end

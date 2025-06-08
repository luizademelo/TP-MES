Here's the commented version of the code:

```c++
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
      # Alias for GRPC::RpcServer for cleaner reference
      RpcServer = GRPC::RpcServer

      # Builds and configures an RPC server for testing purposes
      # @param server_opts [Hash] Options for server configuration
      # @param client_opts [Hash] Options for client configuration
      # @return [GRPC::RpcServer] The configured server instance
      def build_rpc_server(server_opts: {},
                           client_opts: {})
        # Create new server with default poll period of 1 second, merged with provided options
        @server = new_rpc_server_for_testing({ poll_period: 1 }.merge(server_opts))
        # Add insecure HTTP/2 port on all interfaces with random available port
        @port = @server.add_http2_port('0.0.0.0:0', :this_port_is_insecure)
        # Set host address with the allocated port
        @host = "0.0.0.0:#{@port}"
        # Store client options for later use
        @client_opts = client_opts
        @server
      end

      # Runs services on a server in a separate thread and yields to a block
      # @param server [GRPC::RpcServer] The server instance
      # @param services [Array] Array of services to handle
      def run_services_on_server(server, services: [])
        # Register each service with the server
        services.each do |s|
          server.handle(s)
        end
        # Start server in a new thread
        t = Thread.new { server.run }
        # Wait until server is fully running
        server.wait_till_running

        # Yield to allow test code to execute while server is running
        yield

        # Cleanup: stop server and wait for thread to complete
        server.stop
        t.join
      end

      # Creates an insecure client stub for testing
      # @param klass [Class] The stub class to instantiate
      # @param host [String] Host address (defaults to @host if not specified)
      # @param opts [Hash] Client options (defaults to @client_opts if not specified)
      # @return [Object] New instance of the specified stub class
      def build_insecure_stub(klass, host: nil, opts: nil)
        host ||= @host
        opts ||= @client_opts
        klass.new(host, :this_channel_is_insecure, **opts)
      end

      # Creates a new RPC server instance for testing
      # @param server_opts [Hash] Server options
      # @return [GRPC::RpcServer] New server instance
      def new_rpc_server_for_testing(server_opts = {})
        # Initialize server_args if not present
        server_opts[:server_args] ||= {}
        # Update server arguments with required configurations
        update_server_args_hash(server_opts[:server_args])
        RpcServer.new(**server_opts)
      end

      # Creates a new core server instance for testing
      # @param server_args [Hash] Server arguments
      # @return [GRPC::Core::Server] New core server instance
      def new_core_server_for_testing(server_args)
        # Initialize server_args if nil
        server_args.nil? && server_args = {}
        # Update server arguments with required configurations
        update_server_args_hash(server_args)
        GRPC::Core::Server.new(server_args)
      end

      # Updates server arguments with required configurations
      # @param server_args [Hash] Server arguments to be modified
      def update_server_args_hash(server_args)
        so_reuseport_arg = 'grpc.so_reuseport'
        # Validate that the argument isn't already set
        unless server_args[so_reuseport_arg].nil?
          fail 'Unexpected. grpc.so_reuseport already set.'
        end

        # Set SO_REUSEPORT option to 0 (disabled)
        server_args[so_reuseport_arg] = 0
      end
    end
  end
end
```
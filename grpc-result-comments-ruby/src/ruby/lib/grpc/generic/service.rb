Here's the commented version of the code:

```c++
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require_relative 'client_stub'
require_relative 'rpc_desc'

module GRPC
  # Module for defining generic gRPC services
  module GenericService
    # Converts CamelCase strings to snake_case
    # @param s [String] the string to convert
    # @return [String] the converted snake_case string
    def self.underscore(s)
      s = +s
      s.gsub!(/([A-Z]+)([A-Z][a-z])/, '\1_\2')  # Handle consecutive capitals
      s.gsub!(/([a-z\d])([A-Z])/, '\1_\2')     # Handle camelCase transitions
      s.tr!('-', '_')                          # Convert hyphens to underscores
      s.downcase!                              # Convert to lowercase
      s
    end

    # Exception raised when an RPC name is duplicated
    class DuplicateRpcName < StandardError
      def initialize(name)
        super("rpc (#{name}) is already defined")
      end
    end

    # DSL module for defining gRPC services
    module Dsl
      attr_writer(:marshal_class_method, :unmarshal_class_method)
      attr_accessor(:service_name)

      # Defines an RPC method in the service
      # @param name [Symbol] the name of the RPC method
      # @param input [Class] the input message class
      # @param output [Class] the output message class
      # @raise [DuplicateRpcName] if the RPC name is already defined
      def rpc(name, input, output)
        fail(DuplicateRpcName, name) if rpc_descs.key? name
        assert_can_marshal(input)
        assert_can_marshal(output)
        # Store the RPC description
        rpc_descs[name] = RpcDesc.new(name, input, output,
                                      marshal_class_method,
                                      unmarshal_class_method)
        # Define a method that raises unimplemented by default
        define_method(GenericService.underscore(name.to_s).to_sym) do |*|
          fail GRPC::BadStatus.new_status_exception(
            GRPC::Core::StatusCodes::UNIMPLEMENTED)
        end
      end

      # Called when a class inherits from this service
      # @param subclass [Class] the inheriting class
      def inherited(subclass)
        # Copy RPC descriptions and service name to subclass
        subclass.rpc_descs.merge!(rpc_descs)
        subclass.service_name = service_name
      end

      # @return [Symbol] the marshal method name (default: :marshal)
      def marshal_class_method
        @marshal_class_method ||= :marshal
      end

      # @return [Symbol] the unmarshal method name (default: :unmarshal)
      def unmarshal_class_method
        @unmarshal_class_method ||= :unmarshal
      end

      # Verifies that a class can be marshaled/unmarshaled
      # @param cls [Class] the class to check
      # @raise [ArgumentError] if the class doesn't have required methods
      def assert_can_marshal(cls)
        cls = cls.type if cls.is_a? RpcDesc::Stream
        mth = unmarshal_class_method
        unless cls.methods.include? mth
          fail(ArgumentError, "#{cls} needs #{cls}.#{mth}")
        end
        mth = marshal_class_method
        return if cls.methods.include? mth
        fail(ArgumentError, "#{cls} needs #{cls}.#{mth}")
      end

      # Creates a streaming RPC description
      # @param cls [Class] the message class
      # @return [RpcDesc::Stream] stream description
      def stream(cls)
        assert_can_marshal(cls)
        RpcDesc::Stream.new(cls)
      end

      # @return [Hash] the RPC descriptions for this service
      def rpc_descs
        @rpc_descs ||= {}
      end

      # Generates a client stub class for this service
      # @return [Class] dynamically generated client stub class
      def rpc_stub_class
        descs = rpc_descs
        route_prefix = service_name
        Class.new(ClientStub) do
          def initialize(host, creds, **kw)
            super(host, creds, **kw)
          end

          # Dynamically define client methods for each RPC
          descs.each_pair do |name, desc|
            mth_name = GenericService.underscore(name.to_s).to_sym
            marshal = desc.marshal_proc
            unmarshal = desc.unmarshal_proc(:output)
            route = "/#{route_prefix}/#{name}"
            
            if desc.request_response?
              define_method(mth_name) do |req, metadata = {}|
                GRPC.logger.debug("calling #{@host}:#{route}")
                request_response(route, req, marshal, unmarshal, **metadata)
              end
            elsif desc.client_streamer?
              define_method(mth_name) do |reqs, metadata = {}|
                GRPC.logger.debug("calling #{@host}:#{route}")
                client_streamer(route, reqs, marshal, unmarshal, **metadata)
              end
            elsif desc.server_streamer?
              define_method(mth_name) do |req, metadata = {}, &blk|
                GRPC.logger.debug("calling #{@host}:#{route}")
                server_streamer(route, req, marshal, unmarshal, **metadata, &blk)
              end
            else
              define_method(mth_name) do |reqs, metadata = {}, &blk|
                GRPC.logger.debug("calling #{@host}:#{route}")
                bidi_streamer(route, reqs, marshal, unmarshal, **metadata, &blk)
              end
            end
          end
        end
      end
    end

    # Called when this module is included in a class
    # @param o [Class] the including class
    def self.included(o)
      o.extend(Dsl)

      return unless o.service_name.nil?
      # Set default service name based on class name
      if o.name.nil?
        o.service_name = 'GenericService'
      else
        modules = o.name.split('::')
        if modules.length > 2
          o.service_name = modules[modules.length - 2]
        else
          o.service_name = modules.first
        end
      end
    end
  end
end
```
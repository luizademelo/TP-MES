Here's the commented version of the code:

```python
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.discovery.v3 import discovery_pb2 as envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2

class EndpointDiscoveryServiceStub(object):
    """[#protodoc-title: EDS]
    Endpoint discovery :ref:`architecture overview <arch_overview_service_discovery_types_eds>`
    
    This class provides a client-side stub for interacting with the Endpoint Discovery Service (EDS).
    It allows clients to make RPC calls to the EDS server.
    """

    def __init__(self, channel):
        """Constructor.

        Initializes the stub with gRPC channel and sets up the RPC methods.

        Args:
            channel: A grpc.Channel. The channel to use for making RPC calls.
        """
        # Bidirectional streaming RPC for continuous endpoint discovery updates
        self.StreamEndpoints = channel.stream_stream(
                '/envoy.service.endpoint.v3.EndpointDiscoveryService/StreamEndpoints',
                request_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
                )
        
        # Bidirectional streaming RPC for delta-based endpoint discovery updates
        self.DeltaEndpoints = channel.stream_stream(
                '/envoy.service.endpoint.v3.EndpointDiscoveryService/DeltaEndpoints',
                request_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
                )
        
        # Unary RPC for fetching endpoints (single request/response)
        self.FetchEndpoints = channel.unary_unary(
                '/envoy.service.endpoint.v3.EndpointDiscoveryService/FetchEndpoints',
                request_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
                )

class EndpointDiscoveryServiceServicer(object):
    """[#protodoc-title: EDS]
    Endpoint discovery :ref:`architecture overview <arch_overview_service_discovery_types_eds>`
    
    This class provides the server-side implementation of the Endpoint Discovery Service.
    Concrete implementations should inherit from this class and implement the methods.
    """

    def StreamEndpoints(self, request_iterator, context):
        """The resource_names field in DiscoveryRequest specifies a list of clusters
        to subscribe to updates for.
        
        Args:
            request_iterator: An iterator of DiscoveryRequest messages.
            context: gRPC server context.
        
        Returns:
            An iterator of DiscoveryResponse messages (implemented by concrete class).
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def DeltaEndpoints(self, request_iterator, context):
        """Delta endpoint discovery method.
        
        Args:
            request_iterator: An iterator of DeltaDiscoveryRequest messages.
            context: gRPC server context.
        
        Returns:
            An iterator of DeltaDiscoveryResponse messages (implemented by concrete class).
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def FetchEndpoints(self, request, context):
        """Fetch endpoints method (unary RPC).
        
        Args:
            request: A single DiscoveryRequest message.
            context: gRPC server context.
        
        Returns:
            A DiscoveryResponse message (implemented by concrete class).
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_EndpointDiscoveryServiceServicer_to_server(servicer, server):
    """Registers the EndpointDiscoveryService implementation with a gRPC server.
    
    Args:
        servicer: An implementation of EndpointDiscoveryServiceServicer.
        server: The gRPC server to register the servicer with.
    """
    rpc_method_handlers = {
            'StreamEndpoints': grpc.stream_stream_rpc_method_handler(
                    servicer.StreamEndpoints,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.SerializeToString,
            ),
            'DeltaEndpoints': grpc.stream_stream_rpc_method_handler(
                    servicer.DeltaEndpoints,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.SerializeToString,
            ),
            'FetchEndpoints': grpc.unary_unary_rpc_method_handler(
                    servicer.FetchEndpoints,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.endpoint.v3.EndpointDiscoveryService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class EndpointDiscoveryService(object):
    """[#protodoc-title: EDS]
    Endpoint discovery :ref:`architecture overview <arch_overview_service_discovery_types_eds>`
    
    This class provides static methods for making client-side RPC calls without
    requiring a stub instance.
    """

    @staticmethod
    def StreamEndpoints(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Static method for making a StreamEndpoints RPC call.
        
        Args:
            request_iterator: An iterator of DiscoveryRequest messages.
            target: The server address.
            options: (Optional) gRPC options.
            channel_credentials: (Optional) Channel credentials.
            call_credentials: (Optional) Call credentials.
            insecure: (Optional) Boolean indicating if connection should be insecure.
            compression: (Optional) Compression algorithm.
            wait_for_ready: (Optional) Boolean indicating if should wait for ready.
            timeout: (Optional) Timeout in seconds.
            metadata: (Optional) Additional metadata.
        
        Returns:
            An iterator of DiscoveryResponse messages.
        """
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.endpoint.v3.EndpointDiscoveryService/StreamEndpoints',
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def DeltaEndpoints(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Static method for making a DeltaEndpoints RPC call.
        
        Args and Returns similar to StreamEndpoints, but for delta updates.
        """
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.endpoint.v3.EndpointDiscoveryService/DeltaEndpoints',
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def FetchEndpoints(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Static method for making a FetchEndpoints RPC call (unary).
        
        Args:
            request: A single DiscoveryRequest message.
            Other args similar to StreamEndpoints.
        
        Returns:
            A single DiscoveryResponse message.
        """
        return grpc.experimental.unary_unary(request, target, '/envoy.service.endpoint.v3.EndpointDiscoveryService/FetchEndpoints',
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)
```
Here's the commented version of the code:

```python
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.api.v2 import discovery_pb2 as envoy_dot_api_dot_v2_dot_discovery__pb2

class RuntimeDiscoveryServiceStub(object):
    """[#protodoc-title: Runtime Discovery Service (RTDS)]
    RTDS :ref:`configuration overview <config_runtime_rtds>`

    Discovery service for Runtime resources.
    """

    def __init__(self, channel):
        """Constructor.

        Initializes the RPC methods for the Runtime Discovery Service client.

        Args:
            channel: A grpc.Channel used for communication with the server.
        """
        # Bidirectional streaming RPC for runtime discovery
        self.StreamRuntime = channel.stream_stream(
                '/envoy.service.discovery.v2.RuntimeDiscoveryService/StreamRuntime',
                request_serializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryResponse.FromString,
                )
        # Bidirectional streaming RPC for delta runtime discovery
        self.DeltaRuntime = channel.stream_stream(
                '/envoy.service.discovery.v2.RuntimeDiscoveryService/DeltaRuntime',
                request_serializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
                )
        # Unary RPC for fetching runtime configuration
        self.FetchRuntime = channel.unary_unary(
                '/envoy.service.discovery.v2.RuntimeDiscoveryService/FetchRuntime',
                request_serializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryResponse.FromString,
                )

class RuntimeDiscoveryServiceServicer(object):
    """[#protodoc-title: Runtime Discovery Service (RTDS)]
    RTDS :ref:`configuration overview <config_runtime_rtds>`

    Discovery service for Runtime resources.
    """

    def StreamRuntime(self, request_iterator, context):
        """Handles streaming runtime discovery requests.
        
        Args:
            request_iterator: An iterator of DiscoveryRequest messages.
            context: gRPC server context.
        
        Raises:
            NotImplementedError: Indicates the method is not implemented.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def DeltaRuntime(self, request_iterator, context):
        """Handles delta runtime discovery requests.
        
        Args:
            request_iterator: An iterator of DeltaDiscoveryRequest messages.
            context: gRPC server context.
        
        Raises:
            NotImplementedError: Indicates the method is not implemented.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def FetchRuntime(self, request, context):
        """Handles unary runtime fetch requests.
        
        Args:
            request: A DiscoveryRequest message.
            context: gRPC server context.
        
        Raises:
            NotImplementedError: Indicates the method is not implemented.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_RuntimeDiscoveryServiceServicer_to_server(servicer, server):
    """Registers RuntimeDiscoveryService servicer with the gRPC server.
    
    Args:
        servicer: An implementation of RuntimeDiscoveryServiceServicer.
        server: The gRPC server to which the servicer will be added.
    """
    rpc_method_handlers = {
            # Handler for StreamRuntime RPC method
            'StreamRuntime': grpc.stream_stream_rpc_method_handler(
                    servicer.StreamRuntime,
                    request_deserializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryRequest.FromString,
                    response_serializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryResponse.SerializeToString,
            ),
            # Handler for DeltaRuntime RPC method
            'DeltaRuntime': grpc.stream_stream_rpc_method_handler(
                    servicer.DeltaRuntime,
                    request_deserializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryRequest.FromString,
                    response_serializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryResponse.SerializeToString,
            ),
            # Handler for FetchRuntime RPC method
            'FetchRuntime': grpc.unary_unary_rpc_method_handler(
                    servicer.FetchRuntime,
                    request_deserializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryRequest.FromString,
                    response_serializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.discovery.v2.RuntimeDiscoveryService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class RuntimeDiscoveryService(object):
    """[#protodoc-title: Runtime Discovery Service (RTDS)]
    RTDS :ref:`configuration overview <config_runtime_rtds>`

    Discovery service for Runtime resources.
    """

    @staticmethod
    def StreamRuntime(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Creates a client for the StreamRuntime RPC method.
        
        Args:
            request_iterator: An iterator of DiscoveryRequest messages.
            target: The server address.
            options: Optional gRPC options.
            channel_credentials: Optional credentials for secure channel.
            call_credentials: Optional call credentials.
            insecure: If True, creates an insecure channel.
            compression: Optional compression method.
            wait_for_ready: If True, waits for server to be ready.
            timeout: Optional timeout in seconds.
            metadata: Optional metadata to send to server.
        
        Returns:
            A streaming call object for the StreamRuntime RPC.
        """
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.discovery.v2.RuntimeDiscoveryService/StreamRuntime',
            envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
            envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def DeltaRuntime(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Creates a client for the DeltaRuntime RPC method.
        
        Args:
            request_iterator: An iterator of DeltaDiscoveryRequest messages.
            target: The server address.
            options: Optional gRPC options.
            channel_credentials: Optional credentials for secure channel.
            call_credentials: Optional call credentials.
            insecure: If True, creates an insecure channel.
            compression: Optional compression method.
            wait_for_ready: If True, waits for server to be ready.
            timeout: Optional timeout in seconds.
            metadata: Optional metadata to send to server.
        
        Returns:
            A streaming call object for the DeltaRuntime RPC.
        """
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.discovery.v2.RuntimeDiscoveryService/DeltaRuntime',
            envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
            envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def FetchRuntime(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Creates a client for the FetchRuntime RPC method.
        
        Args:
            request: A DiscoveryRequest message.
            target: The server address.
            options: Optional gRPC options.
            channel_credentials: Optional credentials for secure channel.
            call_credentials: Optional call credentials.
            insecure: If True, creates an insecure channel.
            compression: Optional compression method.
            wait_for_ready: If True, waits for server to be ready.
            timeout: Optional timeout in seconds.
            metadata: Optional metadata to send to server.
        
        Returns:
            A unary call object for the FetchRuntime RPC.
        """
        return grpc.experimental.unary_unary(request, target, '/envoy.service.discovery.v2.RuntimeDiscoveryService/FetchRuntime',
            envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
            envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)
```
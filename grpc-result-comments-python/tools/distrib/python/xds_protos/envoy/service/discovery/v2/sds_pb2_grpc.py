Here's the commented version of the code:

```python
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.api.v2 import discovery_pb2 as envoy_dot_api_dot_v2_dot_discovery__pb2

class SecretDiscoveryServiceStub(object):
    """[#protodoc-title: Secret Discovery Service (SDS)]
    Client-side stub for the Secret Discovery Service (SDS).
    Provides methods for interacting with the SDS server.
    """

    def __init__(self, channel):
        """Constructor.
        Initializes the SDS client stub with gRPC channel.

        Args:
            channel: A grpc.Channel. The gRPC channel used for communication with the server.
        """
        # Bidirectional streaming RPC for delta secrets discovery
        self.DeltaSecrets = channel.stream_stream(
                '/envoy.service.discovery.v2.SecretDiscoveryService/DeltaSecrets',
                request_serializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
                )
        # Bidirectional streaming RPC for streaming secrets
        self.StreamSecrets = channel.stream_stream(
                '/envoy.service.discovery.v2.SecretDiscoveryService/StreamSecrets',
                request_serializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryResponse.FromString,
                )
        # Unary RPC for fetching secrets
        self.FetchSecrets = channel.unary_unary(
                '/envoy.service.discovery.v2.SecretDiscoveryService/FetchSecrets',
                request_serializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryResponse.FromString,
                )

class SecretDiscoveryServiceServicer(object):
    """[#protodoc-title: Secret Discovery Service (SDS)]
    Server-side implementation of the Secret Discovery Service.
    This class should be implemented to provide actual functionality.
    """

    def DeltaSecrets(self, request_iterator, context):
        """Handles delta secrets discovery requests.
        This is a bidirectional streaming RPC that should be implemented to handle
        incremental updates of secrets.
        
        Args:
            request_iterator: Iterator yielding DeltaDiscoveryRequest messages.
            context: grpc.ServicerContext for RPC metadata and control.
        
        Raises:
            NotImplementedError: Indicates the method is not implemented.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def StreamSecrets(self, request_iterator, context):
        """Handles streaming secrets requests.
        This is a bidirectional streaming RPC that should be implemented to handle
        streaming of secrets.
        
        Args:
            request_iterator: Iterator yielding DiscoveryRequest messages.
            context: grpc.ServicerContext for RPC metadata and control.
        
        Raises:
            NotImplementedError: Indicates the method is not implemented.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def FetchSecrets(self, request, context):
        """Handles fetch secrets requests.
        This is a unary RPC that should be implemented to handle
        one-time secrets fetching.
        
        Args:
            request: DiscoveryRequest message.
            context: grpc.ServicerContext for RPC metadata and control.
        
        Raises:
            NotImplementedError: Indicates the method is not implemented.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_SecretDiscoveryServiceServicer_to_server(servicer, server):
    """Registers the SDS servicer with a gRPC server.
    
    Args:
        servicer: An implementation of SecretDiscoveryServiceServicer.
        server: The gRPC server to which the servicer will be added.
    """
    rpc_method_handlers = {
            'DeltaSecrets': grpc.stream_stream_rpc_method_handler(
                    servicer.DeltaSecrets,
                    request_deserializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryRequest.FromString,
                    response_serializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryResponse.SerializeToString,
            ),
            'StreamSecrets': grpc.stream_stream_rpc_method_handler(
                    servicer.StreamSecrets,
                    request_deserializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryRequest.FromString,
                    response_serializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryResponse.SerializeToString,
            ),
            'FetchSecrets': grpc.unary_unary_rpc_method_handler(
                    servicer.FetchSecrets,
                    request_deserializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryRequest.FromString,
                    response_serializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.discovery.v2.SecretDiscoveryService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class SecretDiscoveryService(object):
    """[#protodoc-title: Secret Discovery Service (SDS)]
    Provides static methods for building clients to interact with the SDS server.
    """

    @staticmethod
    def DeltaSecrets(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Creates a client for the DeltaSecrets bidirectional streaming RPC.
        
        Args:
            request_iterator: Iterator yielding DeltaDiscoveryRequest messages.
            target: The server address.
            options: Optional gRPC options.
            channel_credentials: Optional credentials for the channel.
            call_credentials: Optional call credentials.
            insecure: If True, uses insecure channel.
            compression: Optional compression method.
            wait_for_ready: If True, waits for server to be ready.
            timeout: Optional timeout in seconds.
            metadata: Optional metadata to send with the request.
        
        Returns:
            A stream of DeltaDiscoveryResponse messages.
        """
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.discovery.v2.SecretDiscoveryService/DeltaSecrets',
            envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
            envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def StreamSecrets(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Creates a client for the StreamSecrets bidirectional streaming RPC.
        
        Args:
            request_iterator: Iterator yielding DiscoveryRequest messages.
            target: The server address.
            options: Optional gRPC options.
            channel_credentials: Optional credentials for the channel.
            call_credentials: Optional call credentials.
            insecure: If True, uses insecure channel.
            compression: Optional compression method.
            wait_for_ready: If True, waits for server to be ready.
            timeout: Optional timeout in seconds.
            metadata: Optional metadata to send with the request.
        
        Returns:
            A stream of DiscoveryResponse messages.
        """
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.discovery.v2.SecretDiscoveryService/StreamSecrets',
            envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
            envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def FetchSecrets(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Creates a client for the FetchSecrets unary RPC.
        
        Args:
            request: A DiscoveryRequest message.
            target: The server address.
            options: Optional gRPC options.
            channel_credentials: Optional credentials for the channel.
            call_credentials: Optional call credentials.
            insecure: If True, uses insecure channel.
            compression: Optional compression method.
            wait_for_ready: If True, waits for server to be ready.
            timeout: Optional timeout in seconds.
            metadata: Optional metadata to send with the request.
        
        Returns:
            A DiscoveryResponse message.
        """
        return grpc.experimental.unary_unary(request, target, '/envoy.service.discovery.v2.SecretDiscoveryService/FetchSecrets',
            envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
            envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)
```
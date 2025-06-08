Here's the commented version of the code:

```python
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.api.v2 import discovery_pb2 as envoy_dot_api_dot_v2_dot_discovery__pb2

class AggregatedDiscoveryServiceStub(object):
    """[#protodoc-title: Aggregated Discovery Service (ADS)]

    Discovery services for endpoints, clusters, routes,
    and listeners are retained in the package `envoy.api.v2` for backwards
    compatibility with existing management servers. New development in discovery
    services should proceed in the package `envoy.service.discovery.v2`.

    See https://github.com/envoyproxy/envoy-api#apis for a description of the role of
    ADS and how it is intended to be used by a management server. ADS requests
    have the same structure as their singleton xDS counterparts, but can
    multiplex many resource types on a single stream. The type_url in the
    DiscoveryRequest/DiscoveryResponse provides sufficient information to recover
    the multiplexed singleton APIs at the Envoy instance and management server.
    """

    def __init__(self, channel):
        """Constructor.

        Initializes the gRPC stub for Aggregated Discovery Service (ADS).

        Args:
            channel: A grpc.Channel for communication with the gRPC server.
        """
        # Setup bi-directional streaming RPC for aggregated resources
        self.StreamAggregatedResources = channel.stream_stream(
                '/envoy.service.discovery.v2.AggregatedDiscoveryService/StreamAggregatedResources',
                request_serializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryResponse.FromString,
                )
        # Setup bi-directional streaming RPC for delta aggregated resources
        self.DeltaAggregatedResources = channel.stream_stream(
                '/envoy.service.discovery.v2.AggregatedDiscoveryService/DeltaAggregatedResources',
                request_serializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
                )

class AggregatedDiscoveryServiceServicer(object):
    """[#protodoc-title: Aggregated Discovery Service (ADS)]

    Discovery services for endpoints, clusters, routes,
    and listeners are retained in the package `envoy.api.v2` for backwards
    compatibility with existing management servers. New development in discovery
    services should proceed in the package `envoy.service.discovery.v2`.

    See https://github.com/envoyproxy/envoy-api#apis for a description of the role of
    ADS and how it is intended to be used by a management server. ADS requests
    have the same structure as their singleton xDS counterparts, but can
    multiplex many resource types on a single stream. The type_url in the
    DiscoveryRequest/DiscoveryResponse provides sufficient information to recover
    the multiplexed singleton APIs at the Envoy instance and management server.
    """

    def StreamAggregatedResources(self, request_iterator, context):
        """StreamAggregatedResources service method.

        This is a gRPC-only API for streaming aggregated resources.
        Must be implemented by concrete servicers.

        Args:
            request_iterator: Iterator of DiscoveryRequest messages.
            context: gRPC server context.

        Raises:
            NotImplementedError: Indicates the method is not implemented.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def DeltaAggregatedResources(self, request_iterator, context):
        """DeltaAggregatedResources service method.

        This is a gRPC-only API for streaming delta updates of aggregated resources.
        Must be implemented by concrete servicers.

        Args:
            request_iterator: Iterator of DeltaDiscoveryRequest messages.
            context: gRPC server context.

        Raises:
            NotImplementedError: Indicates the method is not implemented.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_AggregatedDiscoveryServiceServicer_to_server(servicer, server):
    """Registers the ADS servicer with the gRPC server.

    Args:
        servicer: An implementation of AggregatedDiscoveryServiceServicer.
        server: The gRPC server to which the servicer will be added.
    """
    # Define RPC method handlers for both streaming methods
    rpc_method_handlers = {
            'StreamAggregatedResources': grpc.stream_stream_rpc_method_handler(
                    servicer.StreamAggregatedResources,
                    request_deserializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryRequest.FromString,
                    response_serializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryResponse.SerializeToString,
            ),
            'DeltaAggregatedResources': grpc.stream_stream_rpc_method_handler(
                    servicer.DeltaAggregatedResources,
                    request_deserializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryRequest.FromString,
                    response_serializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryResponse.SerializeToString,
            ),
    }
    # Create and register generic handler for the ADS service
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.discovery.v2.AggregatedDiscoveryService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class AggregatedDiscoveryService(object):
    """[#protodoc-title: Aggregated Discovery Service (ADS)]

    Discovery services for endpoints, clusters, routes,
    and listeners are retained in the package `envoy.api.v2` for backwards
    compatibility with existing management servers. New development in discovery
    services should proceed in the package `envoy.service.discovery.v2`.

    See https://github.com/envoyproxy/envoy-api#apis for a description of the role of
    ADS and how it is intended to be used by a management server. ADS requests
    have the same structure as their singleton xDS counterparts, but can
    multiplex many resource types on a single stream. The type_url in the
    DiscoveryRequest/DiscoveryResponse provides sufficient information to recover
    the multiplexed singleton APIs at the Envoy instance and management server.
    """

    @staticmethod
    def StreamAggregatedResources(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Client-side method for streaming aggregated resources.

        Args:
            request_iterator: Iterator of DiscoveryRequest messages.
            target: The server address.
            options: Optional gRPC options.
            channel_credentials: Optional channel credentials.
            call_credentials: Optional call credentials.
            insecure: If True, use insecure channel.
            compression: Optional compression method.
            wait_for_ready: If True, waits for server to be ready.
            timeout: Optional timeout in seconds.
            metadata: Optional metadata to send with the request.

        Returns:
            A streaming call object for aggregated resources.
        """
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.discovery.v2.AggregatedDiscoveryService/StreamAggregatedResources',
            envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
            envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def DeltaAggregatedResources(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Client-side method for streaming delta aggregated resources.

        Args:
            request_iterator: Iterator of DeltaDiscoveryRequest messages.
            target: The server address.
            options: Optional gRPC options.
            channel_credentials: Optional channel credentials.
            call_credentials: Optional call credentials.
            insecure: If True, use insecure channel.
            compression: Optional compression method.
            wait_for_ready: If True, waits for server to be ready.
            timeout: Optional timeout in seconds.
            metadata: Optional metadata to send with the request.

        Returns:
            A streaming call object for delta aggregated resources.
        """
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.discovery.v2.AggregatedDiscoveryService/DeltaAggregatedResources',
            envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
            envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)
```

Key improvements made:
1. Added detailed docstrings for all methods explaining their purpose and parameters
2. Added comments explaining the RPC setup in the Stub class
3. Enhanced the NotImplemented methods to explain their expected behavior
4. Added clear documentation for the server registration function
5. Added comprehensive parameter documentation for client-side streaming methods
6. Maintained all existing documentation while adding new explanatory comments
7. Added return value documentation where applicable

The comments now provide a complete picture of the service's functionality, making it easier for developers to understand and work with the code.
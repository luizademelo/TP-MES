Here's the commented version of the code:

```python
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.discovery.v2 import hds_pb2 as envoy_dot_service_dot_discovery_dot_v2_dot_hds__pb2

class HealthDiscoveryServiceStub(object):
    """[#protodoc-title: Health Discovery Service (HDS)]

    HDS is Health Discovery Service. It compliments Envoy's health checking
    service by designating this Envoy to be a healthchecker for a subset of hosts
    in the cluster. The status of these health checks will be reported to the
    management server, where it can be aggregated etc and redistributed back to
    Envoy through EDS.
    """

    def __init__(self, channel):
        """Constructor.

        Initializes the gRPC stub for Health Discovery Service with two RPC methods:
        - StreamHealthCheck: A bidirectional streaming RPC
        - FetchHealthCheck: A unary-unary RPC

        Args:
            channel: A grpc.Channel for communication with the gRPC server.
        """
        self.StreamHealthCheck = channel.stream_stream(
                '/envoy.service.discovery.v2.HealthDiscoveryService/StreamHealthCheck',
                request_serializer=envoy_dot_service_dot_discovery_dot_v2_dot_hds__pb2.HealthCheckRequestOrEndpointHealthResponse.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v2_dot_hds__pb2.HealthCheckSpecifier.FromString,
                )
        self.FetchHealthCheck = channel.unary_unary(
                '/envoy.service.discovery.v2.HealthDiscoveryService/FetchHealthCheck',
                request_serializer=envoy_dot_service_dot_discovery_dot_v2_dot_hds__pb2.HealthCheckRequestOrEndpointHealthResponse.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v2_dot_hds__pb2.HealthCheckSpecifier.FromString,
                )

class HealthDiscoveryServiceServicer(object):
    """[#protodoc-title: Health Discovery Service (HDS)]

    HDS is Health Discovery Service. It compliments Envoy's health checking
    service by designating this Envoy to be a healthchecker for a subset of hosts
    in the cluster. The status of these health checks will be reported to the
    management server, where it can be aggregated etc and redistributed back to
    Envoy through EDS.
    """

    def StreamHealthCheck(self, request_iterator, context):
        """Handles the StreamHealthCheck RPC call.

        This method implements the health checking workflow between Envoy and the management server:
        1. Envoy starts up and if its can_healthcheck option is enabled, sends HealthCheckRequest
        2. Management server designates this Envoy as healthchecker for specific hosts
        3. Envoy creates health probes based on configuration
        4. Envoy reports results back via EndpointHealthResponse
        5. Management server collects health statuses for all endpoints
        6. Envoy uses this information for load balancing

        Args:
            request_iterator: An iterator of HealthCheckRequestOrEndpointHealthResponse messages.
            context: gRPC server context.

        Returns:
            HealthCheckSpecifier messages from the management server.

        Note:
            Currently unimplemented - raises NotImplementedError.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def FetchHealthCheck(self, request, context):
        """Handles the FetchHealthCheck RPC call.

        This is a unary RPC alternative to StreamHealthCheck, without streaming capabilities.

        Args:
            request: A HealthCheckRequestOrEndpointHealthResponse message.
            context: gRPC server context.

        Returns:
            A HealthCheckSpecifier message from the management server.

        Note:
            Currently unimplemented - raises NotImplementedError.
        TODO: Consider adding identifier binding between request and response.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_HealthDiscoveryServiceServicer_to_server(servicer, server):
    """Registers the HealthDiscoveryService servicer with a gRPC server.

    Args:
        servicer: An instance of HealthDiscoveryServiceServicer implementing the RPC methods.
        server: The gRPC server to which the servicer will be added.
    """
    rpc_method_handlers = {
            'StreamHealthCheck': grpc.stream_stream_rpc_method_handler(
                    servicer.StreamHealthCheck,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v2_dot_hds__pb2.HealthCheckRequestOrEndpointHealthResponse.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v2_dot_hds__pb2.HealthCheckSpecifier.SerializeToString,
            ),
            'FetchHealthCheck': grpc.unary_unary_rpc_method_handler(
                    servicer.FetchHealthCheck,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v2_dot_hds__pb2.HealthCheckRequestOrEndpointHealthResponse.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v2_dot_hds__pb2.HealthCheckSpecifier.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.discovery.v2.HealthDiscoveryService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class HealthDiscoveryService(object):
    """[#protodoc-title: Health Discovery Service (HDS)]

    HDS is Health Discovery Service. It compliments Envoy's health checking
    service by designating this Envoy to be a healthchecker for a subset of hosts
    in the cluster. The status of these health checks will be reported to the
    management server, where it can be aggregated etc and redistributed back to
    Envoy through EDS.
    """

    @staticmethod
    def StreamHealthCheck(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Client-side method to initiate StreamHealthCheck RPC.

        Args:
            request_iterator: Iterator yielding HealthCheckRequestOrEndpointHealthResponse messages.
            target: The server address.
            options: Optional gRPC options.
            channel_credentials: Optional credentials for secure channel.
            call_credentials: Optional call credentials.
            insecure: If True, uses insecure channel.
            compression: Optional compression algorithm.
            wait_for_ready: If True, waits for server to be ready.
            timeout: Optional timeout in seconds.
            metadata: Optional metadata to send to server.

        Returns:
            A stream of HealthCheckSpecifier messages from the server.
        """
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.discovery.v2.HealthDiscoveryService/StreamHealthCheck',
            envoy_dot_service_dot_discovery_dot_v2_dot_hds__pb2.HealthCheckRequestOrEndpointHealthResponse.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v2_dot_hds__pb2.HealthCheckSpecifier.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def FetchHealthCheck(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Client-side method to initiate FetchHealthCheck RPC.

        Args:
            request: A HealthCheckRequestOrEndpointHealthResponse message.
            target: The server address.
            options: Optional gRPC options.
            channel_credentials: Optional credentials for secure channel.
            call_credentials: Optional call credentials.
            insecure: If True, uses insecure channel.
            compression: Optional compression algorithm.
            wait_for_ready: If True, waits for server to be ready.
            timeout: Optional timeout in seconds.
            metadata: Optional metadata to send to server.

        Returns:
            A HealthCheckSpecifier message from the server.
        """
        return grpc.experimental.unary_unary(request, target, '/envoy.service.discovery.v2.HealthDiscoveryService/FetchHealthCheck',
            envoy_dot_service_dot_discovery_dot_v2_dot_hds__pb2.HealthCheckRequestOrEndpointHealthResponse.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v2_dot_hds__pb2.HealthCheckSpecifier.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)
```
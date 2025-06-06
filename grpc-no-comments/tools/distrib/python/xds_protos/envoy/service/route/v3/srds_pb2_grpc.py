
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.discovery.v3 import discovery_pb2 as envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2

class ScopedRoutesDiscoveryServiceStub(object):
    """[#protodoc-title: SRDS]
    * Routing :ref:`architecture overview <arch_overview_http_routing>`

    The Scoped Routes Discovery Service (SRDS) API distributes
    :ref:`ScopedRouteConfiguration<envoy_v3_api_msg.ScopedRouteConfiguration>`
    resources. Each ScopedRouteConfiguration resource represents a "routing
    scope" containing a mapping that allows the HTTP connection manager to
    dynamically assign a routing table (specified via a
    :ref:`RouteConfiguration<envoy_v3_api_msg_config.route.v3.RouteConfiguration>` message) to each
    HTTP request.
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.StreamScopedRoutes = channel.stream_stream(
                '/envoy.service.route.v3.ScopedRoutesDiscoveryService/StreamScopedRoutes',
                request_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
                )
        self.DeltaScopedRoutes = channel.stream_stream(
                '/envoy.service.route.v3.ScopedRoutesDiscoveryService/DeltaScopedRoutes',
                request_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
                )
        self.FetchScopedRoutes = channel.unary_unary(
                '/envoy.service.route.v3.ScopedRoutesDiscoveryService/FetchScopedRoutes',
                request_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
                )

class ScopedRoutesDiscoveryServiceServicer(object):
    """[#protodoc-title: SRDS]
    * Routing :ref:`architecture overview <arch_overview_http_routing>`

    The Scoped Routes Discovery Service (SRDS) API distributes
    :ref:`ScopedRouteConfiguration<envoy_v3_api_msg.ScopedRouteConfiguration>`
    resources. Each ScopedRouteConfiguration resource represents a "routing
    scope" containing a mapping that allows the HTTP connection manager to
    dynamically assign a routing table (specified via a
    :ref:`RouteConfiguration<envoy_v3_api_msg_config.route.v3.RouteConfiguration>` message) to each
    HTTP request.
    """

    def StreamScopedRoutes(self, request_iterator, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def DeltaScopedRoutes(self, request_iterator, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def FetchScopedRoutes(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_ScopedRoutesDiscoveryServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'StreamScopedRoutes': grpc.stream_stream_rpc_method_handler(
                    servicer.StreamScopedRoutes,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.SerializeToString,
            ),
            'DeltaScopedRoutes': grpc.stream_stream_rpc_method_handler(
                    servicer.DeltaScopedRoutes,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.SerializeToString,
            ),
            'FetchScopedRoutes': grpc.unary_unary_rpc_method_handler(
                    servicer.FetchScopedRoutes,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.route.v3.ScopedRoutesDiscoveryService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class ScopedRoutesDiscoveryService(object):
    """[#protodoc-title: SRDS]
    * Routing :ref:`architecture overview <arch_overview_http_routing>`

    The Scoped Routes Discovery Service (SRDS) API distributes
    :ref:`ScopedRouteConfiguration<envoy_v3_api_msg.ScopedRouteConfiguration>`
    resources. Each ScopedRouteConfiguration resource represents a "routing
    scope" containing a mapping that allows the HTTP connection manager to
    dynamically assign a routing table (specified via a
    :ref:`RouteConfiguration<envoy_v3_api_msg_config.route.v3.RouteConfiguration>` message) to each
    HTTP request.
    """

    @staticmethod
    def StreamScopedRoutes(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.route.v3.ScopedRoutesDiscoveryService/StreamScopedRoutes',
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def DeltaScopedRoutes(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.route.v3.ScopedRoutesDiscoveryService/DeltaScopedRoutes',
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def FetchScopedRoutes(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/envoy.service.route.v3.ScopedRoutesDiscoveryService/FetchScopedRoutes',
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

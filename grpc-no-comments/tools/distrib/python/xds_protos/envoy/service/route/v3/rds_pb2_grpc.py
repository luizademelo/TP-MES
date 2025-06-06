
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.discovery.v3 import discovery_pb2 as envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2

class RouteDiscoveryServiceStub(object):
    """[#protodoc-title: RDS]

    The resource_names field in DiscoveryRequest specifies a route configuration.
    This allows an Envoy configuration with multiple HTTP listeners (and
    associated HTTP connection manager filters) to use different route
    configurations. Each listener will bind its HTTP connection manager filter to
    a route table via this identifier.
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.StreamRoutes = channel.stream_stream(
                '/envoy.service.route.v3.RouteDiscoveryService/StreamRoutes',
                request_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
                )
        self.DeltaRoutes = channel.stream_stream(
                '/envoy.service.route.v3.RouteDiscoveryService/DeltaRoutes',
                request_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
                )
        self.FetchRoutes = channel.unary_unary(
                '/envoy.service.route.v3.RouteDiscoveryService/FetchRoutes',
                request_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
                )

class RouteDiscoveryServiceServicer(object):
    """[#protodoc-title: RDS]

    The resource_names field in DiscoveryRequest specifies a route configuration.
    This allows an Envoy configuration with multiple HTTP listeners (and
    associated HTTP connection manager filters) to use different route
    configurations. Each listener will bind its HTTP connection manager filter to
    a route table via this identifier.
    """

    def StreamRoutes(self, request_iterator, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def DeltaRoutes(self, request_iterator, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def FetchRoutes(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_RouteDiscoveryServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'StreamRoutes': grpc.stream_stream_rpc_method_handler(
                    servicer.StreamRoutes,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.SerializeToString,
            ),
            'DeltaRoutes': grpc.stream_stream_rpc_method_handler(
                    servicer.DeltaRoutes,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.SerializeToString,
            ),
            'FetchRoutes': grpc.unary_unary_rpc_method_handler(
                    servicer.FetchRoutes,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.route.v3.RouteDiscoveryService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class RouteDiscoveryService(object):
    """[#protodoc-title: RDS]

    The resource_names field in DiscoveryRequest specifies a route configuration.
    This allows an Envoy configuration with multiple HTTP listeners (and
    associated HTTP connection manager filters) to use different route
    configurations. Each listener will bind its HTTP connection manager filter to
    a route table via this identifier.
    """

    @staticmethod
    def StreamRoutes(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.route.v3.RouteDiscoveryService/StreamRoutes',
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def DeltaRoutes(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.route.v3.RouteDiscoveryService/DeltaRoutes',
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def FetchRoutes(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/envoy.service.route.v3.RouteDiscoveryService/FetchRoutes',
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

class VirtualHostDiscoveryServiceStub(object):
    """Virtual Host Discovery Service (VHDS) is used to dynamically update the list of virtual hosts for
    a given RouteConfiguration. If VHDS is configured a virtual host list update will be triggered
    during the processing of an HTTP request if a route for the request cannot be resolved. The
    :ref:`resource_names_subscribe <envoy_v3_api_field_service.discovery.v3.DeltaDiscoveryRequest.resource_names_subscribe>`
    field contains a list of virtual host names or aliases to track. The contents of an alias would
    be the contents of a ``host`` or ``authority`` header used to make an http request. An xDS server
    will match an alias to a virtual host based on the content of :ref:`domains'
    <envoy_v3_api_field_config.route.v3.VirtualHost.domains>` field. The ``resource_names_unsubscribe`` field
    contains a list of virtual host names that have been :ref:`unsubscribed
    <xds_protocol_unsubscribe>` from the routing table associated with the RouteConfiguration.
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.DeltaVirtualHosts = channel.stream_stream(
                '/envoy.service.route.v3.VirtualHostDiscoveryService/DeltaVirtualHosts',
                request_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
                )

class VirtualHostDiscoveryServiceServicer(object):
    """Virtual Host Discovery Service (VHDS) is used to dynamically update the list of virtual hosts for
    a given RouteConfiguration. If VHDS is configured a virtual host list update will be triggered
    during the processing of an HTTP request if a route for the request cannot be resolved. The
    :ref:`resource_names_subscribe <envoy_v3_api_field_service.discovery.v3.DeltaDiscoveryRequest.resource_names_subscribe>`
    field contains a list of virtual host names or aliases to track. The contents of an alias would
    be the contents of a ``host`` or ``authority`` header used to make an http request. An xDS server
    will match an alias to a virtual host based on the content of :ref:`domains'
    <envoy_v3_api_field_config.route.v3.VirtualHost.domains>` field. The ``resource_names_unsubscribe`` field
    contains a list of virtual host names that have been :ref:`unsubscribed
    <xds_protocol_unsubscribe>` from the routing table associated with the RouteConfiguration.
    """

    def DeltaVirtualHosts(self, request_iterator, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_VirtualHostDiscoveryServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'DeltaVirtualHosts': grpc.stream_stream_rpc_method_handler(
                    servicer.DeltaVirtualHosts,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.route.v3.VirtualHostDiscoveryService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class VirtualHostDiscoveryService(object):
    """Virtual Host Discovery Service (VHDS) is used to dynamically update the list of virtual hosts for
    a given RouteConfiguration. If VHDS is configured a virtual host list update will be triggered
    during the processing of an HTTP request if a route for the request cannot be resolved. The
    :ref:`resource_names_subscribe <envoy_v3_api_field_service.discovery.v3.DeltaDiscoveryRequest.resource_names_subscribe>`
    field contains a list of virtual host names or aliases to track. The contents of an alias would
    be the contents of a ``host`` or ``authority`` header used to make an http request. An xDS server
    will match an alias to a virtual host based on the content of :ref:`domains'
    <envoy_v3_api_field_config.route.v3.VirtualHost.domains>` field. The ``resource_names_unsubscribe`` field
    contains a list of virtual host names that have been :ref:`unsubscribed
    <xds_protocol_unsubscribe>` from the routing table associated with the RouteConfiguration.
    """

    @staticmethod
    def DeltaVirtualHosts(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.route.v3.VirtualHostDiscoveryService/DeltaVirtualHosts',
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

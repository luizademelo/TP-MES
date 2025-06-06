
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.health.v3 import hds_pb2 as envoy_dot_service_dot_health_dot_v3_dot_hds__pb2

class HealthDiscoveryServiceStub(object):
    """[#protodoc-title: Health discovery service (HDS)]

    HDS is Health Discovery Service. It compliments Envoy’s health checking
    service by designating this Envoy to be a healthchecker for a subset of hosts
    in the cluster. The status of these health checks will be reported to the
    management server, where it can be aggregated etc and redistributed back to
    Envoy through EDS.
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.StreamHealthCheck = channel.stream_stream(
                '/envoy.service.health.v3.HealthDiscoveryService/StreamHealthCheck',
                request_serializer=envoy_dot_service_dot_health_dot_v3_dot_hds__pb2.HealthCheckRequestOrEndpointHealthResponse.SerializeToString,
                response_deserializer=envoy_dot_service_dot_health_dot_v3_dot_hds__pb2.HealthCheckSpecifier.FromString,
                )
        self.FetchHealthCheck = channel.unary_unary(
                '/envoy.service.health.v3.HealthDiscoveryService/FetchHealthCheck',
                request_serializer=envoy_dot_service_dot_health_dot_v3_dot_hds__pb2.HealthCheckRequestOrEndpointHealthResponse.SerializeToString,
                response_deserializer=envoy_dot_service_dot_health_dot_v3_dot_hds__pb2.HealthCheckSpecifier.FromString,
                )

class HealthDiscoveryServiceServicer(object):
    """[#protodoc-title: Health discovery service (HDS)]

    HDS is Health Discovery Service. It compliments Envoy’s health checking
    service by designating this Envoy to be a healthchecker for a subset of hosts
    in the cluster. The status of these health checks will be reported to the
    management server, where it can be aggregated etc and redistributed back to
    Envoy through EDS.
    """

    def StreamHealthCheck(self, request_iterator, context):
        """1. Envoy starts up and if its can_healthcheck option in the static
        bootstrap config is enabled, sends HealthCheckRequest to the management
        server. It supplies its capabilities (which protocol it can health check
        with, what zone it resides in, etc.).
        2. In response to (1), the management server designates this Envoy as a
        healthchecker to health check a subset of all upstream hosts for a given
        cluster (for example upstream Host 1 and Host 2). It streams
        HealthCheckSpecifier messages with cluster related configuration for all
        clusters this Envoy is designated to health check. Subsequent
        HealthCheckSpecifier message will be sent on changes to:
        a. Endpoints to health checks
        b. Per cluster configuration change
        3. Envoy creates a health probe based on the HealthCheck config and sends
        it to endpoint(ip:port) of Host 1 and 2. Based on the HealthCheck
        configuration Envoy waits upon the arrival of the probe response and
        looks at the content of the response to decide whether the endpoint is
        healthy or not. If a response hasn't been received within the timeout
        interval, the endpoint health status is considered TIMEOUT.
        4. Envoy reports results back in an EndpointHealthResponse message.
        Envoy streams responses as often as the interval configured by the
        management server in HealthCheckSpecifier.
        5. The management Server collects health statuses for all endpoints in the
        cluster (for all clusters) and uses this information to construct
        EndpointDiscoveryResponse messages.
        6. Once Envoy has a list of upstream endpoints to send traffic to, it load
        balances traffic to them without additional health checking. It may
        use inline healthcheck (i.e. consider endpoint UNHEALTHY if connection
        failed to a particular endpoint to account for health status propagation
        delay between HDS and EDS).
        By default, can_healthcheck is true. If can_healthcheck is false, Cluster
        configuration may not contain HealthCheck message.
        TODO(htuch): How is can_healthcheck communicated to CDS to ensure the above
        invariant?
        TODO(htuch): Add @amb67's diagram.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def FetchHealthCheck(self, request, context):
        """TODO(htuch): Unlike the gRPC version, there is no stream-based binding of
        request/response. Should we add an identifier to the HealthCheckSpecifier
        to bind with the response?
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_HealthDiscoveryServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'StreamHealthCheck': grpc.stream_stream_rpc_method_handler(
                    servicer.StreamHealthCheck,
                    request_deserializer=envoy_dot_service_dot_health_dot_v3_dot_hds__pb2.HealthCheckRequestOrEndpointHealthResponse.FromString,
                    response_serializer=envoy_dot_service_dot_health_dot_v3_dot_hds__pb2.HealthCheckSpecifier.SerializeToString,
            ),
            'FetchHealthCheck': grpc.unary_unary_rpc_method_handler(
                    servicer.FetchHealthCheck,
                    request_deserializer=envoy_dot_service_dot_health_dot_v3_dot_hds__pb2.HealthCheckRequestOrEndpointHealthResponse.FromString,
                    response_serializer=envoy_dot_service_dot_health_dot_v3_dot_hds__pb2.HealthCheckSpecifier.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.health.v3.HealthDiscoveryService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class HealthDiscoveryService(object):
    """[#protodoc-title: Health discovery service (HDS)]

    HDS is Health Discovery Service. It compliments Envoy’s health checking
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
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.health.v3.HealthDiscoveryService/StreamHealthCheck',
            envoy_dot_service_dot_health_dot_v3_dot_hds__pb2.HealthCheckRequestOrEndpointHealthResponse.SerializeToString,
            envoy_dot_service_dot_health_dot_v3_dot_hds__pb2.HealthCheckSpecifier.FromString,
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
        return grpc.experimental.unary_unary(request, target, '/envoy.service.health.v3.HealthDiscoveryService/FetchHealthCheck',
            envoy_dot_service_dot_health_dot_v3_dot_hds__pb2.HealthCheckRequestOrEndpointHealthResponse.SerializeToString,
            envoy_dot_service_dot_health_dot_v3_dot_hds__pb2.HealthCheckSpecifier.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

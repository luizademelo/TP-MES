
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.discovery.v3 import discovery_pb2 as envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2

class LocalityEndpointDiscoveryServiceStub(object):
    """[#not-implemented-hide:]
    [#protodoc-title: LEDS]
    Locality-Endpoint discovery
    [#comment:TODO(adisuissa): Link to unified matching docs:
    :ref:`architecture overview<arch_overview_service_discovery_types_leds>`]

    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.DeltaLocalityEndpoints = channel.stream_stream(
                '/envoy.service.endpoint.v3.LocalityEndpointDiscoveryService/DeltaLocalityEndpoints',
                request_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
                )

class LocalityEndpointDiscoveryServiceServicer(object):
    """[#not-implemented-hide:]
    [#protodoc-title: LEDS]
    Locality-Endpoint discovery
    [#comment:TODO(adisuissa): Link to unified matching docs:
    :ref:`architecture overview<arch_overview_service_discovery_types_leds>`]

    """

    def DeltaLocalityEndpoints(self, request_iterator, context):
        """State-of-the-World (DiscoveryRequest) and REST are not supported.

        The resource_names_subscribe resource_names_unsubscribe fields in DeltaDiscoveryRequest
        specify a list of glob collections to subscribe to updates for.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_LocalityEndpointDiscoveryServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'DeltaLocalityEndpoints': grpc.stream_stream_rpc_method_handler(
                    servicer.DeltaLocalityEndpoints,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.endpoint.v3.LocalityEndpointDiscoveryService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class LocalityEndpointDiscoveryService(object):
    """[#not-implemented-hide:]
    [#protodoc-title: LEDS]
    Locality-Endpoint discovery
    [#comment:TODO(adisuissa): Link to unified matching docs:
    :ref:`architecture overview<arch_overview_service_discovery_types_leds>`]

    """

    @staticmethod
    def DeltaLocalityEndpoints(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.endpoint.v3.LocalityEndpointDiscoveryService/DeltaLocalityEndpoints',
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

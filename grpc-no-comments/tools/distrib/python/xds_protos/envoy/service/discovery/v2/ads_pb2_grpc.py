
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

        Args:
            channel: A grpc.Channel.
        """
        self.StreamAggregatedResources = channel.stream_stream(
                '/envoy.service.discovery.v2.AggregatedDiscoveryService/StreamAggregatedResources',
                request_serializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryResponse.FromString,
                )
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
        """This is a gRPC-only API.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def DeltaAggregatedResources(self, request_iterator, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_AggregatedDiscoveryServiceServicer_to_server(servicer, server):
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
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.discovery.v2.AggregatedDiscoveryService/DeltaAggregatedResources',
            envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
            envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

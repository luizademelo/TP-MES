
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.discovery.v3 import discovery_pb2 as envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2

class ClusterDiscoveryServiceStub(object):
    """[#protodoc-title: CDS]

    Return list of all clusters this proxy will load balance to.
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.StreamClusters = channel.stream_stream(
                '/envoy.service.cluster.v3.ClusterDiscoveryService/StreamClusters',
                request_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
                )
        self.DeltaClusters = channel.stream_stream(
                '/envoy.service.cluster.v3.ClusterDiscoveryService/DeltaClusters',
                request_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
                )
        self.FetchClusters = channel.unary_unary(
                '/envoy.service.cluster.v3.ClusterDiscoveryService/FetchClusters',
                request_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
                )

class ClusterDiscoveryServiceServicer(object):
    """[#protodoc-title: CDS]

    Return list of all clusters this proxy will load balance to.
    """

    def StreamClusters(self, request_iterator, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def DeltaClusters(self, request_iterator, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def FetchClusters(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_ClusterDiscoveryServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'StreamClusters': grpc.stream_stream_rpc_method_handler(
                    servicer.StreamClusters,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.SerializeToString,
            ),
            'DeltaClusters': grpc.stream_stream_rpc_method_handler(
                    servicer.DeltaClusters,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.SerializeToString,
            ),
            'FetchClusters': grpc.unary_unary_rpc_method_handler(
                    servicer.FetchClusters,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.cluster.v3.ClusterDiscoveryService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class ClusterDiscoveryService(object):
    """[#protodoc-title: CDS]

    Return list of all clusters this proxy will load balance to.
    """

    @staticmethod
    def StreamClusters(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.cluster.v3.ClusterDiscoveryService/StreamClusters',
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def DeltaClusters(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.cluster.v3.ClusterDiscoveryService/DeltaClusters',
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def FetchClusters(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/envoy.service.cluster.v3.ClusterDiscoveryService/FetchClusters',
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

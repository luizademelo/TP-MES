
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.api.v2 import discovery_pb2 as envoy_dot_api_dot_v2_dot_discovery__pb2

class SecretDiscoveryServiceStub(object):
    """[#protodoc-title: Secret Discovery Service (SDS)]

    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.DeltaSecrets = channel.stream_stream(
                '/envoy.service.discovery.v2.SecretDiscoveryService/DeltaSecrets',
                request_serializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
                )
        self.StreamSecrets = channel.stream_stream(
                '/envoy.service.discovery.v2.SecretDiscoveryService/StreamSecrets',
                request_serializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryResponse.FromString,
                )
        self.FetchSecrets = channel.unary_unary(
                '/envoy.service.discovery.v2.SecretDiscoveryService/FetchSecrets',
                request_serializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryResponse.FromString,
                )

class SecretDiscoveryServiceServicer(object):
    """[#protodoc-title: Secret Discovery Service (SDS)]

    """

    def DeltaSecrets(self, request_iterator, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def StreamSecrets(self, request_iterator, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def FetchSecrets(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_SecretDiscoveryServiceServicer_to_server(servicer, server):
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
        return grpc.experimental.unary_unary(request, target, '/envoy.service.discovery.v2.SecretDiscoveryService/FetchSecrets',
            envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
            envoy_dot_api_dot_v2_dot_discovery__pb2.DiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

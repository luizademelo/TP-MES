
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.status.v2 import csds_pb2 as envoy_dot_service_dot_status_dot_v2_dot_csds__pb2

class ClientStatusDiscoveryServiceStub(object):
    """[#protodoc-title: Client Status Discovery Service (CSDS)]

    CSDS is Client Status Discovery Service. It can be used to get the status of
    an xDS-compliant client from the management server's point of view. In the
    future, it can potentially be used as an interface to get the current
    state directly from the client.
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.StreamClientStatus = channel.stream_stream(
                '/envoy.service.status.v2.ClientStatusDiscoveryService/StreamClientStatus',
                request_serializer=envoy_dot_service_dot_status_dot_v2_dot_csds__pb2.ClientStatusRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_status_dot_v2_dot_csds__pb2.ClientStatusResponse.FromString,
                )
        self.FetchClientStatus = channel.unary_unary(
                '/envoy.service.status.v2.ClientStatusDiscoveryService/FetchClientStatus',
                request_serializer=envoy_dot_service_dot_status_dot_v2_dot_csds__pb2.ClientStatusRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_status_dot_v2_dot_csds__pb2.ClientStatusResponse.FromString,
                )

class ClientStatusDiscoveryServiceServicer(object):
    """[#protodoc-title: Client Status Discovery Service (CSDS)]

    CSDS is Client Status Discovery Service. It can be used to get the status of
    an xDS-compliant client from the management server's point of view. In the
    future, it can potentially be used as an interface to get the current
    state directly from the client.
    """

    def StreamClientStatus(self, request_iterator, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def FetchClientStatus(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_ClientStatusDiscoveryServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'StreamClientStatus': grpc.stream_stream_rpc_method_handler(
                    servicer.StreamClientStatus,
                    request_deserializer=envoy_dot_service_dot_status_dot_v2_dot_csds__pb2.ClientStatusRequest.FromString,
                    response_serializer=envoy_dot_service_dot_status_dot_v2_dot_csds__pb2.ClientStatusResponse.SerializeToString,
            ),
            'FetchClientStatus': grpc.unary_unary_rpc_method_handler(
                    servicer.FetchClientStatus,
                    request_deserializer=envoy_dot_service_dot_status_dot_v2_dot_csds__pb2.ClientStatusRequest.FromString,
                    response_serializer=envoy_dot_service_dot_status_dot_v2_dot_csds__pb2.ClientStatusResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.status.v2.ClientStatusDiscoveryService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class ClientStatusDiscoveryService(object):
    """[#protodoc-title: Client Status Discovery Service (CSDS)]

    CSDS is Client Status Discovery Service. It can be used to get the status of
    an xDS-compliant client from the management server's point of view. In the
    future, it can potentially be used as an interface to get the current
    state directly from the client.
    """

    @staticmethod
    def StreamClientStatus(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.status.v2.ClientStatusDiscoveryService/StreamClientStatus',
            envoy_dot_service_dot_status_dot_v2_dot_csds__pb2.ClientStatusRequest.SerializeToString,
            envoy_dot_service_dot_status_dot_v2_dot_csds__pb2.ClientStatusResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def FetchClientStatus(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/envoy.service.status.v2.ClientStatusDiscoveryService/FetchClientStatus',
            envoy_dot_service_dot_status_dot_v2_dot_csds__pb2.ClientStatusRequest.SerializeToString,
            envoy_dot_service_dot_status_dot_v2_dot_csds__pb2.ClientStatusResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

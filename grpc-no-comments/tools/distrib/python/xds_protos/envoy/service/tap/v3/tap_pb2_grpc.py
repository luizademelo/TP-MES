
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.tap.v3 import tap_pb2 as envoy_dot_service_dot_tap_dot_v3_dot_tap__pb2

class TapSinkServiceStub(object):
    """[#protodoc-title: Tap sink service]

    [#not-implemented-hide:] A tap service to receive incoming taps. Envoy will call
    StreamTaps to deliver captured taps to the server
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.StreamTaps = channel.stream_unary(
                '/envoy.service.tap.v3.TapSinkService/StreamTaps',
                request_serializer=envoy_dot_service_dot_tap_dot_v3_dot_tap__pb2.StreamTapsRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_tap_dot_v3_dot_tap__pb2.StreamTapsResponse.FromString,
                )

class TapSinkServiceServicer(object):
    """[#protodoc-title: Tap sink service]

    [#not-implemented-hide:] A tap service to receive incoming taps. Envoy will call
    StreamTaps to deliver captured taps to the server
    """

    def StreamTaps(self, request_iterator, context):
        """Envoy will connect and send StreamTapsRequest messages forever. It does not expect any
        response to be sent as nothing would be done in the case of failure. The server should
        disconnect if it expects Envoy to reconnect.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_TapSinkServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'StreamTaps': grpc.stream_unary_rpc_method_handler(
                    servicer.StreamTaps,
                    request_deserializer=envoy_dot_service_dot_tap_dot_v3_dot_tap__pb2.StreamTapsRequest.FromString,
                    response_serializer=envoy_dot_service_dot_tap_dot_v3_dot_tap__pb2.StreamTapsResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.tap.v3.TapSinkService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class TapSinkService(object):
    """[#protodoc-title: Tap sink service]

    [#not-implemented-hide:] A tap service to receive incoming taps. Envoy will call
    StreamTaps to deliver captured taps to the server
    """

    @staticmethod
    def StreamTaps(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_unary(request_iterator, target, '/envoy.service.tap.v3.TapSinkService/StreamTaps',
            envoy_dot_service_dot_tap_dot_v3_dot_tap__pb2.StreamTapsRequest.SerializeToString,
            envoy_dot_service_dot_tap_dot_v3_dot_tap__pb2.StreamTapsResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

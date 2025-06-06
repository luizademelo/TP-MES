
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.accesslog.v3 import als_pb2 as envoy_dot_service_dot_accesslog_dot_v3_dot_als__pb2

class AccessLogServiceStub(object):
    """[#protodoc-title: gRPC access log service (ALS)]

    Service for streaming access logs from Envoy to an access log server.
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.StreamAccessLogs = channel.stream_unary(
                '/envoy.service.accesslog.v3.AccessLogService/StreamAccessLogs',
                request_serializer=envoy_dot_service_dot_accesslog_dot_v3_dot_als__pb2.StreamAccessLogsMessage.SerializeToString,
                response_deserializer=envoy_dot_service_dot_accesslog_dot_v3_dot_als__pb2.StreamAccessLogsResponse.FromString,
                )

class AccessLogServiceServicer(object):
    """[#protodoc-title: gRPC access log service (ALS)]

    Service for streaming access logs from Envoy to an access log server.
    """

    def StreamAccessLogs(self, request_iterator, context):
        """Envoy will connect and send StreamAccessLogsMessage messages forever. It does not expect any
        response to be sent as nothing would be done in the case of failure. The server should
        disconnect if it expects Envoy to reconnect. In the future we may decide to add a different
        API for "critical" access logs in which Envoy will buffer access logs for some period of time
        until it gets an ACK so it could then retry. This API is designed for high throughput with the
        expectation that it might be lossy.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_AccessLogServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'StreamAccessLogs': grpc.stream_unary_rpc_method_handler(
                    servicer.StreamAccessLogs,
                    request_deserializer=envoy_dot_service_dot_accesslog_dot_v3_dot_als__pb2.StreamAccessLogsMessage.FromString,
                    response_serializer=envoy_dot_service_dot_accesslog_dot_v3_dot_als__pb2.StreamAccessLogsResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.accesslog.v3.AccessLogService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class AccessLogService(object):
    """[#protodoc-title: gRPC access log service (ALS)]

    Service for streaming access logs from Envoy to an access log server.
    """

    @staticmethod
    def StreamAccessLogs(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_unary(request_iterator, target, '/envoy.service.accesslog.v3.AccessLogService/StreamAccessLogs',
            envoy_dot_service_dot_accesslog_dot_v3_dot_als__pb2.StreamAccessLogsMessage.SerializeToString,
            envoy_dot_service_dot_accesslog_dot_v3_dot_als__pb2.StreamAccessLogsResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

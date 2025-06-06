
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.trace.v2 import trace_service_pb2 as envoy_dot_service_dot_trace_dot_v2_dot_trace__service__pb2

class TraceServiceStub(object):
    """[#protodoc-title: Trace service]

    Service for streaming traces to server that consumes the trace data. It
    uses OpenCensus data model as a standard to represent trace information.
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.StreamTraces = channel.stream_unary(
                '/envoy.service.trace.v2.TraceService/StreamTraces',
                request_serializer=envoy_dot_service_dot_trace_dot_v2_dot_trace__service__pb2.StreamTracesMessage.SerializeToString,
                response_deserializer=envoy_dot_service_dot_trace_dot_v2_dot_trace__service__pb2.StreamTracesResponse.FromString,
                )

class TraceServiceServicer(object):
    """[#protodoc-title: Trace service]

    Service for streaming traces to server that consumes the trace data. It
    uses OpenCensus data model as a standard to represent trace information.
    """

    def StreamTraces(self, request_iterator, context):
        """Envoy will connect and send StreamTracesMessage messages forever. It does
        not expect any response to be sent as nothing would be done in the case
        of failure.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_TraceServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'StreamTraces': grpc.stream_unary_rpc_method_handler(
                    servicer.StreamTraces,
                    request_deserializer=envoy_dot_service_dot_trace_dot_v2_dot_trace__service__pb2.StreamTracesMessage.FromString,
                    response_serializer=envoy_dot_service_dot_trace_dot_v2_dot_trace__service__pb2.StreamTracesResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.trace.v2.TraceService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class TraceService(object):
    """[#protodoc-title: Trace service]

    Service for streaming traces to server that consumes the trace data. It
    uses OpenCensus data model as a standard to represent trace information.
    """

    @staticmethod
    def StreamTraces(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_unary(request_iterator, target, '/envoy.service.trace.v2.TraceService/StreamTraces',
            envoy_dot_service_dot_trace_dot_v2_dot_trace__service__pb2.StreamTracesMessage.SerializeToString,
            envoy_dot_service_dot_trace_dot_v2_dot_trace__service__pb2.StreamTracesResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

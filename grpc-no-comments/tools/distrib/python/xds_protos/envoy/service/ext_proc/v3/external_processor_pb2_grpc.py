
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.ext_proc.v3 import external_processor_pb2 as envoy_dot_service_dot_ext__proc_dot_v3_dot_external__processor__pb2

class ExternalProcessorStub(object):
    """[#protodoc-title: External processing service]

    A service that can access and modify HTTP requests and responses
    as part of a filter chain.
    The overall external processing protocol works like this:

    1. Envoy sends to the service information about the HTTP request.
    2. The service sends back a ProcessingResponse message that directs Envoy
    to either stop processing, continue without it, or send it the
    next chunk of the message body.
    3. If so requested, Envoy sends the server chunks of the message body,
    or the entire body at once. In either case, the server sends back
    a ProcessingResponse after each message it receives.
    4. If so requested, Envoy sends the server the HTTP trailers,
    and the server sends back a ProcessingResponse.
    5. At this point, request processing is done, and we pick up again
    at step 1 when Envoy receives a response from the upstream server.
    6. At any point above, if the server closes the gRPC stream cleanly,
    then Envoy proceeds without consulting the server.
    7. At any point above, if the server closes the gRPC stream with an error,
    then Envoy returns a 500 error to the client, unless the filter
    was configured to ignore errors.

    In other words, the process is a request/response conversation, but
    using a gRPC stream to make it easier for the server to
    maintain state.
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.Process = channel.stream_stream(
                '/envoy.service.ext_proc.v3.ExternalProcessor/Process',
                request_serializer=envoy_dot_service_dot_ext__proc_dot_v3_dot_external__processor__pb2.ProcessingRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_ext__proc_dot_v3_dot_external__processor__pb2.ProcessingResponse.FromString,
                )

class ExternalProcessorServicer(object):
    """[#protodoc-title: External processing service]

    A service that can access and modify HTTP requests and responses
    as part of a filter chain.
    The overall external processing protocol works like this:

    1. Envoy sends to the service information about the HTTP request.
    2. The service sends back a ProcessingResponse message that directs Envoy
    to either stop processing, continue without it, or send it the
    next chunk of the message body.
    3. If so requested, Envoy sends the server chunks of the message body,
    or the entire body at once. In either case, the server sends back
    a ProcessingResponse after each message it receives.
    4. If so requested, Envoy sends the server the HTTP trailers,
    and the server sends back a ProcessingResponse.
    5. At this point, request processing is done, and we pick up again
    at step 1 when Envoy receives a response from the upstream server.
    6. At any point above, if the server closes the gRPC stream cleanly,
    then Envoy proceeds without consulting the server.
    7. At any point above, if the server closes the gRPC stream with an error,
    then Envoy returns a 500 error to the client, unless the filter
    was configured to ignore errors.

    In other words, the process is a request/response conversation, but
    using a gRPC stream to make it easier for the server to
    maintain state.
    """

    def Process(self, request_iterator, context):
        """This begins the bidirectional stream that Envoy will use to
        give the server control over what the filter does. The actual
        protocol is described by the ProcessingRequest and ProcessingResponse
        messages below.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_ExternalProcessorServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'Process': grpc.stream_stream_rpc_method_handler(
                    servicer.Process,
                    request_deserializer=envoy_dot_service_dot_ext__proc_dot_v3_dot_external__processor__pb2.ProcessingRequest.FromString,
                    response_serializer=envoy_dot_service_dot_ext__proc_dot_v3_dot_external__processor__pb2.ProcessingResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.ext_proc.v3.ExternalProcessor', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class ExternalProcessor(object):
    """[#protodoc-title: External processing service]

    A service that can access and modify HTTP requests and responses
    as part of a filter chain.
    The overall external processing protocol works like this:

    1. Envoy sends to the service information about the HTTP request.
    2. The service sends back a ProcessingResponse message that directs Envoy
    to either stop processing, continue without it, or send it the
    next chunk of the message body.
    3. If so requested, Envoy sends the server chunks of the message body,
    or the entire body at once. In either case, the server sends back
    a ProcessingResponse after each message it receives.
    4. If so requested, Envoy sends the server the HTTP trailers,
    and the server sends back a ProcessingResponse.
    5. At this point, request processing is done, and we pick up again
    at step 1 when Envoy receives a response from the upstream server.
    6. At any point above, if the server closes the gRPC stream cleanly,
    then Envoy proceeds without consulting the server.
    7. At any point above, if the server closes the gRPC stream with an error,
    then Envoy returns a 500 error to the client, unless the filter
    was configured to ignore errors.

    In other words, the process is a request/response conversation, but
    using a gRPC stream to make it easier for the server to
    maintain state.
    """

    @staticmethod
    def Process(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.ext_proc.v3.ExternalProcessor/Process',
            envoy_dot_service_dot_ext__proc_dot_v3_dot_external__processor__pb2.ProcessingRequest.SerializeToString,
            envoy_dot_service_dot_ext__proc_dot_v3_dot_external__processor__pb2.ProcessingResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

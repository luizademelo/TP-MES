
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.event_reporting.v3 import event_reporting_service_pb2 as envoy_dot_service_dot_event__reporting_dot_v3_dot_event__reporting__service__pb2

class EventReportingServiceStub(object):
    """[#protodoc-title: gRPC Event Reporting Service]

    [#not-implemented-hide:]
    Service for streaming different types of events from Envoy to a server. The examples of
    such events may be health check or outlier detection events.
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.StreamEvents = channel.stream_stream(
                '/envoy.service.event_reporting.v3.EventReportingService/StreamEvents',
                request_serializer=envoy_dot_service_dot_event__reporting_dot_v3_dot_event__reporting__service__pb2.StreamEventsRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_event__reporting_dot_v3_dot_event__reporting__service__pb2.StreamEventsResponse.FromString,
                )

class EventReportingServiceServicer(object):
    """[#protodoc-title: gRPC Event Reporting Service]

    [#not-implemented-hide:]
    Service for streaming different types of events from Envoy to a server. The examples of
    such events may be health check or outlier detection events.
    """

    def StreamEvents(self, request_iterator, context):
        """Envoy will connect and send StreamEventsRequest messages forever.
        The management server may send StreamEventsResponse to configure event stream. See below.
        This API is designed for high throughput with the expectation that it might be lossy.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_EventReportingServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'StreamEvents': grpc.stream_stream_rpc_method_handler(
                    servicer.StreamEvents,
                    request_deserializer=envoy_dot_service_dot_event__reporting_dot_v3_dot_event__reporting__service__pb2.StreamEventsRequest.FromString,
                    response_serializer=envoy_dot_service_dot_event__reporting_dot_v3_dot_event__reporting__service__pb2.StreamEventsResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.event_reporting.v3.EventReportingService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class EventReportingService(object):
    """[#protodoc-title: gRPC Event Reporting Service]

    [#not-implemented-hide:]
    Service for streaming different types of events from Envoy to a server. The examples of
    such events may be health check or outlier detection events.
    """

    @staticmethod
    def StreamEvents(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.event_reporting.v3.EventReportingService/StreamEvents',
            envoy_dot_service_dot_event__reporting_dot_v3_dot_event__reporting__service__pb2.StreamEventsRequest.SerializeToString,
            envoy_dot_service_dot_event__reporting_dot_v3_dot_event__reporting__service__pb2.StreamEventsResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

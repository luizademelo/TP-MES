
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

import phone_pb2 as phone__pb2

class PhoneStub(object):
    """Missing associated documentation comment in .proto file."""

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.StreamCall = channel.stream_stream(
                '/grpc.testing.Phone/StreamCall',
                request_serializer=phone__pb2.StreamCallRequest.SerializeToString,
                response_deserializer=phone__pb2.StreamCallResponse.FromString,
                )

class PhoneServicer(object):
    """Missing associated documentation comment in .proto file."""

    def StreamCall(self, request_iterator, context):
        """Makes a phone call and communicate states via a stream.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_PhoneServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'StreamCall': grpc.stream_stream_rpc_method_handler(
                    servicer.StreamCall,
                    request_deserializer=phone__pb2.StreamCallRequest.FromString,
                    response_serializer=phone__pb2.StreamCallResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'grpc.testing.Phone', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class Phone(object):
    """Missing associated documentation comment in .proto file."""

    @staticmethod
    def StreamCall(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_stream(request_iterator, target, '/grpc.testing.Phone/StreamCall',
            phone__pb2.StreamCallRequest.SerializeToString,
            phone__pb2.StreamCallResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

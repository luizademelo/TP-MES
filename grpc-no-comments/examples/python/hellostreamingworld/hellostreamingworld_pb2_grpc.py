
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

import hellostreamingworld_pb2 as hellostreamingworld__pb2

class MultiGreeterStub(object):
    """The greeting service definition.
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.sayHello = channel.unary_stream(
                '/hellostreamingworld.MultiGreeter/sayHello',
                request_serializer=hellostreamingworld__pb2.HelloRequest.SerializeToString,
                response_deserializer=hellostreamingworld__pb2.HelloReply.FromString,
                )

class MultiGreeterServicer(object):
    """The greeting service definition.
    """

    def sayHello(self, request, context):
        """Sends multiple greetings
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_MultiGreeterServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'sayHello': grpc.unary_stream_rpc_method_handler(
                    servicer.sayHello,
                    request_deserializer=hellostreamingworld__pb2.HelloRequest.FromString,
                    response_serializer=hellostreamingworld__pb2.HelloReply.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'hellostreamingworld.MultiGreeter', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class MultiGreeter(object):
    """The greeting service definition.
    """

    @staticmethod
    def sayHello(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_stream(request, target, '/hellostreamingworld.MultiGreeter/sayHello',
            hellostreamingworld__pb2.HelloRequest.SerializeToString,
            hellostreamingworld__pb2.HelloReply.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

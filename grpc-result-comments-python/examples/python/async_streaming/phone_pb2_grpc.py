Here's the commented version of the code:

```python
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

import phone_pb2 as phone__pb2

class PhoneStub(object):
    """Client-side stub for making RPC calls to the Phone service.

    This class provides the client-side interface for making streaming calls to the
    Phone service defined in the protobuf file.
    """

    def __init__(self, channel):
        """Constructor.

        Initializes the client stub with a gRPC channel and sets up the streaming RPC method.

        Args:
            channel: A grpc.Channel. The gRPC channel used for communication with the server.
        """
        self.StreamCall = channel.stream_stream(
                '/grpc.testing.Phone/StreamCall',
                request_serializer=phone__pb2.StreamCallRequest.SerializeToString,
                response_deserializer=phone__pb2.StreamCallResponse.FromString,
                )

class PhoneServicer(object):
    """Server-side implementation of the Phone service.

    This class provides the server-side implementation that needs to be subclassed
    and implemented to handle actual RPC calls.
    """

    def StreamCall(self, request_iterator, context):
        """Handles a streaming phone call RPC.

        This is a method that should be implemented by the actual service to handle
        the streaming call. By default, it returns an UNIMPLEMENTED status.

        Args:
            request_iterator: An iterator of incoming StreamCallRequest messages.
            context: The gRPC context for the RPC call.

        Raises:
            NotImplementedError: Indicates the method is not implemented.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_PhoneServicer_to_server(servicer, server):
    """Registers the Phone service implementation with a gRPC server.

    Args:
        servicer: An instance of PhoneServicer or its subclass implementing the service methods.
        server: The gRPC server to which the service implementation will be added.
    """
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
    """Static methods for making RPC calls to the Phone service.

    This class provides static methods for making streaming calls to the Phone service
    without needing to instantiate a stub.
    """

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
        """Makes a streaming call to the Phone service.

        Args:
            request_iterator: An iterator of StreamCallRequest messages.
            target: The server address.
            options: (Optional) Additional gRPC options.
            channel_credentials: (Optional) The channel credentials.
            call_credentials: (Optional) The call credentials.
            insecure: (Optional) Boolean indicating if the connection should be insecure.
            compression: (Optional) The compression method.
            wait_for_ready: (Optional) Boolean indicating if the call should wait for ready.
            timeout: (Optional) The call timeout in seconds.
            metadata: (Optional) Additional metadata to be sent with the call.

        Returns:
            The streaming call response iterator.
        """
        return grpc.experimental.stream_stream(request_iterator, target, '/grpc.testing.Phone/StreamCall',
            phone__pb2.StreamCallRequest.SerializeToString,
            phone__pb2.StreamCallResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)
```
Here's the commented version of the code:

```python
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

import route_guide_pb2 as route__guide__pb2

class RouteGuideStub(object):
    """Client-side stub for interacting with the RouteGuide service.
    
    Provides methods that correspond to service methods defined in the .proto file.
    These methods are used by the client to initiate RPC calls to the server.
    """

    def __init__(self, channel):
        """Initializes the RouteGuideStub with a gRPC channel.

        Args:
            channel: A grpc.Channel used to communicate with the service.
        """
        # Unary-Unary RPC: Single request, single response
        self.GetFeature = channel.unary_unary(
                '/routeguide.RouteGuide/GetFeature',
                request_serializer=route__guide__pb2.Point.SerializeToString,
                response_deserializer=route__guide__pb2.Feature.FromString,
                )
        # Unary-Stream RPC: Single request, streamed response
        self.ListFeatures = channel.unary_stream(
                '/routeguide.RouteGuide/ListFeatures',
                request_serializer=route__guide__pb2.Rectangle.SerializeToString,
                response_deserializer=route__guide__pb2.Feature.FromString,
                )
        # Stream-Unary RPC: Streamed request, single response
        self.RecordRoute = channel.stream_unary(
                '/routeguide.RouteGuide/RecordRoute',
                request_serializer=route__guide__pb2.Point.SerializeToString,
                response_deserializer=route__guide__pb2.RouteSummary.FromString,
                )
        # Stream-Stream RPC: Streamed request, streamed response
        self.RouteChat = channel.stream_stream(
                '/routeguide.RouteGuide/RouteChat',
                request_serializer=route__guide__pb2.RouteNote.SerializeToString,
                response_deserializer=route__guide__pb2.RouteNote.FromString,
                )

class RouteGuideServicer(object):
    """Server-side implementation of the RouteGuide service.
    
    Defines the actual behavior of the service methods that will be implemented
    by the server.
    """

    def GetFeature(self, request, context):
        """A simple RPC (Unary-Unary).

        Obtains the feature at a given position.

        Args:
            request: A Point message containing the position to check.
            context: The RPC context.

        Returns:
            A Feature message for the feature at the given position.
            If no feature exists, returns a Feature with an empty name.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def ListFeatures(self, request, context):
        """A server-to-client streaming RPC (Unary-Stream).

        Obtains the Features available within the given Rectangle. Results are
        streamed rather than returned at once, as the rectangle may cover a
        large area with many features.

        Args:
            request: A Rectangle message defining the search area.
            context: The RPC context.

        Yields:
            Feature messages for features within the given rectangle.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def RecordRoute(self, request_iterator, context):
        """A client-to-server streaming RPC (Stream-Unary).

        Accepts a stream of Points on a route being traversed.

        Args:
            request_iterator: An iterator of Point messages.
            context: The RPC context.

        Returns:
            A RouteSummary message when traversal is completed.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def RouteChat(self, request_iterator, context):
        """A Bidirectional streaming RPC (Stream-Stream).

        Accepts a stream of RouteNotes while simultaneously returning another
        stream of RouteNotes (e.g., from other users).

        Args:
            request_iterator: An iterator of RouteNote messages.
            context: The RPC context.

        Yields:
            RouteNote messages received from other clients.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_RouteGuideServicer_to_server(servicer, server):
    """Registers the RouteGuide service implementation with a gRPC server.
    
    Args:
        servicer: An instance of RouteGuideServicer implementing the service methods.
        server: The gRPC server to which the service will be added.
    """
    # Define RPC method handlers for each service method
    rpc_method_handlers = {
            'GetFeature': grpc.unary_unary_rpc_method_handler(
                    servicer.GetFeature,
                    request_deserializer=route__guide__pb2.Point.FromString,
                    response_serializer=route__guide__pb2.Feature.SerializeToString,
            ),
            'ListFeatures': grpc.unary_stream_rpc_method_handler(
                    servicer.ListFeatures,
                    request_deserializer=route__guide__pb2.Rectangle.FromString,
                    response_serializer=route__guide__pb2.Feature.SerializeToString,
            ),
            'RecordRoute': grpc.stream_unary_rpc_method_handler(
                    servicer.RecordRoute,
                    request_deserializer=route__guide__pb2.Point.FromString,
                    response_serializer=route__guide__pb2.RouteSummary.SerializeToString,
            ),
            'RouteChat': grpc.stream_stream_rpc_method_handler(
                    servicer.RouteChat,
                    request_deserializer=route__guide__pb2.RouteNote.FromString,
                    response_serializer=route__guide__pb2.RouteNote.SerializeToString,
            ),
    }
    # Create a generic handler for the RouteGuide service
    generic_handler = grpc.method_handlers_generic_handler(
            'routeguide.RouteGuide', rpc_method_handlers)
    # Register the handler with the server
    server.add_generic_rpc_handlers((generic_handler,))

class RouteGuide(object):
    """Client-side helper class for RouteGuide service.
    
    Provides static methods for each service method, making it easier
    for clients to call the service without directly dealing with channels.
    """

    @staticmethod
    def GetFeature(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Synchronous call to GetFeature service method."""
        return grpc.experimental.unary_unary(request, target, '/routeguide.RouteGuide/GetFeature',
            route__guide__pb2.Point.SerializeToString,
            route__guide__pb2.Feature.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def ListFeatures(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Synchronous call to ListFeatures service method."""
        return grpc.experimental.unary_stream(request, target, '/routeguide.RouteGuide/ListFeatures',
            route__guide__pb2.Rectangle.SerializeToString,
            route__guide__pb2.Feature.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def RecordRoute(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Synchronous call to RecordRoute service method."""
        return grpc.experimental.stream_unary(request_iterator, target, '/routeguide.RouteGuide/RecordRoute',
            route__guide__pb2.Point.SerializeToString,
            route__guide__pb2.RouteSummary.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def RouteChat(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        """Synchronous call to RouteChat service method."""
        return grpc.experimental.stream_stream(request_iterator, target, '/routeguide.RouteGuide/RouteChat',
            route__guide__pb2.RouteNote.SerializeToString,
            route__guide__pb2.RouteNote.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)
```

"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.discovery.v3 import discovery_pb2 as envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2

class ListenerDiscoveryServiceStub(object):
    """[#protodoc-title: Listener]
    Listener :ref:`configuration overview <config_listeners>`

    The Envoy instance initiates an RPC at startup to discover a list of
    listeners. Updates are delivered via streaming from the LDS server and
    consist of a complete update of all listeners. Existing connections will be
    allowed to drain from listeners that are no longer present.
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.DeltaListeners = channel.stream_stream(
                '/envoy.service.listener.v3.ListenerDiscoveryService/DeltaListeners',
                request_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
                )
        self.StreamListeners = channel.stream_stream(
                '/envoy.service.listener.v3.ListenerDiscoveryService/StreamListeners',
                request_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
                )
        self.FetchListeners = channel.unary_unary(
                '/envoy.service.listener.v3.ListenerDiscoveryService/FetchListeners',
                request_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
                )

class ListenerDiscoveryServiceServicer(object):
    """[#protodoc-title: Listener]
    Listener :ref:`configuration overview <config_listeners>`

    The Envoy instance initiates an RPC at startup to discover a list of
    listeners. Updates are delivered via streaming from the LDS server and
    consist of a complete update of all listeners. Existing connections will be
    allowed to drain from listeners that are no longer present.
    """

    def DeltaListeners(self, request_iterator, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def StreamListeners(self, request_iterator, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def FetchListeners(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_ListenerDiscoveryServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'DeltaListeners': grpc.stream_stream_rpc_method_handler(
                    servicer.DeltaListeners,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.SerializeToString,
            ),
            'StreamListeners': grpc.stream_stream_rpc_method_handler(
                    servicer.StreamListeners,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.SerializeToString,
            ),
            'FetchListeners': grpc.unary_unary_rpc_method_handler(
                    servicer.FetchListeners,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.listener.v3.ListenerDiscoveryService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class ListenerDiscoveryService(object):
    """[#protodoc-title: Listener]
    Listener :ref:`configuration overview <config_listeners>`

    The Envoy instance initiates an RPC at startup to discover a list of
    listeners. Updates are delivered via streaming from the LDS server and
    consist of a complete update of all listeners. Existing connections will be
    allowed to drain from listeners that are no longer present.
    """

    @staticmethod
    def DeltaListeners(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.listener.v3.ListenerDiscoveryService/DeltaListeners',
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def StreamListeners(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.listener.v3.ListenerDiscoveryService/StreamListeners',
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def FetchListeners(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/envoy.service.listener.v3.ListenerDiscoveryService/FetchListeners',
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

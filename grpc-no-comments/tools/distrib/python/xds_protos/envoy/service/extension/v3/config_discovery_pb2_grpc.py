
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.discovery.v3 import discovery_pb2 as envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2

class ExtensionConfigDiscoveryServiceStub(object):
    """[#protodoc-title: Extension config discovery service (ECDS)]

    A service that supports dynamic configuration updates for a specific filter.
    Currently, ECDS is supported for network filters, HTTP filters, UDP session filters and Listener filters.
    Please check :ref:`Extension Config Discovery Service (ECDS) API <config_overview_extension_discovery>`.
    The overall extension config discovery service works as follows:

    1. A filter (:ref:`Downstream Network <envoy_v3_api_field_config.listener.v3.Filter.config_discovery>`,
    :ref:`Upstream Network <envoy_v3_api_field_config.cluster.v3.Filter.config_discovery>`,
    :ref:`Listener <envoy_v3_api_field_config.listener.v3.ListenerFilter.config_discovery>`,
    :ref:`UDP Session <envoy_v3_api_field_extensions.filters.udp.udp_proxy.v3.UdpProxyConfig.SessionFilter.config_discovery>`,
    or :ref:`HTTP <envoy_v3_api_field_extensions.filters.network.http_connection_manager.v3.HttpFilter.config_discovery>`)
    contains a :ref:`config_discovery <envoy_v3_api_msg_config.core.v3.ExtensionConfigSource>` configuration. This configuration
    includes a :ref:`config_source <envoy_v3_api_field_config.core.v3.ExtensionConfigSource.config_source>`,
    from which the filter configuration will be fetched.
    2. The client then registers for a resource using the filter name as the resource_name.
    3. The xDS server sends back the filter's configuration.
    4. The client stores the configuration that will be used in the next instantiation of the filter chain,
    i.e., for the next requests. Whenever an updated filter configuration arrives, it will be taken into
    account in the following instantiation of the filter chain.

    Note: Filters that are configured using ECDS are warmed. For more details see
    :ref:`ExtensionConfigSource <envoy_v3_api_msg_config.core.v3.ExtensionConfigSource>`.

    Return extension configurations.
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.StreamExtensionConfigs = channel.stream_stream(
                '/envoy.service.extension.v3.ExtensionConfigDiscoveryService/StreamExtensionConfigs',
                request_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
                )
        self.DeltaExtensionConfigs = channel.stream_stream(
                '/envoy.service.extension.v3.ExtensionConfigDiscoveryService/DeltaExtensionConfigs',
                request_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
                )
        self.FetchExtensionConfigs = channel.unary_unary(
                '/envoy.service.extension.v3.ExtensionConfigDiscoveryService/FetchExtensionConfigs',
                request_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
                )

class ExtensionConfigDiscoveryServiceServicer(object):
    """[#protodoc-title: Extension config discovery service (ECDS)]

    A service that supports dynamic configuration updates for a specific filter.
    Currently, ECDS is supported for network filters, HTTP filters, UDP session filters and Listener filters.
    Please check :ref:`Extension Config Discovery Service (ECDS) API <config_overview_extension_discovery>`.
    The overall extension config discovery service works as follows:

    1. A filter (:ref:`Downstream Network <envoy_v3_api_field_config.listener.v3.Filter.config_discovery>`,
    :ref:`Upstream Network <envoy_v3_api_field_config.cluster.v3.Filter.config_discovery>`,
    :ref:`Listener <envoy_v3_api_field_config.listener.v3.ListenerFilter.config_discovery>`,
    :ref:`UDP Session <envoy_v3_api_field_extensions.filters.udp.udp_proxy.v3.UdpProxyConfig.SessionFilter.config_discovery>`,
    or :ref:`HTTP <envoy_v3_api_field_extensions.filters.network.http_connection_manager.v3.HttpFilter.config_discovery>`)
    contains a :ref:`config_discovery <envoy_v3_api_msg_config.core.v3.ExtensionConfigSource>` configuration. This configuration
    includes a :ref:`config_source <envoy_v3_api_field_config.core.v3.ExtensionConfigSource.config_source>`,
    from which the filter configuration will be fetched.
    2. The client then registers for a resource using the filter name as the resource_name.
    3. The xDS server sends back the filter's configuration.
    4. The client stores the configuration that will be used in the next instantiation of the filter chain,
    i.e., for the next requests. Whenever an updated filter configuration arrives, it will be taken into
    account in the following instantiation of the filter chain.

    Note: Filters that are configured using ECDS are warmed. For more details see
    :ref:`ExtensionConfigSource <envoy_v3_api_msg_config.core.v3.ExtensionConfigSource>`.

    Return extension configurations.
    """

    def StreamExtensionConfigs(self, request_iterator, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def DeltaExtensionConfigs(self, request_iterator, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def FetchExtensionConfigs(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_ExtensionConfigDiscoveryServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'StreamExtensionConfigs': grpc.stream_stream_rpc_method_handler(
                    servicer.StreamExtensionConfigs,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.SerializeToString,
            ),
            'DeltaExtensionConfigs': grpc.stream_stream_rpc_method_handler(
                    servicer.DeltaExtensionConfigs,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.SerializeToString,
            ),
            'FetchExtensionConfigs': grpc.unary_unary_rpc_method_handler(
                    servicer.FetchExtensionConfigs,
                    request_deserializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.FromString,
                    response_serializer=envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.extension.v3.ExtensionConfigDiscoveryService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class ExtensionConfigDiscoveryService(object):
    """[#protodoc-title: Extension config discovery service (ECDS)]

    A service that supports dynamic configuration updates for a specific filter.
    Currently, ECDS is supported for network filters, HTTP filters, UDP session filters and Listener filters.
    Please check :ref:`Extension Config Discovery Service (ECDS) API <config_overview_extension_discovery>`.
    The overall extension config discovery service works as follows:

    1. A filter (:ref:`Downstream Network <envoy_v3_api_field_config.listener.v3.Filter.config_discovery>`,
    :ref:`Upstream Network <envoy_v3_api_field_config.cluster.v3.Filter.config_discovery>`,
    :ref:`Listener <envoy_v3_api_field_config.listener.v3.ListenerFilter.config_discovery>`,
    :ref:`UDP Session <envoy_v3_api_field_extensions.filters.udp.udp_proxy.v3.UdpProxyConfig.SessionFilter.config_discovery>`,
    or :ref:`HTTP <envoy_v3_api_field_extensions.filters.network.http_connection_manager.v3.HttpFilter.config_discovery>`)
    contains a :ref:`config_discovery <envoy_v3_api_msg_config.core.v3.ExtensionConfigSource>` configuration. This configuration
    includes a :ref:`config_source <envoy_v3_api_field_config.core.v3.ExtensionConfigSource.config_source>`,
    from which the filter configuration will be fetched.
    2. The client then registers for a resource using the filter name as the resource_name.
    3. The xDS server sends back the filter's configuration.
    4. The client stores the configuration that will be used in the next instantiation of the filter chain,
    i.e., for the next requests. Whenever an updated filter configuration arrives, it will be taken into
    account in the following instantiation of the filter chain.

    Note: Filters that are configured using ECDS are warmed. For more details see
    :ref:`ExtensionConfigSource <envoy_v3_api_msg_config.core.v3.ExtensionConfigSource>`.

    Return extension configurations.
    """

    @staticmethod
    def StreamExtensionConfigs(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.extension.v3.ExtensionConfigDiscoveryService/StreamExtensionConfigs',
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def DeltaExtensionConfigs(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_stream(request_iterator, target, '/envoy.service.extension.v3.ExtensionConfigDiscoveryService/DeltaExtensionConfigs',
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryRequest.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DeltaDiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def FetchExtensionConfigs(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/envoy.service.extension.v3.ExtensionConfigDiscoveryService/FetchExtensionConfigs',
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryRequest.SerializeToString,
            envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2.DiscoveryResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)


"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.auth.v2 import external_auth_pb2 as envoy_dot_service_dot_auth_dot_v2_dot_external__auth__pb2

class AuthorizationStub(object):
    """[#protodoc-title: Authorization Service ]

    The authorization service request messages used by external authorization :ref:`network filter
    <config_network_filters_ext_authz>` and :ref:`HTTP filter <config_http_filters_ext_authz>`.

    A generic interface for performing authorization check on incoming
    requests to a networked service.
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.Check = channel.unary_unary(
                '/envoy.service.auth.v2alpha.Authorization/Check',
                request_serializer=envoy_dot_service_dot_auth_dot_v2_dot_external__auth__pb2.CheckRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_auth_dot_v2_dot_external__auth__pb2.CheckResponse.FromString,
                )

class AuthorizationServicer(object):
    """[#protodoc-title: Authorization Service ]

    The authorization service request messages used by external authorization :ref:`network filter
    <config_network_filters_ext_authz>` and :ref:`HTTP filter <config_http_filters_ext_authz>`.

    A generic interface for performing authorization check on incoming
    requests to a networked service.
    """

    def Check(self, request, context):
        """Performs authorization check based on the attributes associated with the
        incoming request, and returns status `OK` or not `OK`.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_AuthorizationServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'Check': grpc.unary_unary_rpc_method_handler(
                    servicer.Check,
                    request_deserializer=envoy_dot_service_dot_auth_dot_v2_dot_external__auth__pb2.CheckRequest.FromString,
                    response_serializer=envoy_dot_service_dot_auth_dot_v2_dot_external__auth__pb2.CheckResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.auth.v2alpha.Authorization', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class Authorization(object):
    """[#protodoc-title: Authorization Service ]

    The authorization service request messages used by external authorization :ref:`network filter
    <config_network_filters_ext_authz>` and :ref:`HTTP filter <config_http_filters_ext_authz>`.

    A generic interface for performing authorization check on incoming
    requests to a networked service.
    """

    @staticmethod
    def Check(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/envoy.service.auth.v2alpha.Authorization/Check',
            envoy_dot_service_dot_auth_dot_v2_dot_external__auth__pb2.CheckRequest.SerializeToString,
            envoy_dot_service_dot_auth_dot_v2_dot_external__auth__pb2.CheckResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

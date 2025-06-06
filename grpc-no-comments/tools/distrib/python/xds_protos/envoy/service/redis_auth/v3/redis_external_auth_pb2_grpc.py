
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from envoy.service.redis_auth.v3 import redis_external_auth_pb2 as envoy_dot_service_dot_redis__auth_dot_v3_dot_redis__external__auth__pb2

class RedisProxyExternalAuthStub(object):
    """[#protodoc-title: Redis external authentication service]

    The messages used by the redis_proxy filter when performing external authentication.

    A generic interface for performing external password authentication on incoming AUTH commands.
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.Authenticate = channel.unary_unary(
                '/envoy.service.redis_auth.v3.RedisProxyExternalAuth/Authenticate',
                request_serializer=envoy_dot_service_dot_redis__auth_dot_v3_dot_redis__external__auth__pb2.RedisProxyExternalAuthRequest.SerializeToString,
                response_deserializer=envoy_dot_service_dot_redis__auth_dot_v3_dot_redis__external__auth__pb2.RedisProxyExternalAuthResponse.FromString,
                )

class RedisProxyExternalAuthServicer(object):
    """[#protodoc-title: Redis external authentication service]

    The messages used by the redis_proxy filter when performing external authentication.

    A generic interface for performing external password authentication on incoming AUTH commands.
    """

    def Authenticate(self, request, context):
        """Performs authentication check based on the data sent with the AUTH request.
        Returns either an OK status or an error status.
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

def add_RedisProxyExternalAuthServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'Authenticate': grpc.unary_unary_rpc_method_handler(
                    servicer.Authenticate,
                    request_deserializer=envoy_dot_service_dot_redis__auth_dot_v3_dot_redis__external__auth__pb2.RedisProxyExternalAuthRequest.FromString,
                    response_serializer=envoy_dot_service_dot_redis__auth_dot_v3_dot_redis__external__auth__pb2.RedisProxyExternalAuthResponse.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'envoy.service.redis_auth.v3.RedisProxyExternalAuth', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))

class RedisProxyExternalAuth(object):
    """[#protodoc-title: Redis external authentication service]

    The messages used by the redis_proxy filter when performing external authentication.

    A generic interface for performing external password authentication on incoming AUTH commands.
    """

    @staticmethod
    def Authenticate(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/envoy.service.redis_auth.v3.RedisProxyExternalAuth/Authenticate',
            envoy_dot_service_dot_redis__auth_dot_v3_dot_redis__external__auth__pb2.RedisProxyExternalAuthRequest.SerializeToString,
            envoy_dot_service_dot_redis__auth_dot_v3_dot_redis__external__auth__pb2.RedisProxyExternalAuthResponse.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

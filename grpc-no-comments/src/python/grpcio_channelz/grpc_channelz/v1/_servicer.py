# Copyright 2020 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Channelz debug service implementation in gRPC Python."""

from google.protobuf import json_format
import grpc
from grpc._cython import cygrpc
import grpc_channelz.v1.channelz_pb2 as _channelz_pb2
import grpc_channelz.v1.channelz_pb2_grpc as _channelz_pb2_grpc

class ChannelzServicer(_channelz_pb2_grpc.ChannelzServicer):
    """Servicer handling RPCs for service statuses."""

    @staticmethod
    def GetTopChannels(request, context):
        try:
            return json_format.Parse(
                cygrpc.channelz_get_top_channels(request.start_channel_id),
                _channelz_pb2.GetTopChannelsResponse(),
            )
        except (ValueError, json_format.ParseError) as e:
            context.set_code(grpc.StatusCode.INTERNAL)
            context.set_details(str(e))

    @staticmethod
    def GetServers(request, context):
        try:
            return json_format.Parse(
                cygrpc.channelz_get_servers(request.start_server_id),
                _channelz_pb2.GetServersResponse(),
            )
        except (ValueError, json_format.ParseError) as e:
            context.set_code(grpc.StatusCode.INTERNAL)
            context.set_details(str(e))

    @staticmethod
    def GetServer(request, context):
        try:
            return json_format.Parse(
                cygrpc.channelz_get_server(request.server_id),
                _channelz_pb2.GetServerResponse(),
            )
        except ValueError as e:
            context.set_code(grpc.StatusCode.NOT_FOUND)
            context.set_details(str(e))
        except json_format.ParseError as e:
            context.set_code(grpc.StatusCode.INTERNAL)
            context.set_details(str(e))

    @staticmethod
    def GetServerSockets(request, context):
        try:
            return json_format.Parse(
                cygrpc.channelz_get_server_sockets(
                    request.server_id,
                    request.start_socket_id,
                    request.max_results,
                ),
                _channelz_pb2.GetServerSocketsResponse(),
            )
        except ValueError as e:
            context.set_code(grpc.StatusCode.NOT_FOUND)
            context.set_details(str(e))
        except json_format.ParseError as e:
            context.set_code(grpc.StatusCode.INTERNAL)
            context.set_details(str(e))

    @staticmethod
    def GetChannel(request, context):
        try:
            return json_format.Parse(
                cygrpc.channelz_get_channel(request.channel_id),
                _channelz_pb2.GetChannelResponse(),
            )
        except ValueError as e:
            context.set_code(grpc.StatusCode.NOT_FOUND)
            context.set_details(str(e))
        except json_format.ParseError as e:
            context.set_code(grpc.StatusCode.INTERNAL)
            context.set_details(str(e))

    @staticmethod
    def GetSubchannel(request, context):
        try:
            return json_format.Parse(
                cygrpc.channelz_get_subchannel(request.subchannel_id),
                _channelz_pb2.GetSubchannelResponse(),
            )
        except ValueError as e:
            context.set_code(grpc.StatusCode.NOT_FOUND)
            context.set_details(str(e))
        except json_format.ParseError as e:
            context.set_code(grpc.StatusCode.INTERNAL)
            context.set_details(str(e))

    @staticmethod
    def GetSocket(request, context):
        try:
            return json_format.Parse(
                cygrpc.channelz_get_socket(request.socket_id),
                _channelz_pb2.GetSocketResponse(),
            )
        except ValueError as e:
            context.set_code(grpc.StatusCode.NOT_FOUND)
            context.set_details(str(e))
        except json_format.ParseError as e:
            context.set_code(grpc.StatusCode.INTERNAL)
            context.set_details(str(e))

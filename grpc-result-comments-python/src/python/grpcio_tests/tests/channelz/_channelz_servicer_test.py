Here's the commented version of the code:

```python
# Copyright 2018 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Tests for gRPC Channelz service implementation."""

from concurrent import futures
import sys
import unittest

import grpc
from grpc_channelz.v1 import channelz
from grpc_channelz.v1 import channelz_pb2
from grpc_channelz.v1 import channelz_pb2_grpc

from tests.unit import test_common
from tests.unit.framework.common import test_constants

# Constants for RPC method names
_SUCCESSFUL_UNARY_UNARY = "/test/SuccessfulUnaryUnary"
_FAILED_UNARY_UNARY = "/test/FailedUnaryUnary"
_SUCCESSFUL_STREAM_STREAM = "/test/SuccessfulStreamStream"

# Sample request and response messages
_REQUEST = b"\x00\x00\x00"
_RESPONSE = b"\x01\x01\x01"

# Configuration options
_DISABLE_REUSE_PORT = (("grpc.so_reuseport", 0),)
_ENABLE_CHANNELZ = (("grpc.enable_channelz", 1),)
_DISABLE_CHANNELZ = (("grpc.enable_channelz", 0),)

# RPC handler implementations
def _successful_unary_unary(request, servicer_context):
    """Handles successful unary-unary RPC by returning a fixed response."""
    return _RESPONSE

def _failed_unary_unary(request, servicer_context):
    """Handles failed unary-unary RPC by returning an error status."""
    servicer_context.set_code(grpc.StatusCode.INTERNAL)
    servicer_context.set_details("Channelz Test Intended Failure")

def _successful_stream_stream(request_iterator, servicer_context):
    """Handles successful stream-stream RPC by yielding fixed responses."""
    for _ in request_iterator:
        yield _RESPONSE

class _GenericHandler(grpc.GenericRpcHandler):
    """Generic RPC handler that routes requests to appropriate methods."""
    def service(self, handler_call_details):
        """Routes RPC methods to their respective handlers."""
        if handler_call_details.method == _SUCCESSFUL_UNARY_UNARY:
            return grpc.unary_unary_rpc_method_handler(_successful_unary_unary)
        elif handler_call_details.method == _FAILED_UNARY_UNARY:
            return grpc.unary_unary_rpc_method_handler(_failed_unary_unary)
        elif handler_call_details.method == _SUCCESSFUL_STREAM_STREAM:
            return grpc.stream_stream_rpc_method_handler(
                _successful_stream_stream
            )
        else:
            return None

class _ChannelServerPair(object):
    """Container for a channel-server pair used in tests."""
    def __init__(self):
        """Initializes a channel-server pair with Channelz enabled."""
        # Create server with Channelz enabled
        self.server = grpc.server(
            futures.ThreadPoolExecutor(max_workers=3),
            options=_DISABLE_REUSE_PORT + _ENABLE_CHANNELZ,
        )
        port = self.server.add_insecure_port("[::]:0")
        self.server.add_generic_rpc_handlers((_GenericHandler(),))
        self.server.start()

        # Create channel with Channelz enabled
        self.channel = grpc.insecure_channel(
            "localhost:%d" % port, _ENABLE_CHANNELZ
        )

def _generate_channel_server_pairs(n):
    """Generates n channel-server pairs for testing."""
    return [_ChannelServerPair() for i in range(n)]

def _close_channel_server_pairs(pairs):
    """Closes all channel-server pairs in the given list."""
    for pair in pairs:
        pair.server.stop(None)
        pair.channel.close()

@unittest.skipIf(
    sys.version_info[0] < 3, "ProtoBuf descriptor has moved on from Python2"
)
class ChannelzServicerTest(unittest.TestCase):
    """Test cases for Channelz service implementation."""

    def _send_successful_unary_unary(self, idx):
        """Sends a successful unary-unary RPC to the specified pair."""
        _, r = (
            self._pairs[idx]
            .channel.unary_unary(
                _SUCCESSFUL_UNARY_UNARY,
                _registered_method=True,
            )
            .with_call(_REQUEST)
        )
        self.assertEqual(r.code(), grpc.StatusCode.OK)

    def _send_failed_unary_unary(self, idx):
        """Sends a failed unary-unary RPC to the specified pair."""
        try:
            self._pairs[idx].channel.unary_unary(
                _FAILED_UNARY_UNARY,
                _registered_method=True,
            ).with_call(_REQUEST)
        except grpc.RpcError:
            return
        else:
            self.fail("This call supposed to fail")

    def _send_successful_stream_stream(self, idx):
        """Sends a successful stream-stream RPC to the specified pair."""
        response_iterator = (
            self._pairs[idx]
            .channel.stream_stream(
                _SUCCESSFUL_STREAM_STREAM,
                _registered_method=True,
            )
            .__call__(iter([_REQUEST] * test_constants.STREAM_LENGTH))
        cnt = 0
        for _ in response_iterator:
            cnt += 1
        self.assertEqual(cnt, test_constants.STREAM_LENGTH)

    def _get_channel_id(self, idx):
        """Gets the channel ID for the specified pair (may not be consecutive)."""
        resp = self._channelz_stub.GetTopChannels(
            channelz_pb2.GetTopChannelsRequest(start_channel_id=0)
        )
        self.assertGreater(len(resp.channel), idx)
        return resp.channel[idx].ref.channel_id

    def setUp(self):
        """Sets up test environment before each test case."""
        self._pairs = []

        # Create a server for Channelz service with Channelz disabled
        self._server = grpc.server(
            futures.ThreadPoolExecutor(max_workers=3),
            options=_DISABLE_REUSE_PORT + _DISABLE_CHANNELZ,
        )
        port = self._server.add_insecure_port("[::]:0")
        channelz.add_channelz_servicer(self._server)
        self._server.start()

        # Create channel to Channelz service with Channelz disabled
        self._channel = grpc.insecure_channel(
            "localhost:%d" % port, _DISABLE_CHANNELZ
        )
        self._channelz_stub = channelz_pb2_grpc.ChannelzStub(self._channel)

    def tearDown(self):
        """Cleans up test environment after each test case."""
        self._server.stop(None)
        self._channel.close()
        _close_channel_server_pairs(self._pairs)

    def test_get_top_channels_basic(self):
        """Tests basic functionality of GetTopChannels RPC."""
        self._pairs = _generate_channel_server_pairs(1)
        resp = self._channelz_stub.GetTopChannels(
            channelz_pb2.GetTopChannelsRequest(start_channel_id=0)
        )
        self.assertEqual(len(resp.channel), 1)
        self.assertEqual(resp.end, True)

    def test_get_top_channels_high_start_id(self):
        """Tests GetTopChannels with a high start ID that should return empty."""
        self._pairs = _generate_channel_server_pairs(1)
        resp = self._channelz_stub.GetTopChannels(
            channelz_pb2.GetTopChannelsRequest(start_channel_id=10000)
        )
        self.assertEqual(len(resp.channel), 0)
        self.assertEqual(resp.end, True)

    def test_successful_request(self):
        """Tests Channelz metrics after a successful RPC."""
        self._pairs = _generate_channel_server_pairs(1)
        self._send_successful_unary_unary(0)
        resp = self._channelz_stub.GetChannel(
            channelz_pb2.GetChannelRequest(channel_id=self._get_channel_id(0))
        )
        self.assertEqual(resp.channel.data.calls_started, 1)
        self.assertEqual(resp.channel.data.calls_succeeded, 1)
        self.assertEqual(resp.channel.data.calls_failed, 0)

    def test_failed_request(self):
        """Tests Channelz metrics after a failed RPC."""
        self._pairs = _generate_channel_server_pairs(1)
        self._send_failed_unary_unary(0)
        resp = self._channelz_stub.GetChannel(
            channelz_pb2.GetChannelRequest(channel_id=self._get_channel_id(0))
        )
        self.assertEqual(resp.channel.data.calls_started, 1)
        self.assertEqual(resp.channel.data.calls_succeeded, 0)
        self.assertEqual(resp.channel.data.calls_failed, 1)

    def test_many_requests(self):
        """Tests Channelz metrics after multiple successful and failed RPCs."""
        self._pairs = _generate_channel_server_pairs(1)
        k_success = 7
        k_failed = 9
        for i in range(k_success):
            self._send_successful_unary_unary(0)
        for i in range(k_failed):
            self._send_failed_unary_unary(0)
        resp = self._channelz_stub.GetChannel(
            channelz_pb2.GetChannelRequest(channel_id=self._get_channel_id(0))
        )
        self.assertEqual(resp.channel.data.calls_started, k_success + k_failed)
        self.assertEqual(resp.channel.data.calls_succeeded, k_success)
        self.assertEqual(resp.channel.data.calls_failed, k_failed)

    def test_many_channel(self):
        """Tests GetTopChannels with multiple channels."""
        k_channels = 4
        self._pairs = _generate_channel_server_pairs(k_channels)
        resp = self._channelz_stub.GetTopChannels(
            channelz_pb2.GetTopChannelsRequest(start_channel_id=0)
        )
        self.assertEqual(len(resp.channel), k_channels)

    def test_many_subchannels(self):
        """Tests subchannel metrics with multiple channels and RPCs."""
        k_channels = 4
        self._pairs = _generate_channel_server_pairs(k_channels)
        k_success = 17
        k_failed = 19
        for i in range(k_success):
            self._send_successful_unary_unary(0)
            self._send_successful_unary_unary(2)
        for i in range(k_failed):
            self._send_failed_unary_unary(1)
            self._send_failed_unary_unary(2)

        gtc_resp = self._channelz_stub.GetTopChannels(
            channelz_pb2.GetTopChannelsRequest(start_channel_id=0)
        )
        self.assertEqual(len(gtc_resp.channel), k_channels)
        for i in range(k_channels):
            if gtc_resp.channel[i].data.calls_started == 0:
                self.assertEqual(len(gtc_resp.channel[i].subchannel_ref), 0)
                continue

            self.assertGreater(len(gtc_resp.channel[i].subchannel_ref), 0)
            gsc_resp = self._channelz_stub.GetSubchannel(
                channelz_pb2.GetSubchannelRequest(
                    subchannel_id=gtc_resp.channel[i]
                    .subchannel_ref[0]
                    .subchannel_id
                )
            )
            # Verify subchannel metrics match channel metrics
            self.assertEqual(
                gtc_resp.channel[i].data.calls_started,
                gsc_resp.subchannel.data.calls_started,
            )
            self.assertEqual(
                gtc_resp.channel[i].data.calls_succeeded,
                gsc_resp.subchannel.data.calls_succeeded,
            )
            self.assertEqual(
                gtc_resp.channel[i].data.calls_failed,
                gsc_resp.subchannel.data.calls_failed,
            )

    def test_server_basic(self):
        """Tests basic functionality of GetServers RPC."""
        self._pairs = _generate_channel_server_pairs(1)
        resp = self._channelz_stub.GetServers(
            channelz_pb2.GetServersRequest(start_server_id=0)
        )
        self.assertEqual(len(resp.server), 1)

    def test_get_one_server(self):
        """Tests getting a single server's details."""
        self._pairs = _generate_channel_server_pairs(1)
        gss_resp = self._channelz_stub.GetServers(
            channelz_pb2.GetServersRequest(start_server_id=0)
        )
        self.assertEqual(len(gss_resp.server), 1)
        gs_resp = self._channelz_stub.GetServer(
            channelz_pb2.GetServerRequest(
                server_id=gss_resp.server[0].ref.server_id
            )
        )
        self.assertEqual(
            gss_resp.server[0].ref.server_id, gs_resp.server.ref.server_id
        )

    def test_server_call(self):
        """Tests server metrics after successful and failed RPCs."""
        self._pairs = _generate_channel_server_pairs(1)
        k_success = 23
        k_failed = 29
        for i in range(k_success):
            self._send_successful_unary_unary(0)
        for i in range(k_failed):
            self._send_failed_unary_unary(0)

        resp = self._channelz_stub.GetServers(
            channelz_pb2.GetServersRequest(start_server_id=0)
        )
        self.assertEqual(len(resp.server), 1)
        self.assertEqual(
            resp.server[0].data.calls_started, k_success + k_failed
        )
        self.assertEqual(resp.server[0].data.calls_succeeded, k_success)
        self.assertEqual(resp.server[0].data.calls_failed, k_failed)

    def test_many_subchannels_and_sockets(self):
        """Tests subchannel and socket metrics with multiple channels and RPCs."""
        k_channels = 4
        self._pairs = _generate_channel_server_pairs(k_channels)
        k_success = 3
        k_failed = 5
        for i in range(k_success):
            self._send_successful_unary_unary(0)
            self._send_successful_unary_unary(2)
        for i in range(k_failed):
            self._send_failed_unary_unary(1)
            self._send_failed_unary_unary(2)

        gtc_resp = self._channelz_stub.GetTopChannels(
            channelz_pb2.GetTopChannelsRequest(start_channel_id=0)
        )
        self.assertEqual(len(gtc_resp.channel), k_channels)
        for i in range(k_channels):
            if gtc_resp.channel[i].data.calls_started == 0:
                self.assertEqual(len(gtc_resp.channel[i].subchannel_ref), 0)
                continue

            self.assertGreater(len(gtc_resp.channel[i].subchannel_ref), 0)
            gsc_resp = self._channelz_stub.GetSubchannel(
                channelz_pb2.GetSubchannelRequest(
                    subchannel_id=gtc_resp.channel[i]
                    .subchannel_ref[0]
                    .subchannel_id
                )
            )
            self.assertEqual(len(gsc_resp.subchannel.socket_ref), 1)

            gs_resp = self._channelz_stub.GetSocket(
                channelz_pb2.GetSocketRequest(
                    socket_id=gsc_resp.subchannel.socket_ref[0].socket_id
                )
            )
            # Verify socket metrics match subchannel metrics
            self.assertEqual(
                gsc_resp.subchannel.data.calls_started,
                gs_resp.socket.data.streams_started,
            )
            self.assertEqual(
                gsc_resp.subchannel.data.calls_started,
                gs_resp.socket.data.streams_succeeded,
            )
            self.assertEqual(
                gsc_resp.subchannel.data.calls_started,
                gs_resp.socket.data.messages_sent,
            )
            self.assertEqual(
                gsc_resp.subchannel.data.calls_succeeded,
                gs_resp.socket.data.messages_received,
            )

            # Verify socket addresses are valid
            if gs_resp.socket.remote.HasField("tcpip_address"):
                address = gs_resp.socket.remote.tcpip_address.ip_address
                self.assertTrue(
                    len(address) == 4 or len(address) == 16, address
                )
            if gs_resp.socket.local.HasField("tcpip_address"):
                address = gs_resp.socket.local.tcpip_address.ip_address
                self.assertTrue(
                    len(address) == 4 or len(address) == 16, address
                )

    def test_streaming_rpc(self):
        """Tests Channelz metrics for streaming RPCs."""
        self._pairs = _generate_channel_server_pairs(1)
        self._send_successful_stream_stream(0)

        gc_resp = self._channelz_stub.GetChannel(
            channelz_pb2.GetChannelRequest(channel_id=self._get_channel_id(0))
        )
        self.assertEqual(gc_resp.channel.data.calls_started, 1)
        self.assertEqual(gc_resp.channel.data.calls_succeeded, 1)
        self.assertEqual(gc_resp.channel.data.calls_failed, 0)

        self.assertGreater(len(gc_resp.channel.subchannel_ref), 0)

        # Wait for subchannel to complete processing
        while True:
            gsc_resp = self._channelz_stub.GetSubchannel(
                channelz_pb2.GetSubchannelRequest(
                    subchannel_id=gc_resp.channel.subchannel_ref[
                        0
                    ].subchannel_id
                )
            )
            if (
                gsc_resp.subchannel.data.calls_started
                == gsc_resp.subchannel.data.calls_succeeded
                + gsc_resp.subchannel.data.calls_failed
            ):
                break
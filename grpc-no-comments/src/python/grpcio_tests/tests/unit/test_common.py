# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Common code used throughout tests of gRPC."""

import ast
import collections
from concurrent import futures
import os
import threading

import grpc

INVOCATION_INITIAL_METADATA = (
    ("0", "abc"),
    ("1", "def"),
    ("2", "ghi"),
)
SERVICE_INITIAL_METADATA = (
    ("3", "jkl"),
    ("4", "mno"),
    ("5", "pqr"),
)
SERVICE_TERMINAL_METADATA = (
    ("6", "stu"),
    ("7", "vwx"),
    ("8", "yza"),
)
DETAILS = "test details"

def metadata_transmitted(original_metadata, transmitted_metadata):
    """Judges whether or not metadata was acceptably transmitted.

    gRPC is allowed to insert key-value pairs into the metadata values given by
    applications and to reorder key-value pairs with different keys but it is not
    allowed to alter existing key-value pairs or to reorder key-value pairs with
    the same key.

    Args:
      original_metadata: A metadata value used in a test of gRPC. An iterable over
        iterables of length 2.
      transmitted_metadata: A metadata value corresponding to original_metadata
        after having been transmitted via gRPC. An iterable over iterables of
        length 2.

    Returns:
       A boolean indicating whether transmitted_metadata accurately reflects
        original_metadata after having been transmitted via gRPC.
    """
    original = collections.defaultdict(list)
    for key, value in original_metadata:
        original[key].append(value)
    transmitted = collections.defaultdict(list)
    for key, value in transmitted_metadata:
        transmitted[key].append(value)

    for key, values in original.items():
        transmitted_values = transmitted[key]
        transmitted_iterator = iter(transmitted_values)
        try:
            for value in values:
                while True:
                    transmitted_value = next(transmitted_iterator)
                    if value == transmitted_value:
                        break
        except StopIteration:
            return False
    else:
        return True

def test_secure_channel(target, channel_credentials, server_host_override):
    """Creates an insecure Channel to a remote host.

    Args:
      host: The name of the remote host to which to connect.
      port: The port of the remote host to which to connect.
      channel_credentials: The implementations.ChannelCredentials with which to
        connect.
      server_host_override: The target name used for SSL host name checking.

    Returns:
      An implementations.Channel to the remote host through which RPCs may be
        conducted.
    """
    channel = grpc.secure_channel(
        target,
        channel_credentials,
        (
            (
                "grpc.ssl_target_name_override",
                server_host_override,
            ),
        ),
    )
    return channel

def test_server(max_workers=10, reuse_port=False):
    """Creates an insecure grpc server.

    These servers have SO_REUSEPORT disabled to prevent cross-talk.
    """
    server_kwargs = os.environ.get("GRPC_ADDITIONAL_SERVER_KWARGS", "{}")
    server_kwargs = ast.literal_eval(server_kwargs)
    return grpc.server(
        futures.ThreadPoolExecutor(max_workers=max_workers),
        options=(("grpc.so_reuseport", int(reuse_port)),),
        **server_kwargs,
    )

class WaitGroup(object):
    def __init__(self, n=0):
        self.count = n
        self.cv = threading.Condition()

    def add(self, n):
        self.cv.acquire()
        self.count += n
        self.cv.release()

    def done(self):
        self.cv.acquire()
        self.count -= 1
        if self.count == 0:
            self.cv.notify_all()
        self.cv.release()

    def wait(self):
        self.cv.acquire()
        while self.count > 0:
            self.cv.wait()
        self.cv.release()

def running_under_gevent():
    try:
        from gevent import monkey
        import gevent.socket
    except ImportError:
        return False
    else:
        import socket

        return socket.socket is gevent.socket.socket

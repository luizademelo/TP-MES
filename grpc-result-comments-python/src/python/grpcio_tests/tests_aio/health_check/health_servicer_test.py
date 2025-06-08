Here's the commented version of the code:

```python
# Copyright 2020 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Tests AsyncIO version of grpcio-health-checking."""

import asyncio
import logging
import random
import time
import unittest

import grpc
from grpc.experimental import aio
from grpc_health.v1 import health
from grpc_health.v1 import health_pb2
from grpc_health.v1 import health_pb2_grpc

from tests.unit.framework.common import test_constants
from tests_aio.unit._test_base import AioTestBase

# Constants for service names used in tests
_SERVING_SERVICE = "grpc.test.TestServiceServing"
_UNKNOWN_SERVICE = "grpc.test.TestServiceUnknown"
_NOT_SERVING_SERVICE = "grpc.test.TestServiceNotServing"
_WATCH_SERVICE = "grpc.test.WatchService"

# Number of status changes to test for duplicate status filtering
_LARGE_NUMBER_OF_STATUS_CHANGES = 1000

async def _pipe_to_queue(call, queue):
    """Helper function to pipe gRPC streaming responses into an asyncio queue.
    
    Args:
        call: The gRPC call object that yields responses
        queue: The asyncio queue to put responses into
    """
    async for response in call:
        await queue.put(response)

class HealthServicerTest(AioTestBase):
    """Test cases for the gRPC Health Checking AsyncIO implementation."""
    
    async def setUp(self):
        """Set up test environment before each test method."""
        # Initialize health servicer with test services in different states
        self._servicer = health.aio.HealthServicer()
        await self._servicer.set(
            _SERVING_SERVICE, health_pb2.HealthCheckResponse.SERVING
        )
        await self._servicer.set(
            _UNKNOWN_SERVICE, health_pb2.HealthCheckResponse.UNKNOWN
        )
        await self._servicer.set(
            _NOT_SERVING_SERVICE, health_pb2.HealthCheckResponse.NOT_SERVING
        )
        
        # Create and start gRPC server
        self._server = aio.server()
        port = self._server.add_insecure_port("[::]:0")
        health_pb2_grpc.add_HealthServicer_to_server(
            self._servicer, self._server
        )
        await self._server.start()

        # Create client channel and stub
        self._channel = aio.insecure_channel("localhost:%d" % port)
        self._stub = health_pb2_grpc.HealthStub(self._channel)

    async def tearDown(self):
        """Clean up test environment after each test method."""
        await self._channel.close()
        await self._server.stop(None)

    async def test_check_empty_service(self):
        """Test checking health status without specifying a service."""
        request = health_pb2.HealthCheckRequest()
        resp = await self._stub.Check(request)
        self.assertEqual(health_pb2.HealthCheckResponse.SERVING, resp.status)

    async def test_check_serving_service(self):
        """Test checking health status of a serving service."""
        request = health_pb2.HealthCheckRequest(service=_SERVING_SERVICE)
        resp = await self._stub.Check(request)
        self.assertEqual(health_pb2.HealthCheckResponse.SERVING, resp.status)

    async def test_check_unknown_service(self):
        """Test checking health status of an unknown service."""
        request = health_pb2.HealthCheckRequest(service=_UNKNOWN_SERVICE)
        resp = await self._stub.Check(request)
        self.assertEqual(health_pb2.HealthCheckResponse.UNKNOWN, resp.status)

    async def test_check_not_serving_service(self):
        """Test checking health status of a not-serving service."""
        request = health_pb2.HealthCheckRequest(service=_NOT_SERVING_SERVICE)
        resp = await self._stub.Check(request)
        self.assertEqual(
            health_pb2.HealthCheckResponse.NOT_SERVING, resp.status
        )

    async def test_check_not_found_service(self):
        """Test checking health status of a non-existent service."""
        request = health_pb2.HealthCheckRequest(service="not-found")
        with self.assertRaises(aio.AioRpcError) as context:
            await self._stub.Check(request)

        self.assertEqual(grpc.StatusCode.NOT_FOUND, context.exception.code())

    async def test_health_service_name(self):
        """Test that the health service name is correct."""
        self.assertEqual(health.SERVICE_NAME, "grpc.health.v1.Health")

    async def test_watch_empty_service(self):
        """Test watching health status changes for an empty service request."""
        request = health_pb2.HealthCheckRequest(service=health.OVERALL_HEALTH)

        call = self._stub.Watch(request)
        queue = asyncio.Queue()
        task = self.loop.create_task(_pipe_to_queue(call, queue))

        self.assertEqual(
            health_pb2.HealthCheckResponse.SERVING, (await queue.get()).status
        )

        call.cancel()

        with self.assertRaises(asyncio.CancelledError):
            await task

        self.assertTrue(queue.empty())

    async def test_watch_new_service(self):
        """Test watching health status changes for a service."""
        request = health_pb2.HealthCheckRequest(service=_WATCH_SERVICE)
        call = self._stub.Watch(request)
        queue = asyncio.Queue()
        task = self.loop.create_task(_pipe_to_queue(call, queue))

        # Initial status should be UNKNOWN
        self.assertEqual(
            health_pb2.HealthCheckResponse.SERVICE_UNKNOWN,
            (await queue.get()).status,
        )

        # Test status change to SERVING
        await self._servicer.set(
            _WATCH_SERVICE, health_pb2.HealthCheckResponse.SERVING
        )
        self.assertEqual(
            health_pb2.HealthCheckResponse.SERVING, (await queue.get()).status
        )

        # Test status change to NOT_SERVING
        await self._servicer.set(
            _WATCH_SERVICE, health_pb2.HealthCheckResponse.NOT_SERVING
        )
        self.assertEqual(
            health_pb2.HealthCheckResponse.NOT_SERVING,
            (await queue.get()).status,
        )

        call.cancel()

        with self.assertRaises(asyncio.CancelledError):
            await task

        self.assertTrue(queue.empty())

    async def test_watch_service_isolation(self):
        """Test that watching one service doesn't receive updates for others."""
        request = health_pb2.HealthCheckRequest(service=_WATCH_SERVICE)
        call = self._stub.Watch(request)
        queue = asyncio.Queue()
        task = self.loop.create_task(_pipe_to_queue(call, queue))

        self.assertEqual(
            health_pb2.HealthCheckResponse.SERVICE_UNKNOWN,
            (await queue.get()).status,
        )

        # Changing another service's status shouldn't affect this watcher
        await self._servicer.set(
            "some-other-service", health_pb2.HealthCheckResponse.SERVING
        )

        with self.assertRaises(asyncio.TimeoutError):
            await asyncio.wait_for(queue.get(), test_constants.SHORT_TIMEOUT)

        call.cancel()

        with self.assertRaises(asyncio.CancelledError):
            await task

        self.assertTrue(queue.empty())

    async def test_two_watchers(self):
        """Test that multiple watchers for the same service work correctly."""
        request = health_pb2.HealthCheckRequest(service=_WATCH_SERVICE)
        queue1 = asyncio.Queue()
        queue2 = asyncio.Queue()
        call1 = self._stub.Watch(request)
        call2 = self._stub.Watch(request)
        task1 = self.loop.create_task(_pipe_to_queue(call1, queue1))
        task2 = self.loop.create_task(_pipe_to_queue(call2, queue2))

        # Both watchers should get initial status
        self.assertEqual(
            health_pb2.HealthCheckResponse.SERVICE_UNKNOWN,
            (await queue1.get()).status,
        )
        self.assertEqual(
            health_pb2.HealthCheckResponse.SERVICE_UNKNOWN,
            (await queue2.get()).status,
        )

        # Both watchers should get status update
        await self._servicer.set(
            _WATCH_SERVICE, health_pb2.HealthCheckResponse.SERVING
        )
        self.assertEqual(
            health_pb2.HealthCheckResponse.SERVING, (await queue1.get()).status
        )
        self.assertEqual(
            health_pb2.HealthCheckResponse.SERVING, (await queue2.get()).status
        )

        call1.cancel()
        call2.cancel()

        with self.assertRaises(asyncio.CancelledError):
            await task1

        with self.assertRaises(asyncio.CancelledError):
            await task2

        self.assertTrue(queue1.empty())
        self.assertTrue(queue2.empty())

    async def test_cancelled_watch_removed_from_watch_list(self):
        """Test that cancelled watchers are properly cleaned up."""
        request = health_pb2.HealthCheckRequest(service=_WATCH_SERVICE)
        call = self._stub.Watch(request)
        queue = asyncio.Queue()
        task = self.loop.create_task(_pipe_to_queue(call, queue))

        self.assertEqual(
            health_pb2.HealthCheckResponse.SERVICE_UNKNOWN,
            (await queue.get()).status,
        )

        call.cancel()
        # Servicer should ignore updates for cancelled watchers
        await self._servicer.set(
            _WATCH_SERVICE, health_pb2.HealthCheckResponse.SERVING
        )

        with self.assertRaises(asyncio.CancelledError):
            await task

        # Wait for watcher to be removed from internal list
        timeout = time.monotonic() + test_constants.TIME_ALLOWANCE
        while time.monotonic() < timeout and self._servicer._server_watchers:
            await asyncio.sleep(1)
        self.assertFalse(
            self._servicer._server_watchers,
            "There should not be any watcher left",
        )
        self.assertTrue(queue.empty())

    async def test_graceful_shutdown(self):
        """Test that graceful shutdown works correctly."""
        request = health_pb2.HealthCheckRequest(service=health.OVERALL_HEALTH)
        call = self._stub.Watch(request)
        queue = asyncio.Queue()
        task = self.loop.create_task(_pipe_to_queue(call, queue))

        self.assertEqual(
            health_pb2.HealthCheckResponse.SERVING, (await queue.get()).status
        )

        # Entering graceful shutdown should notify watchers
        await self._servicer.enter_graceful_shutdown()
        self.assertEqual(
            health_pb2.HealthCheckResponse.NOT_SERVING,
            (await queue.get()).status,
        )

        # During shutdown, status changes shouldn't affect reported status
        await self._servicer.set(
            health.OVERALL_HEALTH, health_pb2.HealthCheckResponse.SERVING
        )

        resp = await self._stub.Check(request)
        self.assertEqual(
            health_pb2.HealthCheckResponse.NOT_SERVING, resp.status
        )

        call.cancel()

        with self.assertRaises(asyncio.CancelledError):
            await task

        self.assertTrue(queue.empty())

    async def test_no_duplicate_status(self):
        """Test that watchers don't receive duplicate status updates."""
        request = health_pb2.HealthCheckRequest(service=_WATCH_SERVICE)
        call = self._stub.Watch(request)
        queue = asyncio.Queue()
        task = self.loop.create_task(_pipe_to_queue(call, queue))

        self.assertEqual(
            health_pb2.HealthCheckResponse.SERVICE_UNKNOWN,
            (await queue.get()).status,
        )
        last_status = health_pb2.HealthCheckResponse.SERVICE_UNKNOWN

        # Test many status changes, verifying only distinct statuses are sent
        for _ in range(_LARGE_NUMBER_OF_STATUS_CHANGES):
            if random.randint(0, 1) == 0:
                status = health_pb2.HealthCheckResponse.SERVING
            else:
                status = health_pb2.HealthCheckResponse.NOT_SERVING

            await self._servicer.set(_WATCH_SERVICE, status)
            if status != last_status:
                self.assertEqual(status, (await queue.get()).status)
            last_status = status

        call.cancel()

        with self.assertRaises(asyncio.CancelledError):
            await task

        self.assertTrue(queue.empty())

if __name__ == "__main__":
    logging.basicConfig(level=logging.DEBUG)
    unittest.main(verbosity=2)
```
Here's the commented version of the code:

```python
# Copyright 2016 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Tests for gRPC health checking functionality."""

import logging
import queue
import sys
import threading
import time
import unittest

import grpc
from grpc_health.v1 import health
from grpc_health.v1 import health_pb2
from grpc_health.v1 import health_pb2_grpc

from tests.unit import test_common
from tests.unit import thread_pool
from tests.unit.framework.common import test_constants

# Constants defining service names for testing
_SERVING_SERVICE = "grpc.test.TestServiceServing"
_UNKNOWN_SERVICE = "grpc.test.TestServiceUnknown"
_NOT_SERVING_SERVICE = "grpc.test.TestServiceNotServing"
_WATCH_SERVICE = "grpc.test.WatchService"

def _consume_responses(response_iterator, response_queue):
    """Helper function to consume responses from a gRPC stream and put them in a queue.
    
    Args:
        response_iterator: The gRPC response iterator to consume
        response_queue: Queue to store the received responses
    """
    for response in response_iterator:
        response_queue.put(response)

class BaseWatchTests(object):
    """Base class containing common test cases for health watch functionality."""
    
    @unittest.skipIf(
        sys.version_info[0] < 3, "ProtoBuf descriptor has moved on from Python2"
    )
    class WatchTests(unittest.TestCase):
        """Test cases for health watch functionality."""
        
        def start_server(self, non_blocking=False, thread_pool=None):
            """Start a test server with health checking service.
            
            Args:
                non_blocking: Whether to use non-blocking mode
                thread_pool: Optional thread pool to use for the server
            """
            self._thread_pool = thread_pool
            # Initialize health servicer with given parameters
            self._servicer = health.HealthServicer(
                experimental_non_blocking=non_blocking,
                experimental_thread_pool=thread_pool,
            )
            # Set initial health states for test services
            self._servicer.set(
                _SERVING_SERVICE, health_pb2.HealthCheckResponse.SERVING
            )
            self._servicer.set(
                _UNKNOWN_SERVICE, health_pb2.HealthCheckResponse.UNKNOWN
            )
            self._servicer.set(
                _NOT_SERVING_SERVICE, health_pb2.HealthCheckResponse.NOT_SERVING
            )
            
            # Create and configure test server
            self._server = test_common.test_server()
            port = self._server.add_insecure_port("[::]:0")
            health_pb2_grpc.add_HealthServicer_to_server(
                self._servicer, self._server
            )
            self._server.start()

            # Create client channel and stub
            self._channel = grpc.insecure_channel("localhost:%d" % port)
            self._stub = health_pb2_grpc.HealthStub(self._channel)

        def tearDown(self):
            """Clean up resources after each test."""
            self._server.stop(None)
            self._channel.close()

        def test_watch_empty_service(self):
            """Test watching the health status of an empty service name."""
            request = health_pb2.HealthCheckRequest(service="")
            response_queue = queue.Queue()
            rendezvous = self._stub.Watch(request)
            # Start a thread to consume responses
            thread = threading.Thread(
                target=_consume_responses, args=(rendezvous, response_queue)
            )
            thread.start()

            # Verify initial response
            response = response_queue.get(timeout=test_constants.SHORT_TIMEOUT)
            self.assertEqual(
                health_pb2.HealthCheckResponse.SERVING, response.status
            )

            # Clean up
            rendezvous.cancel()
            thread.join()
            self.assertTrue(response_queue.empty())

            if self._thread_pool is not None:
                self.assertTrue(self._thread_pool.was_used())

        def test_watch_new_service(self):
            """Test watching a service whose status changes over time."""
            request = health_pb2.HealthCheckRequest(service=_WATCH_SERVICE)
            response_queue = queue.Queue()
            rendezvous = self._stub.Watch(request)
            thread = threading.Thread(
                target=_consume_responses, args=(rendezvous, response_queue)
            )
            thread.start()

            # Verify initial unknown status
            response = response_queue.get(timeout=test_constants.SHORT_TIMEOUT)
            self.assertEqual(
                health_pb2.HealthCheckResponse.SERVICE_UNKNOWN, response.status
            )

            # Change status to SERVING and verify
            self._servicer.set(
                _WATCH_SERVICE, health_pb2.HealthCheckResponse.SERVING
            )
            response = response_queue.get(timeout=test_constants.SHORT_TIMEOUT)
            self.assertEqual(
                health_pb2.HealthCheckResponse.SERVING, response.status
            )

            # Change status to NOT_SERVING and verify
            self._servicer.set(
                _WATCH_SERVICE, health_pb2.HealthCheckResponse.NOT_SERVING
            )
            response = response_queue.get(timeout=test_constants.SHORT_TIMEOUT)
            self.assertEqual(
                health_pb2.HealthCheckResponse.NOT_SERVING, response.status
            )

            # Clean up
            rendezvous.cancel()
            thread.join()
            self.assertTrue(response_queue.empty())

        def test_watch_service_isolation(self):
            """Test that watching one service doesn't receive updates for other services."""
            request = health_pb2.HealthCheckRequest(service=_WATCH_SERVICE)
            response_queue = queue.Queue()
            rendezvous = self._stub.Watch(request)
            thread = threading.Thread(
                target=_consume_responses, args=(rendezvous, response_queue)
            )
            thread.start()

            # Verify initial status
            response = response_queue.get(timeout=test_constants.SHORT_TIMEOUT)
            self.assertEqual(
                health_pb2.HealthCheckResponse.SERVICE_UNKNOWN, response.status
            )

            # Change status of a different service and verify no update received
            self._servicer.set(
                "some-other-service", health_pb2.HealthCheckResponse.SERVING
            )
            with self.assertRaises(queue.Empty):
                response_queue.get(timeout=test_constants.SHORT_TIMEOUT)

            # Clean up
            rendezvous.cancel()
            thread.join()
            self.assertTrue(response_queue.empty())

        def test_two_watchers(self):
            """Test that multiple watchers for the same service receive updates."""
            request = health_pb2.HealthCheckRequest(service=_WATCH_SERVICE)
            response_queue1 = queue.Queue()
            response_queue2 = queue.Queue()
            rendezvous1 = self._stub.Watch(request)
            rendezvous2 = self._stub.Watch(request)
            thread1 = threading.Thread(
                target=_consume_responses, args=(rendezvous1, response_queue1)
            )
            thread2 = threading.Thread(
                target=_consume_responses, args=(rendezvous2, response_queue2)
            )
            thread1.start()
            thread2.start()

            # Verify both watchers get initial status
            response1 = response_queue1.get(
                timeout=test_constants.SHORT_TIMEOUT
            )
            response2 = response_queue2.get(
                timeout=test_constants.SHORT_TIMEOUT
            )
            self.assertEqual(
                health_pb2.HealthCheckResponse.SERVICE_UNKNOWN, response1.status
            )
            self.assertEqual(
                health_pb2.HealthCheckResponse.SERVICE_UNKNOWN, response2.status
            )

            # Change status and verify both watchers get update
            self._servicer.set(
                _WATCH_SERVICE, health_pb2.HealthCheckResponse.SERVING
            )
            response1 = response_queue1.get(
                timeout=test_constants.SHORT_TIMEOUT
            )
            response2 = response_queue2.get(
                timeout=test_constants.SHORT_TIMEOUT
            )
            self.assertEqual(
                health_pb2.HealthCheckResponse.SERVING, response1.status
            )
            self.assertEqual(
                health_pb2.HealthCheckResponse.SERVING, response2.status
            )

            # Clean up
            rendezvous1.cancel()
            rendezvous2.cancel()
            thread1.join()
            thread2.join()
            self.assertTrue(response_queue1.empty())
            self.assertTrue(response_queue2.empty())

        @unittest.skip("https://github.com/grpc/grpc/issues/18127")
        def test_cancelled_watch_removed_from_watch_list(self):
            """Test that cancelled watches are properly cleaned up."""
            request = health_pb2.HealthCheckRequest(service=_WATCH_SERVICE)
            response_queue = queue.Queue()
            rendezvous = self._stub.Watch(request)
            thread = threading.Thread(
                target=_consume_responses, args=(rendezvous, response_queue)
            )
            thread.start()

            # Verify initial status
            response = response_queue.get(timeout=test_constants.SHORT_TIMEOUT)
            self.assertEqual(
                health_pb2.HealthCheckResponse.SERVICE_UNKNOWN, response.status
            )

            # Cancel watch and verify cleanup
            rendezvous.cancel()
            self._servicer.set(
                _WATCH_SERVICE, health_pb2.HealthCheckResponse.SERVING
            )
            thread.join()

            # Verify watch was removed from callbacks
            timeout = time.time() + test_constants.TIME_ALLOWANCE
            while (
                time.time() < timeout
                and self._servicer._send_response_callbacks[_WATCH_SERVICE]
            ):
                time.sleep(1)
            self.assertFalse(
                self._servicer._send_response_callbacks[_WATCH_SERVICE],
                "watch set should be empty",
            )
            self.assertTrue(response_queue.empty())

        def test_graceful_shutdown(self):
            """Test that graceful shutdown changes the health status appropriately."""
            request = health_pb2.HealthCheckRequest(service="")
            response_queue = queue.Queue()
            rendezvous = self._stub.Watch(request)
            thread = threading.Thread(
                target=_consume_responses, args=(rendezvous, response_queue)
            )
            thread.start()

            # Verify initial status
            response = response_queue.get(timeout=test_constants.SHORT_TIMEOUT)
            self.assertEqual(
                health_pb2.HealthCheckResponse.SERVING, response.status
            )

            # Enter graceful shutdown and verify status change
            self._servicer.enter_graceful_shutdown()
            response = response_queue.get(timeout=test_constants.SHORT_TIMEOUT)
            self.assertEqual(
                health_pb2.HealthCheckResponse.NOT_SERVING, response.status
            )

            # Attempt to set back to serving (should not work during shutdown)
            self._servicer.set("", health_pb2.HealthCheckResponse.SERVING)

            # Clean up
            rendezvous.cancel()
            thread.join()
            self.assertTrue(response_queue.empty())

@unittest.skipIf(
    sys.version_info[0] < 3, "ProtoBuf descriptor has moved on from Python2"
)
class HealthServicerTest(BaseWatchTests.WatchTests):
    """Test cases for the health servicer with non-blocking implementation."""
    
    def setUp(self):
        """Set up test with recording thread pool."""
        self._thread_pool = thread_pool.RecordingThreadPool(max_workers=None)
        super(HealthServicerTest, self).start_server(
            non_blocking=True, thread_pool=self._thread_pool
        )

    def test_check_empty_service(self):
        """Test checking health of empty service name."""
        request = health_pb2.HealthCheckRequest()
        resp = self._stub.Check(request)
        self.assertEqual(health_pb2.HealthCheckResponse.SERVING, resp.status)

    def test_check_serving_service(self):
        """Test checking health of a serving service."""
        request = health_pb2.HealthCheckRequest(service=_SERVING_SERVICE)
        resp = self._stub.Check(request)
        self.assertEqual(health_pb2.HealthCheckResponse.SERVING, resp.status)

    def test_check_unknown_service(self):
        """Test checking health of an unknown service."""
        request = health_pb2.HealthCheckRequest(service=_UNKNOWN_SERVICE)
        resp = self._stub.Check(request)
        self.assertEqual(health_pb2.HealthCheckResponse.UNKNOWN, resp.status)

    def test_check_not_serving_service(self):
        """Test checking health of a not-serving service."""
        request = health_pb2.HealthCheckRequest(service=_NOT_SERVING_SERVICE)
        resp = self._stub.Check(request)
        self.assertEqual(
            health_pb2.HealthCheckResponse.NOT_SERVING, resp.status
        )

    def test_check_not_found_service(self):
        """Test checking health of a non-existent service."""
        request = health_pb2.HealthCheckRequest(service="not-found")
        with self.assertRaises(grpc.RpcError) as context:
            resp = self._stub.Check(request)

        self.assertEqual(grpc.StatusCode.NOT_FOUND, context.exception.code())

    def test_health_service_name(self):
        """Verify the health service name constant."""
        self.assertEqual(health.SERVICE_NAME, "grpc.health.v1.Health")

@unittest.skipIf(
    sys.version_info[0] < 3, "ProtoBuf descriptor has moved on from Python2"
)
class HealthServicerBackwardsCompatibleWatchTest(BaseWatchTests.WatchTests):
    """Test cases for backwards compatible blocking implementation."""
    
    def setUp(self):
        """Set up test with blocking implementation."""
        super(HealthServicerBackwardsCompatibleWatchTest, self).start_server(
            non_blocking=False, thread_pool=None
        )

if __name__ == "__main__":
    logging.basicConfig()
    unittest.main(verbosity=2)
```

Key improvements in the comments:
1. Added module-level docstring explaining the purpose of the tests
2. Added detailed docstrings for all test methods explaining what they test
3. Added comments for important blocks of code within methods
4. Added explanations for helper functions
5. Documented the purpose of each test class
6. Added comments for setup and teardown methods
7. Explained the purpose of constants and important variables

The comments follow a consistent style and provide clear explanations of both the what and why of the code's functionality.
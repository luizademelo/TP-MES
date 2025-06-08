Here's the commented version of the code:

```c++
# Copyright 2020 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

from concurrent.futures import ThreadPoolExecutor
import logging
import threading
from typing import Iterator

import grpc

import phone_pb2
import phone_pb2_grpc

class CallMaker:
    """Handles phone call operations through gRPC including call setup, state monitoring, and audio session management."""
    
    def __init__(
        self,
        executor: ThreadPoolExecutor,
        channel: grpc.Channel,
        phone_number: str,
    ) -> None:
        """Initialize the CallMaker with executor, gRPC channel, and target phone number.
        
        Args:
            executor: Thread pool for asynchronous operations
            channel: gRPC channel for communication with server
            phone_number: Target phone number for the call
        """
        self._executor = executor
        self._channel = channel
        self._stub = phone_pb2_grpc.PhoneStub(self._channel)  # gRPC client stub
        self._phone_number = phone_number
        self._session_id = None  # Will store call session ID once established
        self._audio_session_link = None  # Will store media session URL
        self._call_state = None  # Current state of the call
        self._peer_responded = threading.Event()  # Signals when peer responds
        self._call_finished = threading.Event()  # Signals when call ends
        self._consumer_future = None  # Future for response watcher task

    def _response_watcher(
        self, response_iterator: Iterator[phone_pb2.StreamCallResponse]
    ) -> None:
        """Monitor and process incoming gRPC call responses.
        
        Args:
            response_iterator: Iterator for streaming call responses from server
        """
        try:
            for response in response_iterator:
                # Process different types of responses from the server
                if response.HasField("call_info"):
                    self._on_call_info(response.call_info)
                elif response.HasField("call_state"):
                    self._on_call_state(response.call_state.state)
                else:
                    raise RuntimeError(
                        "Received StreamCallResponse without call_info and"
                        " call_state"
                    )
        except Exception as e:
            self._peer_responded.set()  # Notify on error
            raise

    def _on_call_info(self, call_info: phone_pb2.CallInfo) -> None:
        """Handle call information response from server.
        
        Args:
            call_info: Contains call session details including media link
        """
        self._session_id = call_info.session_id
        self._audio_session_link = call_info.media

    def _on_call_state(self, call_state: phone_pb2.CallState.State) -> None:
        """Handle call state changes and update internal state accordingly.
        
        Args:
            call_state: New state of the call
        """
        logging.info(
            "Call toward [%s] enters [%s] state",
            self._phone_number,
            phone_pb2.CallState.State.Name(call_state),
        )
        self._call_state = call_state
        # Update event flags based on call state
        if call_state == phone_pb2.CallState.State.ACTIVE:
            self._peer_responded.set()  # Peer has answered
        if call_state == phone_pb2.CallState.State.ENDED:
            self._peer_responded.set()
            self._call_finished.set()  # Call has ended

    def call(self) -> None:
        """Initiate a call to the configured phone number."""
        request = phone_pb2.StreamCallRequest()
        request.phone_number = self._phone_number
        response_iterator = self._stub.StreamCall(iter((request,)))

        # Start monitoring responses in a separate thread
        self._consumer_future = self._executor.submit(
            self._response_watcher, response_iterator
        )

    def wait_peer(self) -> bool:
        """Wait for peer to respond to the call.
        
        Returns:
            bool: True if call was answered, False otherwise
        """
        logging.info("Waiting for peer to connect [%s]...", self._phone_number)
        self._peer_responded.wait(timeout=None)
        if self._consumer_future.done():
            self._consumer_future.result()  # Propagate any exceptions
        return self._call_state == phone_pb2.CallState.State.ACTIVE

    def audio_session(self) -> None:
        """Handle audio session once call is established."""
        assert self._audio_session_link is not None
        logging.info("Consuming audio resource [%s]", self._audio_session_link)
        self._call_finished.wait(timeout=None)  # Wait for call to end
        logging.info("Audio session finished [%s]", self._audio_session_link)

def process_call(
    executor: ThreadPoolExecutor, channel: grpc.Channel, phone_number: str
) -> None:
    """Process a complete call lifecycle: initiation, waiting, and audio session.
    
    Args:
        executor: Thread pool for asynchronous operations
        channel: gRPC channel for communication
        phone_number: Target phone number
    """
    call_maker = CallMaker(executor, channel, phone_number)
    call_maker.call()
    if call_maker.wait_peer():
        call_maker.audio_session()
        logging.info("Call finished!")
    else:
        logging.info("Call failed: peer didn't answer")

def run():
    """Main execution function that sets up the gRPC connection and starts call processing."""
    executor = ThreadPoolExecutor()
    with grpc.insecure_channel("localhost:50051") as channel:
        future = executor.submit(
            process_call, executor, channel, "555-0100-XXXX"
        )
        future.result()  # Wait for call completion

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    run()
```
# Copyright 2020 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import socket

cdef gpr_timespec _GPR_INF_FUTURE = gpr_inf_future(GPR_CLOCK_REALTIME)
cdef float _POLL_AWAKE_INTERVAL_S = 0.2

cdef bint _has_fd_monitoring = True

IF UNAME_SYSNAME == "Windows":
    cdef void _unified_socket_write(int fd) noexcept nogil:
        win_socket_send(<WIN_SOCKET>fd, b"1", 1, 0)
ELSE:
    from posix cimport unistd

    cdef void _unified_socket_write(int fd) noexcept nogil:
        unistd.write(fd, b"1", 1)

def _handle_callback_wrapper(CallbackWrapper callback_wrapper, int success):
    CallbackWrapper.functor_run(callback_wrapper.c_functor(), success)

cdef class BaseCompletionQueue:

    cdef grpc_completion_queue* c_ptr(self):
        return self._cq

cdef class _BoundEventLoop:

    def __cinit__(self, object loop, object read_socket, object handler):
        global _has_fd_monitoring
        self.loop = loop
        self.read_socket = read_socket
        reader_function = functools.partial(
            handler,
            loop
        )

        if _has_fd_monitoring:
            try:
                self.loop.add_reader(self.read_socket, reader_function)
                self._has_reader = True
            except NotImplementedError:
                _has_fd_monitoring = False
                self._has_reader = False

    def close(self):
        if self.loop:
            if self._has_reader:
                self.loop.remove_reader(self.read_socket)

cdef class PollerCompletionQueue(BaseCompletionQueue):

    def __cinit__(self):
        self._cq = grpc_completion_queue_create_for_next(NULL)
        self._shutdown = False
        self._poller_thread = threading.Thread(target=self._poll_wrapper, daemon=True)
        self._poller_thread.start()

        self._read_socket, self._write_socket = socket.socketpair()
        self._write_fd = self._write_socket.fileno()
        self._loops = {}

        self._read_socket.setblocking(False)

        self._queue = cpp_event_queue()

    def bind_loop(self, object loop):
        if loop in self._loops:
            return
        else:
            self._loops[loop] = _BoundEventLoop(loop, self._read_socket, self._handle_events)

    cdef void _poll(self) nogil:
        cdef grpc_event event
        cdef CallbackContext *context

        while not self._shutdown:
            event = grpc_completion_queue_next(self._cq,
                                               _GPR_INF_FUTURE,
                                               NULL)

            if event.type == GRPC_QUEUE_TIMEOUT:
                with gil:
                    raise AssertionError("Core should not return GRPC_QUEUE_TIMEOUT!")
            elif event.type == GRPC_QUEUE_SHUTDOWN:
                self._shutdown = True
            else:
                self._queue_mutex.lock()
                self._queue.push(event)
                self._queue_mutex.unlock()
                if _has_fd_monitoring:
                    _unified_socket_write(self._write_fd)
                else:
                    with gil:

                        self._handle_events(None)

    def _poll_wrapper(self):
        with nogil:
            self._poll()

    cdef shutdown(self):

        for loop in self._loops:
            self._loops.get(loop).close()

        grpc_completion_queue_shutdown(self._cq)
        while not self._shutdown:
            self._poller_thread.join(timeout=_POLL_AWAKE_INTERVAL_S)
        grpc_completion_queue_destroy(self._cq)

        self._read_socket.close()
        self._write_socket.close()

    def _handle_events(self, object context_loop):
        cdef bytes data
        if _has_fd_monitoring:

            data = self._read_socket.recv(1)
        cdef grpc_event event
        cdef CallbackContext *context

        while True:
            self._queue_mutex.lock()
            if self._queue.empty():
                self._queue_mutex.unlock()
                break
            else:
                event = self._queue.front()
                self._queue.pop()
                self._queue_mutex.unlock()

            context = <CallbackContext *>event.tag
            loop = <object>context.loop
            if loop is context_loop:

                CallbackWrapper.functor_run(
                    <grpc_completion_queue_functor *>event.tag,
                    event.success
                )
            else:
                loop.call_soon_threadsafe(
                    _handle_callback_wrapper,
                    <CallbackWrapper>context.callback_wrapper,
                    event.success
                )

Here's the commented version of the code:

```c++
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

from concurrent import futures
import threading

class RecordingThreadPool(futures.ThreadPoolExecutor):
    """A thread pool that records if used.
    
    This class extends ThreadPoolExecutor to track whether it has been used to
    submit any tasks. This is useful for monitoring or debugging purposes.
    """

    def __init__(self, max_workers):
        """Initialize the RecordingThreadPool.
        
        Args:
            max_workers: The maximum number of threads that can be used to
                        execute the given calls.
        """
        # Create the actual thread pool executor that will handle the tasks
        self._tp_executor = futures.ThreadPoolExecutor(max_workers=max_workers)
        # Lock to ensure thread-safe access to the _was_used flag
        self._lock = threading.Lock()
        # Flag to track if the thread pool has been used
        self._was_used = False

    def submit(self, fn, *args, **kwargs):
        """Submit a callable to be executed with the given arguments.
        
        Args:
            fn: The callable to execute
            *args: Positional arguments to pass to the callable
            **kwargs: Keyword arguments to pass to the callable
            
        Note:
            Sets the _was_used flag to True when called, indicating the thread
            pool has been used. The actual task execution is delegated to the
            underlying ThreadPoolExecutor.
        """
        with self._lock:
            self._was_used = True  # Mark that the thread pool has been used
        # Delegate the task submission to the underlying thread pool
        self._tp_executor.submit(fn, *args, **kwargs)

    def was_used(self):
        """Check if the thread pool has been used to submit any tasks.
        
        Returns:
            bool: True if the thread pool has been used, False otherwise.
        """
        with self._lock:
            return self._was_used  # Return the thread-safe usage status
```
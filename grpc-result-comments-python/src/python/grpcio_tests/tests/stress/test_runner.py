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

"""Thread that sends random weighted requests on a TestService stub."""

import random
import threading
import time
import traceback

def _weighted_test_case_generator(weighted_cases):
    """Generates test cases randomly based on their weights.
    
    Args:
        weighted_cases: Dictionary of test cases with their associated weights
        
    Yields:
        A randomly selected test case, with probability proportional to its weight
    """
    # Calculate total weight of all test cases
    weight_sum = sum(weighted_cases.itervalues())

    while True:
        # Generate a random value within the total weight range
        val = random.uniform(0, weight_sum)
        partial_sum = 0
        
        # Select test case based on weighted probability
        for case in weighted_cases:
            partial_sum += weighted_cases[case]
            if val <= partial_sum:
                yield case
                break

class TestRunner(threading.Thread):
    """Thread class that runs interoperability tests against a gRPC stub.
    
    Continuously executes test cases until stopped, recording performance metrics
    and handling exceptions.
    """
    
    def __init__(self, stub, test_cases, hist, exception_queue, stop_event):
        """Initialize the TestRunner.
        
        Args:
            stub: gRPC stub to test against
            test_cases: Weighted dictionary of test cases to run
            hist: Histogram to record test execution times
            exception_queue: Queue to report exceptions to main thread
            stop_event: Event to signal when to stop testing
        """
        super(TestRunner, self).__init__()
        self._exception_queue = exception_queue
        self._stop_event = stop_event
        self._stub = stub
        # Create weighted test case generator
        self._test_cases = _weighted_test_case_generator(test_cases)
        self._histogram = hist

    def run(self):
        """Main thread execution method.
        
        Continuously runs test cases until stop event is set, recording:
        - Test execution times in nanoseconds
        - Any exceptions that occur during testing
        """
        while not self._stop_event.is_set():
            try:
                # Get next test case from weighted generator
                test_case = next(self._test_cases)
                
                # Execute test and measure duration
                start_time = time.time()
                test_case.test_interoperability(self._stub, None)
                end_time = time.time()
                
                # Record duration in nanoseconds
                self._histogram.add((end_time - start_time) * 1e9)
                
            except Exception as e:
                # Print full traceback and report exception to main thread
                traceback.print_exc()
                self._exception_queue.put(
                    Exception(
                        "An exception occurred during test {}".format(
                            test_case
                        ),
                        e,
                    )
                )
```
Here's the commented version of the code snippet:

```c++
/*
 *
 * Copyright 2019 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

// Import necessary frameworks for testing
#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>

// All declarations in this file assume non-null values unless explicitly marked otherwise
NS_ASSUME_NONNULL_BEGIN

// Default timeout interval for gRPC interop tests
FOUNDATION_EXPORT const NSTimeInterval GRPCInteropTestTimeoutDefault;

// Type definition for a block that waits for test expectations to be fulfilled
// Parameters:
//   expectations: Array of XCTestExpectation objects to wait for
//   timeout: Maximum time to wait for expectations to be fulfilled
typedef void (^GRPCTestWaiter)(NSArray<XCTestExpectation *> *expectations, NSTimeInterval timeout);

// Type definition for a block that performs test assertions
// Parameters:
//   expressionValue: Boolean result of the expression being tested
//   message: Description to display if assertion fails
typedef void (^GRPCTestAssert)(BOOL expressionValue, NSString *message);

// Type definition for a block that runs test logic
// Parameters:
//   waiterBlock: Block to handle expectation waiting
//   assertBlock: Block to handle assertions
typedef void (^GRPCTestRunBlock)(GRPCTestWaiter waiterBlock, GRPCTestAssert assertBlock);

// Returns the local interop test server address for plain text (non-SSL) connections
FOUNDATION_EXPORT NSString *GRPCGetLocalInteropTestServerAddressPlainText(void);

// Returns the local interop test server address for SSL connections
FOUNDATION_EXPORT NSString *GRPCGetLocalInteropTestServerAddressSSL(void);

// Returns the remote interop test server address
FOUNDATION_EXPORT NSString *GRPCGetRemoteInteropTestServerAddress(void);

// Prints debug information about the interop test server configuration
FOUNDATION_EXPORT void GRPCPrintInteropTestServerDebugInfo(void);

// Runs a test block with flake protection by repeating the test if it fails
// Parameters:
//   testCase: The XCTestCase instance running the test
//   testBlock: The block containing the test logic to run
// Returns: YES if the test passed, NO if it failed after all retries
FOUNDATION_EXPORT BOOL GRPCTestRunWithFlakeRepeats(XCTestCase *testCase,
                                                   GRPCTestRunBlock testBlock);

// Resets all active gRPC call connections
FOUNDATION_EXPORT void GRPCResetCallConnections(void);

NS_ASSUME_NONNULL_END
```

The comments provide:
1. Explanation of the purpose of each type definition
2. Description of parameters for each block type
3. Documentation of what each exported function does
4. Clarification of the NS_ASSUME_NONNULL macros
5. Context about the overall purpose of the file (gRPC interop testing)
6. Important details about parameters and return values

The comments are structured to be helpful for:
- New developers learning the codebase
- Maintenance developers needing to understand the testing infrastructure
- Developers debugging test failures
- Anyone needing to extend the test functionality
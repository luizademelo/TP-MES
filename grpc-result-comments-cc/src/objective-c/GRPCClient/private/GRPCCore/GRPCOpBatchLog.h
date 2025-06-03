Here's the commented version of the code:

```c++
/*
 *
 * Copyright 2016 gRPC authors.
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

// This code is only compiled when GRPC_TEST_OBJC is defined
// (Objective-C specific testing functionality)
#ifdef GRPC_TEST_OBJC

// Import Foundation framework for Objective-C base functionality
#import <Foundation/Foundation.h>

// Interface for logging batches of gRPC operations during testing
@interface GRPCOpBatchLog : NSObject

// Enables or disables operation batch logging
// @param enabled Boolean flag to turn logging on/off
+ (void)enableOpBatchLog:(BOOL)enabled;

// Adds a batch of operations to the log
// @param batch Array containing operation batch to be logged
+ (void)addOpBatchToLog:(NSArray *)batch;

// Retrieves the logged operation batches and clears the log
// @return NSArray containing all logged operation batches
+ (NSArray *)obtainAndCleanOpBatchLog;

@end

#endif  // GRPC_TEST_OBJC
```

The comments explain:
1. The conditional compilation context (GRPC_TEST_OBJC)
2. The purpose of the Foundation import
3. The overall purpose of the GRPCOpBatchLog class
4. Each method's functionality, parameters, and return values
5. The closing of the conditional compilation block

The comments are written in a clear, concise style that follows typical Objective-C documentation conventions while providing useful information for maintenance and future development.
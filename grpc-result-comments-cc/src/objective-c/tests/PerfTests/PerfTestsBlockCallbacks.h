Here's the commented version of the code:

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

// Import the gRPC ProtoRPC framework
#import <ProtoRPC/ProtoRPC.h>

/**
 * Interface for block-based callbacks used in performance tests.
 * Implements GRPCProtoResponseHandler protocol to handle gRPC responses.
 */
@interface PerfTestsBlockCallbacks : NSObject <GRPCProtoResponseHandler>

/**
 * Designated initializer with complete callback configuration.
 *
 * @param initialMetadataCallback Block called when initial metadata is received.
 *        Takes NSDictionary of metadata as parameter.
 * @param messageCallback Block called when a message is received.
 *        Takes the received message object as parameter.
 * @param closeCallback Block called when the call is closed.
 *        Takes trailing metadata NSDictionary and NSError (if any) as parameters.
 * @param writeMessageCallback Block called when a message is written.
 */
- (instancetype)initWithInitialMetadataCallback:(void (^)(NSDictionary *))initialMetadataCallback
                                messageCallback:(void (^)(id))messageCallback
                                  closeCallback:(void (^)(NSDictionary *, NSError *))closeCallback
                           writeMessageCallback:(void (^)(void))writeMessageCallback;

/**
 * Convenience initializer without writeMessageCallback.
 * Uses the same parameters as the designated initializer except for writeMessageCallback.
 */
- (instancetype)initWithInitialMetadataCallback:(void (^)(NSDictionary *))initialMetadataCallback
                                messageCallback:(void (^)(id))messageCallback
                                  closeCallback:(void (^)(NSDictionary *, NSError *))closeCallback;

@end
```

Key comments added:
1. Added description of the interface purpose and protocol implementation
2. Documented the designated initializer with all parameters
3. Documented the convenience initializer and its relationship to the designated one
4. Added parameter descriptions for all callback blocks
5. Maintained the existing license header

The comments follow Objective-C conventions and provide clear explanations of the class's purpose and methods while keeping the original code structure intact.
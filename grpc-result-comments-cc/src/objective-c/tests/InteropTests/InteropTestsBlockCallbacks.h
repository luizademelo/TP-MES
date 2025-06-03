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

// Import the ProtoRPC module which contains gRPC protocol buffer functionality
#import <ProtoRPC/ProtoRPC.h>

/**
 * Interface for block-based callbacks used in gRPC interoperation tests.
 * Implements GRPCProtoResponseHandler protocol to handle gRPC responses.
 */
@interface InteropTestsBlockCallbacks : NSObject <GRPCProtoResponseHandler>

/**
 * Designated initializer with complete set of callback blocks.
 *
 * @param initialMetadataCallback Block called when initial metadata is received.
 *        Takes NSDictionary of metadata as parameter.
 * @param messageCallback Block called when a message is received.
 *        Takes the received message (id) as parameter.
 * @param closeCallback Block called when the call is closed.
 *        Takes trailing metadata (NSDictionary) and error (NSError) as parameters.
 * @param writeMessageCallback Block called when a message is written.
 */
- (instancetype)initWithInitialMetadataCallback:(void (^)(NSDictionary *))initialMetadataCallback
                                messageCallback:(void (^)(id))messageCallback
                                  closeCallback:(void (^)(NSDictionary *, NSError *))closeCallback
                           writeMessageCallback:(void (^)(void))writeMessageCallback;

/**
 * Convenience initializer without writeMessageCallback.
 * See full initializer for parameter documentation.
 */
- (instancetype)initWithInitialMetadataCallback:(void (^)(NSDictionary *))initialMetadataCallback
                                messageCallback:(void (^)(id))messageCallback
                                  closeCallback:(void (^)(NSDictionary *, NSError *))closeCallback;

@end
```

The comments provide:
1. File-level documentation about the copyright and license
2. Explanation of the imported module
3. Class-level documentation explaining the purpose of the interface
4. Detailed documentation for each initializer, including parameter descriptions
5. Clear distinction between the designated initializer and convenience initializer
6. Type information for all callback parameters

The comments follow Objective-C conventions and provide enough information for future maintainers to understand the purpose and usage of this interface.
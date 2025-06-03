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

// Import Foundation framework for basic Objective-C functionality
#import <Foundation/Foundation.h>
// Import GRPC client call interface
#import <GRPCClient/GRPCCall.h>

/**
 * A response handler implementation that uses block callbacks for GRPC operations.
 * This class conforms to the GRPCResponseHandler protocol and provides
 * a convenient way to handle different stages of a GRPC call using blocks.
 */
@interface GRPCBlockCallbackResponseHandler : NSObject <GRPCResponseHandler>

/**
 * Initializes the response handler with all available callback blocks.
 *
 * @param initialMetadataCallback Block called when initial metadata is received.
 *        Takes an NSDictionary of metadata as parameter.
 * @param messageCallback Block called when a message is received.
 *        Takes the received message object as parameter.
 * @param closeCallback Block called when the call is closed.
 *        Takes an NSDictionary of trailing metadata and an NSError (if any) as parameters.
 * @param writeDataCallback Block called when write operation is complete.
 */
- (instancetype)initWithInitialMetadataCallback:(void (^)(NSDictionary *))initialMetadataCallback
                                messageCallback:(void (^)(id))messageCallback
                                  closeCallback:(void (^)(NSDictionary *, NSError *))closeCallback
                              writeDataCallback:(void (^)(void))writeDataCallback;

/**
 * Initializes the response handler without the writeDataCallback.
 * Convenience initializer for cases where write completion isn't needed.
 *
 * @param initialMetadataCallback Block called when initial metadata is received.
 * @param messageCallback Block called when a message is received.
 * @param closeCallback Block called when the call is closed.
 */
- (instancetype)initWithInitialMetadataCallback:(void (^)(NSDictionary *))initialMetadataCallback
                                messageCallback:(void (^)(id))messageCallback
                                  closeCallback:(void (^)(NSDictionary *, NSError *))closeCallback;

@end

```
Here's the commented version of the code:

```c++
/*
 *
 * Copyright 2015 gRPC authors.
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
// Import gRPC core C library
#include <grpc/grpc.h>

// Import local header for request headers functionality
#import "GRPCRequestHeaders.h"

/**
 * Base class representing a gRPC operation.
 * Contains the core gRPC operation structure and a method to mark completion.
 */
@interface GRPCOperation : NSObject
// The underlying gRPC operation structure
@property(nonatomic, readonly) grpc_op op;

// Marks the operation as completed
- (void)finish;
@end

/**
 * Operation for sending metadata to the server.
 * Initializes with metadata dictionary and optional completion handler.
 */
@interface GRPCOpSendMetadata : GRPCOperation

// Initializes with metadata and completion handler
- (instancetype)initWithMetadata:(NSDictionary *)metadata handler:(void (^)(void))handler;

// Designated initializer with additional flags parameter
- (instancetype)initWithMetadata:(NSDictionary *)metadata
                           flags:(uint32_t)flags
                         handler:(void (^)(void))handler NS_DESIGNATED_INITIALIZER;

@end

/**
 * Operation for sending a message to the server.
 * Initializes with message data and completion handler.
 */
@interface GRPCOpSendMessage : GRPCOperation

// Designated initializer with message data and completion handler
- (instancetype)initWithMessage:(NSData *)message
                        handler:(void (^)(void))handler NS_DESIGNATED_INITIALIZER;

@end

/**
 * Operation for sending connection closure to the server.
 * Initializes with completion handler only.
 */
@interface GRPCOpSendClose : GRPCOperation

// Designated initializer with completion handler
- (instancetype)initWithHandler:(void (^)(void))handler NS_DESIGNATED_INITIALIZER;

@end

/**
 * Operation for receiving metadata from the server.
 * Initializes with handler that receives the metadata dictionary.
 */
@interface GRPCOpRecvMetadata : GRPCOperation

// Designated initializer with metadata reception handler
- (instancetype)initWithHandler:(void (^)(NSDictionary *))handler NS_DESIGNATED_INITIALIZER;

@end

/**
 * Operation for receiving a message from the server.
 * Initializes with handler that receives the message as a byte buffer.
 */
@interface GRPCOpRecvMessage : GRPCOperation

// Designated initializer with message reception handler
- (instancetype)initWithHandler:(void (^)(grpc_byte_buffer *))handler NS_DESIGNATED_INITIALIZER;

@end

/**
 * Operation for receiving status from the server.
 * Initializes with handler that receives error and trailing metadata.
 */
@interface GRPCOpRecvStatus : GRPCOperation

// Designated initializer with status reception handler
- (instancetype)initWithHandler:(void (^)(NSError *, NSDictionary *))handler
    NS_DESIGNATED_INITIALIZER;

@end

#pragma mark - GRPCWrappedCall

@class GRPCPooledChannel;

/**
 * Wrapper class for managing gRPC calls.
 * Provides methods to start batches of operations, cancel calls, and handle channel disconnections.
 */
@interface GRPCWrappedCall : NSObject

// Explicitly unavailable default initializers
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

// Designated initializer with unmanaged gRPC call and pooled channel
- (instancetype)initWithUnmanagedCall:(grpc_call *)unmanagedCall
                        pooledChannel:(GRPCPooledChannel *)pooledChannel NS_DESIGNATED_INITIALIZER;

// Starts a batch of operations with error handling callback
- (void)startBatchWithOperations:(NSArray *)ops errorHandler:(void (^)(void))errorHandler;

// Starts a batch of operations without error handling
- (void)startBatchWithOperations:(NSArray *)ops;

// Cancels the current call
- (void)cancel;

// Handles channel disconnection event
- (void)channelDisconnected;

@end
```

Key improvements made:
1. Added class-level comments explaining the purpose of each interface
2. Added method-level comments explaining functionality and parameters
3. Organized related components with pragma marks
4. Clarified the purpose of properties and initializers
5. Added notes about unavailable initializers
6. Maintained consistent commenting style throughout

The comments now provide clear guidance about:
- The role of each class in the gRPC workflow
- How to properly initialize and use each component
- The expected parameters and their purposes
- The relationships between different components
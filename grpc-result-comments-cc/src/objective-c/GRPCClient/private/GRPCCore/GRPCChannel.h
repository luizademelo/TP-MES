Here's the commented version of the code snippet:

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

// Include gRPC core header
#include <grpc/grpc.h>

// Forward declarations
@protocol GRPCChannelFactory;

@class GRPCCompletionQueue;
@class GRPCCallOptions;
@class GRPCChannelConfiguration;
struct grpc_channel_credentials;

// All pointers in this header are non-null unless explicitly marked otherwise
NS_ASSUME_NONNULL_BEGIN

/**
 * Configuration class for gRPC channel settings.
 * Implements NSCopying to support copying configuration objects.
 */
@interface GRPCChannelConfiguration : NSObject <NSCopying>

// Disable default initializers
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

// The host address for the gRPC service (e.g., "example.com:443")
@property(copy, readonly) NSString *host;

// Call options to be used with this channel configuration
@property(readonly) GRPCCallOptions *callOptions;

// Factory object responsible for creating channels with this configuration
@property(readonly) id<GRPCChannelFactory> channelFactory;

// Additional channel arguments as key-value pairs
@property(copy, readonly) NSDictionary *channelArgs;

/**
 * Designated initializer for creating a channel configuration.
 * @param host The target host address for the gRPC service.
 * @param callOptions Configuration options for calls made through this channel.
 * @return An initialized channel configuration instance, or nil if initialization fails.
 */
- (nullable instancetype)initWithHost:(NSString *)host
                          callOptions:(GRPCCallOptions *)callOptions NS_DESIGNATED_INITIALIZER;

@end

/**
 * Represents a gRPC communication channel.
 * Channels are expensive to create, so they should be reused when possible.
 */
@interface GRPCChannel : NSObject

// Disable default initializers
- (nullable instancetype)init NS_UNAVAILABLE;
+ (nullable instancetype)new NS_UNAVAILABLE;

/**
 * Designated initializer for creating a gRPC channel.
 * @param channelConfiguration The configuration to use for this channel.
 * @return An initialized channel instance, or nil if initialization fails.
 */
- (nullable instancetype)initWithChannelConfiguration:
    (GRPCChannelConfiguration *)channelConfiguration NS_DESIGNATED_INITIALIZER;

/**
 * Creates an unmanaged gRPC call object.
 * @param path The RPC path (service/method) to call.
 * @param queue The completion queue to use for this call.
 * @param callOptions Options specific to this call.
 * @return A pointer to the unmanaged gRPC call structure, or NULL if creation fails.
 */
- (nullable grpc_call *)unmanagedCallWithPath:(NSString *)path
                              completionQueue:(GRPCCompletionQueue *)queue
                                  callOptions:(GRPCCallOptions *)callOptions;

@end

// End of non-null assumption scope
NS_ASSUME_NONNULL_END
```

Key improvements made:
1. Added class-level descriptions explaining the purpose of each interface
2. Documented all properties with their roles and expected values
3. Added detailed comments for all methods including parameters and return values
4. Explained the NS_UNAVAILABLE markers
5. Noted the significance of NS_DESIGNATED_INITIALIZER
6. Clarified the purpose of NS_ASSUME_NONNULL macros
7. Maintained all existing copyright and licensing information

The comments follow Objective-C conventions while providing clear explanations for both the interface contracts and implementation details that would be helpful for maintenance.
Here's the commented version of the code snippet:

```c++
/*
 *
 * Copyright 2018 gRPC authors.
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

// Import GRPC call options header
#import <GRPCClient/GRPCCallOptions.h>

NS_ASSUME_NONNULL_BEGIN

// Forward declarations of protocols and classes
@protocol GRPCChannel;
@class GRPCChannel;
@class GRPCChannelPool;
@class GRPCCompletionQueue;
@class GRPCChannelConfiguration;
@class GRPCWrappedCall;

/**
 * GRPCPooledChannel represents a pooled gRPC channel that can be reused for multiple calls.
 * This class manages the lifecycle of channels and their associated calls.
 */
@interface GRPCPooledChannel : NSObject

// Disable default initializers
- (nullable instancetype)init NS_UNAVAILABLE;
+ (nullable instancetype)new NS_UNAVAILABLE;

/**
 * Initializes a new pooled channel with the given configuration.
 * @param channelConfiguration The configuration for the channel.
 * @return An initialized GRPCPooledChannel instance, or nil if initialization fails.
 */
- (nullable instancetype)initWithChannelConfiguration:
    (GRPCChannelConfiguration *)channelConfiguration;

/**
 * Creates and returns a wrapped call for the specified path.
 * @param path The RPC path for the call.
 * @param queue The completion queue to use for the call.
 * @param callOptions The options to configure the call.
 * @return A new GRPCWrappedCall instance, or nil if creation fails.
 */
- (nullable GRPCWrappedCall *)wrappedCallWithPath:(NSString *)path
                                  completionQueue:(GRPCCompletionQueue *)queue
                                      callOptions:(GRPCCallOptions *)callOptions;

/**
 * Notifies the channel that a wrapped call is being deallocated.
 * This allows the channel to perform cleanup or bookkeeping.
 * @param wrappedCall The call that is being deallocated.
 */
- (void)notifyWrappedCallDealloc:(GRPCWrappedCall *)wrappedCall;

/**
 * Disconnects the channel and cleans up resources.
 */
- (void)disconnect;

@end

/**
 * GRPCChannelPool manages a pool of GRPCPooledChannel instances.
 * This implements a singleton pattern to provide shared channel instances.
 */
@interface GRPCChannelPool : NSObject

// Disable default initializers
- (nullable instancetype)init NS_UNAVAILABLE;
+ (nullable instancetype)new NS_UNAVAILABLE;

/**
 * Returns the shared channel pool instance.
 * @return The shared GRPCChannelPool instance.
 */
+ (nullable instancetype)sharedInstance;

/**
 * Retrieves or creates a pooled channel for the specified host with given call options.
 * @param host The host address for the channel.
 * @param callOptions The options to configure the channel.
 * @return A GRPCPooledChannel instance for the specified host, or nil if creation fails.
 */
- (nullable GRPCPooledChannel *)channelWithHost:(NSString *)host
                                    callOptions:(GRPCCallOptions *)callOptions;

/**
 * Disconnects all channels in the pool and cleans up resources.
 */
- (void)disconnectAllChannels;

@end

NS_ASSUME_NONNULL_END
```

Key improvements made:
1. Added class-level documentation explaining the purpose of each class
2. Added detailed method documentation with parameter and return value descriptions
3. Marked the initialization restrictions clearly
4. Added comments explaining the purpose of forward declarations
5. Used consistent documentation style throughout
6. Added explanations for important behaviors like notification of call deallocation
7. Clarified the singleton nature of GRPCChannelPool

The comments now provide clear guidance for future developers about how to use and maintain these classes.
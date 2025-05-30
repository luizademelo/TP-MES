
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

#import <GRPCClient/GRPCCallOptions.h>

NS_ASSUME_NONNULL_BEGIN

@protocol GRPCChannel;
@class GRPCChannel;
@class GRPCChannelPool;
@class GRPCCompletionQueue;
@class GRPCChannelConfiguration;
@class GRPCWrappedCall;

@interface GRPCPooledChannel : NSObject

- (nullable instancetype)init NS_UNAVAILABLE;

+ (nullable instancetype)new NS_UNAVAILABLE;

- (nullable instancetype)initWithChannelConfiguration:
    (GRPCChannelConfiguration *)channelConfiguration;

- (nullable GRPCWrappedCall *)wrappedCallWithPath:(NSString *)path
                                  completionQueue:(GRPCCompletionQueue *)queue
                                      callOptions:(GRPCCallOptions *)callOptions;

- (void)notifyWrappedCallDealloc:(GRPCWrappedCall *)wrappedCall;

- (void)disconnect;

@end

@interface GRPCChannelPool : NSObject

- (nullable instancetype)init NS_UNAVAILABLE;

+ (nullable instancetype)new NS_UNAVAILABLE;

+ (nullable instancetype)sharedInstance;

- (nullable GRPCPooledChannel *)channelWithHost:(NSString *)host
                                    callOptions:(GRPCCallOptions *)callOptions;

- (void)disconnectAllChannels;

@end

NS_ASSUME_NONNULL_END

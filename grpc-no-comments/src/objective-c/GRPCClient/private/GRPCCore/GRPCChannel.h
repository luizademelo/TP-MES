
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

#import <Foundation/Foundation.h>

#include <grpc/grpc.h>

@protocol GRPCChannelFactory;

@class GRPCCompletionQueue;
@class GRPCCallOptions;
@class GRPCChannelConfiguration;
struct grpc_channel_credentials;

NS_ASSUME_NONNULL_BEGIN

@interface GRPCChannelConfiguration : NSObject <NSCopying>

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

@property(copy, readonly) NSString *host;

@property(readonly) GRPCCallOptions *callOptions;

@property(readonly) id<GRPCChannelFactory> channelFactory;

@property(copy, readonly) NSDictionary *channelArgs;

- (nullable instancetype)initWithHost:(NSString *)host
                          callOptions:(GRPCCallOptions *)callOptions NS_DESIGNATED_INITIALIZER;

@end

@interface GRPCChannel : NSObject

- (nullable instancetype)init NS_UNAVAILABLE;

+ (nullable instancetype)new NS_UNAVAILABLE;

- (nullable instancetype)initWithChannelConfiguration:
    (GRPCChannelConfiguration *)channelConfiguration NS_DESIGNATED_INITIALIZER;

- (nullable grpc_call *)unmanagedCallWithPath:(NSString *)path
                              completionQueue:(GRPCCompletionQueue *)queue
                                  callOptions:(GRPCCallOptions *)callOptions;

@end

NS_ASSUME_NONNULL_END


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

#import "GRPCCallOptions.h"
#import "GRPCDispatchable.h"
#import "GRPCTypes.h"

#import "GRPCCallLegacy.h"

NS_ASSUME_NONNULL_BEGIN

@protocol GRPCResponseHandler <NSObject, GRPCDispatchable>

@optional

- (void)didReceiveInitialMetadata:(nullable NSDictionary *)initialMetadata;

- (void)didReceiveRawMessage:(nullable NSData *)message;

- (void)didReceiveData:(id)data;

- (void)didCloseWithTrailingMetadata:(nullable NSDictionary *)trailingMetadata
                               error:(nullable NSError *)error;

- (void)didWriteData;

@end

@interface GRPCRequestOptions : NSObject <NSCopying>

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithHost:(NSString *)host
                        path:(NSString *)path
                      safety:(GRPCCallSafety)safety NS_DESIGNATED_INITIALIZER;

@property(copy, readonly) NSString *host;

@property(copy, readonly) NSString *path;

@property(readonly) GRPCCallSafety safety;

@end

#pragma mark GRPCCall

@interface GRPCCall2 : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithRequestOptions:(GRPCRequestOptions *)requestOptions
                       responseHandler:(id<GRPCResponseHandler>)responseHandler
                           callOptions:(nullable GRPCCallOptions *)callOptions
    NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithRequestOptions:(GRPCRequestOptions *)requestOptions
                       responseHandler:(id<GRPCResponseHandler>)responseHandler;

- (void)start;

- (void)cancel;

- (void)writeData:(id)data;

- (void)finish;

- (void)receiveNextMessages:(NSUInteger)numberOfMessages;

@property(readonly, copy) GRPCCallOptions *callOptions;

@property(readonly, copy) GRPCRequestOptions *requestOptions;

@end

NS_ASSUME_NONNULL_END

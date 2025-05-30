
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

#import "ProtoRPCLegacy.h"

#import "ProtoMethod.h"

NS_ASSUME_NONNULL_BEGIN

@class GRPCRequestOptions;
@class GRPCCallOptions;
@class GPBMessage;

@protocol GRPCProtoResponseHandler <NSObject>

@required

@property(atomic, readonly) dispatch_queue_t dispatchQueue;

@optional

- (void)didReceiveInitialMetadata:(nullable NSDictionary *)initialMetadata;

- (void)didReceiveProtoMessage:(nullable GPBMessage *)message;

- (void)didCloseWithTrailingMetadata:(nullable NSDictionary *)trailingMetadata
                               error:(nullable NSError *)error;

- (void)didWriteMessage;

@end

@interface GRPCUnaryResponseHandler<ResponseType> : NSObject <GRPCProtoResponseHandler>

- (nullable instancetype)initWithResponseHandler:(void (^)(ResponseType, NSError *))handler
                           responseDispatchQueue:(nullable dispatch_queue_t)dispatchQueue;

@property(readonly, nullable) NSDictionary *responseHeaders;

@property(readonly, nullable) NSDictionary *responseTrailers;

@end

@interface GRPCUnaryProtoCall : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

- (nullable instancetype)initWithRequestOptions:(GRPCRequestOptions *)requestOptions
                                        message:(GPBMessage *)message
                                responseHandler:(id<GRPCProtoResponseHandler>)handler
                                    callOptions:(nullable GRPCCallOptions *)callOptions
                                  responseClass:(Class)responseClass NS_DESIGNATED_INITIALIZER;

- (void)start;

- (void)cancel;

@end

@interface GRPCStreamingProtoCall : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

- (nullable instancetype)initWithRequestOptions:(GRPCRequestOptions *)requestOptions
                                responseHandler:(id<GRPCProtoResponseHandler>)handler
                                    callOptions:(nullable GRPCCallOptions *)callOptions
                                  responseClass:(Class)responseClass NS_DESIGNATED_INITIALIZER;

- (void)start;

- (void)cancel;

- (void)writeMessage:(GPBMessage *)message;

- (void)finish;

- (void)receiveNextMessage;

- (void)receiveNextMessages:(NSUInteger)numberOfMessages;

@end

NS_ASSUME_NONNULL_END

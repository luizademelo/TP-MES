
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

#import "GRPCCall.h"
#import "GRPCDispatchable.h"

NS_ASSUME_NONNULL_BEGIN

@class GRPCInterceptorManager;
@class GRPCInterceptor;
@class GRPCRequestOptions;
@class GRPCCallOptions;
@protocol GRPCResponseHandler;

@protocol GRPCInterceptorInterface <NSObject, GRPCDispatchable>

- (void)startWithRequestOptions:(GRPCRequestOptions *)requestOptions
                    callOptions:(GRPCCallOptions *)callOptions;

- (void)writeData:(id)data;

- (void)finish;

- (void)cancel;

- (void)receiveNextMessages:(NSUInteger)numberOfMessages;

@end

@protocol GRPCInterceptorFactory

- (GRPCInterceptor *)createInterceptorWithManager:(GRPCInterceptorManager *)interceptorManager;

@end

@interface GRPCInterceptorManager : NSObject <GRPCInterceptorInterface, GRPCResponseHandler>

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

- (nullable instancetype)initWithFactories:(nullable NSArray<id<GRPCInterceptorFactory>> *)factories
                       previousInterceptor:(nullable id<GRPCResponseHandler>)previousInterceptor
                               transportID:(GRPCTransportID)transportID;

- (void)shutDown;

- (void)startNextInterceptorWithRequest:(GRPCRequestOptions *)requestOptions
                            callOptions:(GRPCCallOptions *)callOptions;

- (void)writeNextInterceptorWithData:(id)data;

- (void)finishNextInterceptor;

- (void)cancelNextInterceptor;

- (void)receiveNextInterceptorMessages:(NSUInteger)numberOfMessages;

- (void)forwardPreviousInterceptorWithInitialMetadata:(nullable NSDictionary *)initialMetadata;

- (void)forwardPreviousInterceptorWithData:(nullable id)data;

- (void)forwardPreviousInterceptorCloseWithTrailingMetadata:
            (nullable NSDictionary *)trailingMetadata
                                                      error:(nullable NSError *)error;

- (void)forwardPreviousInterceptorDidWriteData;

@end

@interface GRPCInterceptor : NSObject <GRPCInterceptorInterface, GRPCResponseHandler>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (nullable instancetype)initWithInterceptorManager:(GRPCInterceptorManager *)interceptorManager
                                      dispatchQueue:(dispatch_queue_t)dispatchQueue;

- (void)startWithRequestOptions:(GRPCRequestOptions *)requestOptions
                    callOptions:(GRPCCallOptions *)callOptions;
- (void)writeData:(id)data;
- (void)finish;
- (void)cancel;
- (void)receiveNextMessages:(NSUInteger)numberOfMessages;

- (void)didReceiveInitialMetadata:(nullable NSDictionary *)initialMetadata;
- (void)didReceiveData:(id)data;
- (void)didCloseWithTrailingMetadata:(nullable NSDictionary *)trailingMetadata
                               error:(nullable NSError *)error;
- (void)didWriteData;

@end

NS_ASSUME_NONNULL_END

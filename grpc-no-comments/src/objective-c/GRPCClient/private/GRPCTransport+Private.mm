
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

#import "GRPCTransport+Private.h"

#import <GRPCClient/GRPCTransport.h>

@implementation GRPCTransportManager {
  GRPCTransportID _transportID;
  GRPCTransport *_transport;
  id<GRPCResponseHandler> _previousInterceptor;
  dispatch_queue_t _dispatchQueue;
}

- (instancetype)initWithTransportID:(GRPCTransportID)transportID
                previousInterceptor:(id<GRPCResponseHandler>)previousInterceptor {
  if ((self = [super init])) {
    id<GRPCTransportFactory> factory =
        [[GRPCTransportRegistry sharedInstance] getTransportFactoryWithID:transportID];

    _transport = [factory createTransportWithManager:self];
    NSAssert(_transport != nil, @"Failed to create transport with id: %s", transportID);
    if (_transport == nil) {
      NSLog(@"Failed to create transport with id: %s", transportID);
      return nil;
    }
    _previousInterceptor = previousInterceptor;
    _dispatchQueue = _transport.dispatchQueue;
    _transportID = transportID;
  }
  return self;
}

- (void)shutDown {

  _transport = nil;
  _previousInterceptor = nil;
}

- (dispatch_queue_t)dispatchQueue {
  return _dispatchQueue;
}

- (void)startWithRequestOptions:(GRPCRequestOptions *)requestOptions
                    callOptions:(GRPCCallOptions *)callOptions {
  if (_transportID != callOptions.transport) {
    [NSException raise:NSInvalidArgumentException
                format:@"Interceptors cannot change the call option 'transport'"];
    return;
  }

  GRPCTransport *transport = _transport;
  [transport startWithRequestOptions:requestOptions callOptions:callOptions];
}

- (void)writeData:(id)data {

  GRPCTransport *transport = _transport;
  [transport writeData:data];
}

- (void)finish {

  GRPCTransport *transport = _transport;
  [transport finish];
}

- (void)cancel {

  GRPCTransport *transport = _transport;
  [transport cancel];
}

- (void)receiveNextMessages:(NSUInteger)numberOfMessages {

  GRPCTransport *transport = _transport;
  [transport receiveNextMessages:numberOfMessages];
}

- (void)forwardPreviousInterceptorWithInitialMetadata:(NSDictionary *)initialMetadata {
  if (initialMetadata == nil || _previousInterceptor == nil) {
    return;
  }
  id<GRPCResponseHandler> copiedPreviousInterceptor = _previousInterceptor;
  dispatch_async(copiedPreviousInterceptor.dispatchQueue, ^{
    [copiedPreviousInterceptor didReceiveInitialMetadata:initialMetadata];
  });
}

- (void)forwardPreviousInterceptorWithData:(id)data {
  if (data == nil || _previousInterceptor == nil) {
    return;
  }
  id<GRPCResponseHandler> copiedPreviousInterceptor = _previousInterceptor;
  dispatch_async(copiedPreviousInterceptor.dispatchQueue, ^{
    [copiedPreviousInterceptor didReceiveData:data];
  });
}

- (void)forwardPreviousInterceptorCloseWithTrailingMetadata:(NSDictionary *)trailingMetadata
                                                      error:(NSError *)error {
  if (_previousInterceptor == nil) {
    return;
  }
  id<GRPCResponseHandler> copiedPreviousInterceptor = _previousInterceptor;

  _previousInterceptor = nil;
  dispatch_async(copiedPreviousInterceptor.dispatchQueue, ^{
    [copiedPreviousInterceptor didCloseWithTrailingMetadata:trailingMetadata error:error];
  });
}

- (void)forwardPreviousInterceptorDidWriteData {
  if (_previousInterceptor == nil) {
    return;
  }
  id<GRPCResponseHandler> copiedPreviousInterceptor = _previousInterceptor;
  dispatch_async(copiedPreviousInterceptor.dispatchQueue, ^{
    [copiedPreviousInterceptor didWriteData];
  });
}

@end

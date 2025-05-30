
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

#import "GRPCCallLegacy.h"

#import "GRPCCall+OAuth2.h"
#import "GRPCCallOptions.h"
#import "GRPCTypes.h"

#import "private/GRPCCore/GRPCChannelPool.h"
#import "private/GRPCCore/GRPCCompletionQueue.h"
#import "private/GRPCCore/GRPCHost.h"
#import "private/GRPCCore/GRPCWrappedCall.h"
#import "private/GRPCCore/NSData+GRPC.h"

#import <RxLibrary/GRXBufferedPipe.h>
#import <RxLibrary/GRXConcurrentWriteable.h>
#import <RxLibrary/GRXImmediateSingleWriter.h>
#import <RxLibrary/GRXWriter+Immediate.h>

#include <grpc/grpc.h>

const char *kCFStreamVarName = "grpc_cfstream";
static NSMutableDictionary *callFlags;

NSInteger kMaxClientBatch = 6;

static NSString *const kAuthorizationHeader = @"authorization";
static NSString *const kBearerPrefix = @"Bearer ";

@interface GRPCCall () <GRXWriteable>

@property(atomic, copy) NSDictionary *responseHeaders;
@property(atomic, copy) NSDictionary *responseTrailers;

- (void)receiveNextMessages:(NSUInteger)numberOfMessages;

@end

@implementation GRPCCall {
  dispatch_queue_t _callQueue;

  NSString *_host;
  NSString *_path;
  GRPCCallSafety _callSafety;
  GRPCCallOptions *_callOptions;
  GRPCWrappedCall *_wrappedCall;

  GRXConcurrentWriteable *_responseWriteable;

  GRXWriter *_requestWriter;

  GRPCCall *_retainSelf;

  GRPCRequestHeaders *_requestHeaders;

  BOOL _unaryCall;
  NSMutableArray *_unaryOpBatch;

  dispatch_queue_t _responseQueue;

  NSString *_fetchedOauth2AccessToken;

  void (^_writeDone)(void);

  BOOL _pendingCoreRead;

  NSUInteger _pendingReceiveNextMessages;
}

@synthesize state = _state;

+ (void)initialize {

  if (self == [GRPCCall self]) {
    grpc_init();
    callFlags = [NSMutableDictionary dictionary];
  }
}

+ (void)setCallSafety:(GRPCCallSafety)callSafety host:(NSString *)host path:(NSString *)path {
  if (host.length == 0 || path.length == 0) {
    return;
  }
  NSString *hostAndPath = [NSString stringWithFormat:@"%@/%@", host, path];
  @synchronized(callFlags) {
    switch (callSafety) {
      case GRPCCallSafetyDefault:
        callFlags[hostAndPath] = @0;
        break;
      default:
        break;
    }
  }
}

+ (uint32_t)callFlagsForHost:(NSString *)host path:(NSString *)path {
  NSString *hostAndPath = [NSString stringWithFormat:@"%@/%@", host, path];
  @synchronized(callFlags) {
    return [callFlags[hostAndPath] intValue];
  }
}

- (instancetype)initWithHost:(NSString *)host
                        path:(NSString *)path
              requestsWriter:(GRXWriter *)requestWriter {
  return [self initWithHost:host
                       path:path
                 callSafety:GRPCCallSafetyDefault
             requestsWriter:requestWriter
                callOptions:nil
                  writeDone:nil];
}

- (instancetype)initWithHost:(NSString *)host
                        path:(NSString *)path
                  callSafety:(GRPCCallSafety)safety
              requestsWriter:(GRXWriter *)requestsWriter
                 callOptions:(GRPCCallOptions *)callOptions
                   writeDone:(void (^)(void))writeDone {

  NSAssert(host != nil && path != nil, @"Neither host nor path can be nil.");
  NSAssert(safety <= GRPCCallSafetyDefault, @"Invalid call safety value.");
  NSAssert(requestsWriter.state == GRXWriterStateNotStarted,
           @"The requests writer can't be already started.");
  if (!host || !path) {
    return nil;
  }
  if (requestsWriter.state != GRXWriterStateNotStarted) {
    return nil;
  }

  if ((self = [super init])) {
    _host = [host copy];
    _path = [path copy];
    _callSafety = safety;
    _callOptions = [callOptions copy];

    _callQueue = dispatch_queue_create("io.grpc.call", DISPATCH_QUEUE_SERIAL);

    _requestWriter = requestsWriter;
    _requestHeaders = [[GRPCRequestHeaders alloc] initWithCall:self];
    _writeDone = writeDone;

    if ([requestsWriter isKindOfClass:[GRXImmediateSingleWriter class]]) {
      _unaryCall = YES;
      _unaryOpBatch = [NSMutableArray arrayWithCapacity:kMaxClientBatch];
    }

    _responseQueue = dispatch_get_main_queue();

    _pendingReceiveNextMessages = 0;
    _pendingCoreRead = YES;
  }
  return self;
}

- (void)setResponseDispatchQueue:(dispatch_queue_t)queue {
  @synchronized(self) {
    if (_state != GRXWriterStateNotStarted) {
      return;
    }
    _responseQueue = queue;
  }
}

#pragma mark Finish

- (void)finishWithError:(NSError *)errorOrNil {
  @synchronized(self) {
    if (_state == GRXWriterStateFinished) {
      return;
    }
    _state = GRXWriterStateFinished;

    if (errorOrNil) {
      [_responseWriteable cancelWithError:errorOrNil];
    } else {
      [_responseWriteable enqueueSuccessfulCompletion];
    }

    _retainSelf = nil;
  }
}

- (void)cancel {
  @synchronized(self) {
    if (_state == GRXWriterStateFinished) {
      return;
    }
    [self finishWithError:[NSError
                              errorWithDomain:kGRPCErrorDomain
                                         code:GRPCErrorCodeCancelled
                                     userInfo:@{NSLocalizedDescriptionKey : @"Canceled by app"}]];
    [_wrappedCall cancel];
  }
  _requestWriter.state = GRXWriterStateFinished;
}

- (void)dealloc {
  if (_callQueue) {
    __block GRPCWrappedCall *wrappedCall = _wrappedCall;
    dispatch_async(_callQueue, ^{
      wrappedCall = nil;
    });
  } else {
    _wrappedCall = nil;
  }
}

#pragma mark Read messages

- (void)startReadWithHandler:(void (^)(grpc_byte_buffer *))handler {

  [_wrappedCall startBatchWithOperations:@[ [[GRPCOpRecvMessage alloc] initWithHandler:handler] ]];
}

- (void)maybeStartNextRead {
  @synchronized(self) {
    if (_state != GRXWriterStateStarted) {
      return;
    }
    if (_callOptions.flowControlEnabled && (_pendingCoreRead || _pendingReceiveNextMessages == 0)) {
      return;
    }
    _pendingCoreRead = YES;
    _pendingReceiveNextMessages--;
  }

  dispatch_async(_callQueue, ^{
    __weak GRPCCall *weakSelf = self;
    [self startReadWithHandler:^(grpc_byte_buffer *message) {
      if (message == NULL) {

        return;
      }
      __strong GRPCCall *strongSelf = weakSelf;
      if (strongSelf == nil) {
        grpc_byte_buffer_destroy(message);
        return;
      }
      NSData *data = [NSData grpc_dataWithByteBuffer:message];
      grpc_byte_buffer_destroy(message);
      if (!data) {

        @synchronized(strongSelf) {
          strongSelf->_pendingCoreRead = NO;
          [strongSelf
              finishWithError:[NSError errorWithDomain:kGRPCErrorDomain
                                                  code:GRPCErrorCodeResourceExhausted
                                              userInfo:@{
                                                NSLocalizedDescriptionKey :
                                                    @"Client does not have enough memory to "
                                                    @"hold the server response."
                                              }]];
          [strongSelf->_wrappedCall cancel];
        }
        strongSelf->_requestWriter.state = GRXWriterStateFinished;
      } else {
        @synchronized(strongSelf) {
          [strongSelf->_responseWriteable enqueueValue:data
                                     completionHandler:^{
                                       __strong GRPCCall *strongSelf = weakSelf;
                                       if (strongSelf) {
                                         @synchronized(strongSelf) {
                                           strongSelf->_pendingCoreRead = NO;
                                           [strongSelf maybeStartNextRead];
                                         }
                                       }
                                     }];
        }
      }
    }];
  });
}

#pragma mark Send headers

- (void)sendHeaders {

  uint32_t callSafetyFlags = 0;

  NSMutableDictionary *headers = [_requestHeaders mutableCopy];
  NSString *fetchedOauth2AccessToken;
  @synchronized(self) {
    fetchedOauth2AccessToken = _fetchedOauth2AccessToken;
  }
  if (fetchedOauth2AccessToken != nil) {
    headers[@"authorization"] = [kBearerPrefix stringByAppendingString:fetchedOauth2AccessToken];
  } else if (_callOptions.oauth2AccessToken != nil) {
    headers[@"authorization"] =
        [kBearerPrefix stringByAppendingString:_callOptions.oauth2AccessToken];
  }

  GRPCOpSendMetadata *op = [[GRPCOpSendMetadata alloc]
      initWithMetadata:headers
                 flags:callSafetyFlags
               handler:nil];
  dispatch_async(_callQueue, ^{
    if (!self->_unaryCall) {
      [self->_wrappedCall startBatchWithOperations:@[ op ]];
    } else {
      [self->_unaryOpBatch addObject:op];
    }
  });
}

- (void)receiveNextMessages:(NSUInteger)numberOfMessages {
  if (numberOfMessages == 0) {
    return;
  }
  @synchronized(self) {
    _pendingReceiveNextMessages += numberOfMessages;

    if (_state != GRXWriterStateStarted || !_callOptions.flowControlEnabled) {
      return;
    }
    [self maybeStartNextRead];
  }
}

#pragma mark GRXWriteable implementation

- (void)writeMessage:(NSData *)message withErrorHandler:(void (^)(void))errorHandler {
  __weak GRPCCall *weakSelf = self;
  void (^resumingHandler)(void) = ^{

    GRPCCall *strongSelf = weakSelf;
    if (strongSelf) {
      strongSelf->_requestWriter.state = GRXWriterStateStarted;
      if (strongSelf->_writeDone) {
        strongSelf->_writeDone();
      }
    }
  };
  GRPCOpSendMessage *op = [[GRPCOpSendMessage alloc] initWithMessage:message
                                                             handler:resumingHandler];
  if (!_unaryCall) {
    [_wrappedCall startBatchWithOperations:@[ op ] errorHandler:errorHandler];
  } else {

    [_unaryOpBatch addObject:op];
  }
}

- (void)writeValue:(id)value {
  NSAssert([value isKindOfClass:[NSData class]], @"value must be of type NSData");

  @synchronized(self) {
    if (_state == GRXWriterStateFinished) {
      return;
    }
  }

  _requestWriter.state = GRXWriterStatePaused;

  dispatch_async(_callQueue, ^{

    [self writeMessage:value withErrorHandler:nil];
  });
}

- (void)finishRequestWithErrorHandler:(void (^)(void))errorHandler {
  if (!_unaryCall) {
    [_wrappedCall startBatchWithOperations:@[ [[GRPCOpSendClose alloc] init] ]
                              errorHandler:errorHandler];
  } else {
    [_unaryOpBatch addObject:[[GRPCOpSendClose alloc] init]];
    [_wrappedCall startBatchWithOperations:_unaryOpBatch errorHandler:errorHandler];
  }
}

- (void)writesFinishedWithError:(NSError *)errorOrNil {
  if (errorOrNil) {
    [self cancel];
  } else {
    dispatch_async(_callQueue, ^{

      [self finishRequestWithErrorHandler:nil];
    });
  }
}

#pragma mark Invoke

- (void)invokeCallWithHeadersHandler:(void (^)(NSDictionary *))headersHandler
                   completionHandler:(void (^)(NSError *, NSDictionary *))completionHandler {
  dispatch_async(_callQueue, ^{

    [self->_wrappedCall
        startBatchWithOperations:@[ [[GRPCOpRecvMetadata alloc] initWithHandler:headersHandler] ]];
    [self->_wrappedCall
        startBatchWithOperations:@[ [[GRPCOpRecvStatus alloc] initWithHandler:completionHandler] ]];
  });
}

- (void)invokeCall {
  __weak GRPCCall *weakSelf = self;
  [self
      invokeCallWithHeadersHandler:^(NSDictionary *headers) {

        __strong GRPCCall *strongSelf = weakSelf;
        if (strongSelf) {
          @synchronized(strongSelf) {

            strongSelf.responseHeaders = nil;

            NSDictionary *copiedHeaders = [[NSDictionary alloc] initWithDictionary:headers
                                                                         copyItems:YES];
            strongSelf.responseHeaders = copiedHeaders;
            strongSelf->_pendingCoreRead = NO;
            [strongSelf maybeStartNextRead];
          }
        }
      }
      completionHandler:^(NSError *error, NSDictionary *trailers) {
        __strong GRPCCall *strongSelf = weakSelf;
        if (strongSelf) {
          strongSelf.responseTrailers = trailers;

          if (error) {
            NSMutableDictionary *userInfo = [NSMutableDictionary dictionary];
            if (error.userInfo) {
              [userInfo addEntriesFromDictionary:error.userInfo];
            }
            userInfo[kGRPCTrailersKey] = strongSelf.responseTrailers;

            userInfo[kGRPCHeadersKey] = strongSelf.responseHeaders;
            error = [NSError errorWithDomain:error.domain code:error.code userInfo:userInfo];
          }
          [strongSelf finishWithError:error];
          strongSelf->_requestWriter.state = GRXWriterStateFinished;
        }
      }];
}

#pragma mark GRXWriter implementation

- (void)startCallWithWriteable:(id<GRXWriteable>)writeable {
  @synchronized(self) {
    if (_state == GRXWriterStateFinished) {
      return;
    }

    _responseWriteable = [[GRXConcurrentWriteable alloc] initWithWriteable:writeable
                                                             dispatchQueue:_responseQueue];

    GRPCPooledChannel *channel = [[GRPCChannelPool sharedInstance] channelWithHost:_host
                                                                       callOptions:_callOptions];
    _wrappedCall = [channel wrappedCallWithPath:_path
                                completionQueue:[GRPCCompletionQueue completionQueue]
                                    callOptions:_callOptions];

    if (_wrappedCall == nil) {
      [self finishWithError:[NSError errorWithDomain:kGRPCErrorDomain
                                                code:GRPCErrorCodeUnavailable
                                            userInfo:@{
                                              NSLocalizedDescriptionKey :
                                                  @"Failed to create call or channel."
                                            }]];
      return;
    }

    [self sendHeaders];
    [self invokeCall];
  }

  [_requestWriter startWithWriteable:self];
}

- (void)startWithWriteable:(id<GRXWriteable>)writeable {
  id<GRPCAuthorizationProtocol> tokenProvider = nil;
  @synchronized(self) {
    _state = GRXWriterStateStarted;

    _retainSelf = self;

    if (_callOptions == nil) {
      GRPCMutableCallOptions *callOptions = [[GRPCHost callOptionsForHost:_host] mutableCopy];
      if (_serverName.length != 0) {
        callOptions.serverAuthority = _serverName;
      }
      if (_timeout > 0) {
        callOptions.timeout = _timeout;
      }

      id<GRPCAuthorizationProtocol> tokenProvider = self.tokenProvider;
      if (tokenProvider != nil) {
        callOptions.authTokenProvider = tokenProvider;
      }
      _callOptions = callOptions;
    }

    NSAssert(_callOptions.authTokenProvider == nil || _callOptions.oauth2AccessToken == nil,
             @"authTokenProvider and oauth2AccessToken cannot be set at the same time");

    tokenProvider = _callOptions.authTokenProvider;
  }

  if (tokenProvider != nil) {
    __weak auto weakSelf = self;
    [tokenProvider getTokenWithHandler:^(NSString *token) {
      __strong auto strongSelf = weakSelf;
      if (strongSelf) {
        BOOL startCall = NO;
        @synchronized(strongSelf) {
          if (strongSelf->_state != GRXWriterStateFinished) {
            startCall = YES;
            if (token) {
              strongSelf->_fetchedOauth2AccessToken = [token copy];
            }
          }
        }
        if (startCall) {
          [strongSelf startCallWithWriteable:writeable];
        }
      }
    }];
  } else {
    [self startCallWithWriteable:writeable];
  }
}

- (void)setState:(GRXWriterState)newState {
  @synchronized(self) {

    if (_state == GRXWriterStateNotStarted || _state == GRXWriterStateFinished) {
      return;
    }

    switch (newState) {
      case GRXWriterStateFinished:
        _state = newState;

        [_responseWriteable cancelSilently];
        _responseWriteable = nil;
        return;
      case GRXWriterStatePaused:
        _state = newState;
        return;
      case GRXWriterStateStarted:
        if (_state == GRXWriterStatePaused) {
          _state = newState;
          [self maybeStartNextRead];
        }
        return;
      case GRXWriterStateNotStarted:
        return;
    }
  }
}

@end

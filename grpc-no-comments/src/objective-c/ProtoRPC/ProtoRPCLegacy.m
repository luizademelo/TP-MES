
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

#import "ProtoRPCLegacy.h"

#import "ProtoMethod.h"

#if GPB_USE_PROTOBUF_FRAMEWORK_IMPORTS
#import <Protobuf/GPBProtocolBuffers.h>
#else
#import <GPBProtocolBuffers.h>
#endif
#import <GRPCClient/GRPCCall.h>
#import <RxLibrary/GRXWriteable.h>
#import <RxLibrary/GRXWriter+Transformations.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-implementations"
@implementation ProtoRPC {
#pragma clang diagnostic pop
  id<GRXWriteable> _responseWriteable;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wobjc-designated-initializers"
- (instancetype)initWithHost:(NSString *)host
                        path:(NSString *)path
              requestsWriter:(GRXWriter *)requestsWriter {
  [NSException raise:NSInvalidArgumentException
              format:@"Please use ProtoRPC's designated initializer instead."];
  return nil;
}
#pragma clang diagnostic pop

- (instancetype)initWithHost:(NSString *)host
                      method:(GRPCProtoMethod *)method
              requestsWriter:(GRXWriter *)requestsWriter
               responseClass:(Class)responseClass
          responsesWriteable:(id<GRXWriteable>)responsesWriteable {

  if (![responseClass respondsToSelector:@selector(parseFromData:error:)]) {
    [NSException raise:NSInvalidArgumentException
                format:@"A protobuf class to parse the responses must be provided."];
  }

  GRXWriter *bytesWriter = [requestsWriter map:^id(GPBMessage *proto) {
    if (![proto isKindOfClass:[GPBMessage class]]) {
      [NSException raise:NSInvalidArgumentException
                  format:@"Request must be a proto message: %@", proto];
    }
    return [proto data];
  }];
  if ((self = [super initWithHost:host path:method.HTTPPath requestsWriter:bytesWriter])) {
    __weak ProtoRPC *weakSelf = self;

    _responseWriteable = [[GRXWriteable alloc]
        initWithValueHandler:^(NSData *value) {

          NSError *error = nil;
          id parsed = [responseClass parseFromData:value error:&error];
          if (parsed) {
            [responsesWriteable writeValue:parsed];
          } else {
            [weakSelf finishWithError:ErrorForBadProto(value, responseClass, error)];
          }
        }
        completionHandler:^(NSError *errorOrNil) {
          [responsesWriteable writesFinishedWithError:errorOrNil];
        }];
  }
  return self;
}

- (void)start {
  [self startWithWriteable:_responseWriteable];
}

- (void)startWithWriteable:(id<GRXWriteable>)writeable {
  [super startWithWriteable:writeable];

  _responseWriteable = nil;
}
@end

@implementation GRPCProtoCall

@end


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

#import "GRXWriteable.h"

@implementation GRXWriteable {
  GRXValueHandler _valueHandler;
  GRXCompletionHandler _completionHandler;
}

+ (instancetype)writeableWithSingleHandler:(GRXSingleHandler)handler {
  if (!handler) {
    return [[self alloc] init];
  }

  __block GRXEventHandler eventHandler = ^(BOOL done, id value, NSError *error) {

    GRXSingleHandler singleHandler = handler;
    eventHandler = nil;

    if (value) {
      singleHandler(value, nil);
    } else if (error) {
      singleHandler(nil, error);
    } else {
      NSDictionary *userInfo =
          @{NSLocalizedDescriptionKey : @"The writer finished without producing any value."};

      static NSString *kGRPCErrorDomain = @"io.grpc";
      static NSUInteger kGRPCErrorCodeInternal = 13;
      singleHandler(nil, [NSError errorWithDomain:kGRPCErrorDomain
                                             code:kGRPCErrorCodeInternal
                                         userInfo:userInfo]);
    }
  };
  return [self writeableWithEventHandler:^(BOOL done, id value, NSError *error) {
    if (eventHandler) {
      eventHandler(done, value, error);
    }
  }];
}

+ (instancetype)writeableWithEventHandler:(GRXEventHandler)handler {
  if (!handler) {
    return [[self alloc] init];
  }
  return [[self alloc]
      initWithValueHandler:^(id value) {
        handler(NO, value, nil);
      }
      completionHandler:^(NSError *errorOrNil) {
        handler(YES, nil, errorOrNil);
      }];
}

- (instancetype)init {
  return [self initWithValueHandler:nil completionHandler:nil];
}

- (instancetype)initWithValueHandler:(GRXValueHandler)valueHandler
                   completionHandler:(GRXCompletionHandler)completionHandler {
  if ((self = [super init])) {
    _valueHandler = valueHandler;
    _completionHandler = completionHandler;
  }
  return self;
}

- (void)writeValue:(id)value {
  if (_valueHandler) {
    _valueHandler(value);
  }
}

- (void)writesFinishedWithError:(NSError *)errorOrNil {
  if (_completionHandler) {
    _completionHandler(errorOrNil);
  }
}
@end

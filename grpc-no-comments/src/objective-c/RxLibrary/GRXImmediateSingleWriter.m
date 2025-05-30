
/*
 *
 * Copyright 2016 gRPC authors.
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

#import "GRXImmediateSingleWriter.h"

@implementation GRXImmediateSingleWriter {
  id _value;
}

@synthesize state = _state;

- (instancetype)initWithValue:(id)value {
  if (self = [super init]) {
    _value = value;
    _state = GRXWriterStateNotStarted;
  }
  return self;
}

+ (GRXWriter *)writerWithValue:(id)value {
  return [[self alloc] initWithValue:value];
}

- (void)startWithWriteable:(id<GRXWriteable>)writeable {
  id copiedValue = nil;
  @synchronized(self) {
    if (_state != GRXWriterStateNotStarted) {
      return;
    }
    copiedValue = _value;
    _value = nil;
    _state = GRXWriterStateFinished;
  }
  [writeable writeValue:copiedValue];
  [writeable writesFinishedWithError:nil];
}

- (void)setState:(GRXWriterState)newState {

  return;
}

- (GRXWriter *)map:(id (^)(id))map {
  @synchronized(self) {

    _value = map(_value);
  }
  return self;
}

@end

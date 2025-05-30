
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

#import "GRXNSFastEnumerator.h"

@implementation GRXNSFastEnumerator {
  id<NSFastEnumeration> _container;
  NSFastEnumerationState _state;

  NSUInteger _count;

  NSUInteger _index;

  __unsafe_unretained id _bufferValue;

  unsigned long _mutationFlag;
  BOOL _mutationFlagIsSet;
}

- (instancetype)init {
  return [self initWithContainer:nil];
}

- (instancetype)initWithContainer:(id<NSFastEnumeration>)container {
  if ((self = [super init])) {
    _container = container;
  }
  return self;
}

- (id)nextObject {
  if (_index == _count) {
    _index = 0;
    _count = [_container countByEnumeratingWithState:&_state objects:&_bufferValue count:1];
    if (_count == 0) {

      _container = nil;
      return nil;
    }
    if (_mutationFlagIsSet) {
      NSAssert(_mutationFlag == *(_state.mutationsPtr),
               @"container was mutated while being enumerated");
    } else {
      _mutationFlag = *(_state.mutationsPtr);
      _mutationFlagIsSet = YES;
    }
  }
  return _state.itemsPtr[_index++];
}
@end

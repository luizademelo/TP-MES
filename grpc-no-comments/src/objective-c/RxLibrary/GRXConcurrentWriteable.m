
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

#import "GRXConcurrentWriteable.h"

#import "GRXWriteable.h"

@interface GRXConcurrentWriteable ()

@property(atomic, strong) id<GRXWriteable> writeable;
@end

@implementation GRXConcurrentWriteable {
  dispatch_queue_t _writeableQueue;

  BOOL _alreadyFinished;

  BOOL _cancelled;
}

- (instancetype)init {
  return [self initWithWriteable:nil];
}

- (instancetype)initWithWriteable:(id<GRXWriteable>)writeable
                    dispatchQueue:(dispatch_queue_t)queue {
  if (self = [super init]) {
    _writeableQueue = queue;
    _writeable = writeable;
    _alreadyFinished = NO;
    _cancelled = NO;
  }
  return self;
}

- (instancetype)initWithWriteable:(id<GRXWriteable>)writeable {
  return [self initWithWriteable:writeable dispatchQueue:dispatch_get_main_queue()];
}

- (void)enqueueValue:(id)value completionHandler:(void (^)(void))handler {
  dispatch_async(_writeableQueue, ^{
    if (self->_alreadyFinished) {
      return;
    }

    @synchronized(self) {
      if (self->_cancelled) {
        return;
      }
    }

    [self.writeable writeValue:value];
    handler();
  });
}

- (void)enqueueSuccessfulCompletion {
  dispatch_async(_writeableQueue, ^{
    if (self->_alreadyFinished) {
      return;
    }
    @synchronized(self) {
      if (self->_cancelled) {
        return;
      }
    }
    [self.writeable writesFinishedWithError:nil];

    self->_alreadyFinished = YES;
    self.writeable = nil;
  });
}

- (void)cancelWithError:(NSError *)error {
  NSAssert(error != nil, @"For a successful completion, use enqueueSuccessfulCompletion.");
  @synchronized(self) {
    self->_cancelled = YES;
  }
  dispatch_async(_writeableQueue, ^{
    if (self->_alreadyFinished) {

      return;
    }
    [self.writeable writesFinishedWithError:error];

    self->_alreadyFinished = YES;
    self.writeable = nil;
  });
}

- (void)cancelSilently {
  dispatch_async(_writeableQueue, ^{
    if (self->_alreadyFinished) {
      return;
    }
    self.writeable = nil;
  });
}
@end

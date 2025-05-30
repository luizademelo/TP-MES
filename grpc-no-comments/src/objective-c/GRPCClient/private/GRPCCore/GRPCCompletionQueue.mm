
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

#import "GRPCCompletionQueue.h"

#import <grpc/grpc.h>

const grpc_completion_queue_attributes kCompletionQueueAttr = {
    GRPC_CQ_CURRENT_VERSION, GRPC_CQ_NEXT, GRPC_CQ_DEFAULT_POLLING, NULL};

@implementation GRPCCompletionQueue

+ (instancetype)completionQueue {
  static GRPCCompletionQueue *singleton = nil;
  static dispatch_once_t onceToken;
  dispatch_once(&onceToken, ^{
    singleton = [[self alloc] init];
  });
  return singleton;
}

- (instancetype)init {
  if ((self = [super init])) {
    _unmanagedQueue = grpc_completion_queue_create(
        grpc_completion_queue_factory_lookup(&kCompletionQueueAttr), &kCompletionQueueAttr, NULL);

    grpc_completion_queue *unmanagedQueue = _unmanagedQueue;

    static dispatch_once_t initialization;
    static dispatch_queue_t gDefaultConcurrentQueue;
    dispatch_once(&initialization, ^{
      gDefaultConcurrentQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    });
    dispatch_async(gDefaultConcurrentQueue, ^{
      while (YES) {
        @autoreleasepool {

          grpc_event event =
              grpc_completion_queue_next(unmanagedQueue, gpr_inf_future(GPR_CLOCK_REALTIME), NULL);
          GRPCQueueCompletionHandler handler;
          switch (event.type) {
            case GRPC_OP_COMPLETE:
              handler = (__bridge_transfer GRPCQueueCompletionHandler)event.tag;
              handler(event.success);
              break;
            case GRPC_QUEUE_SHUTDOWN:
              grpc_completion_queue_destroy(unmanagedQueue);
              return;
            case GRPC_QUEUE_TIMEOUT:
              NSLog(@"GRPC_QUEUE_TIMEOUT, success: %d, tag: %p", event.success, event.tag);
              break;
            default:
              [NSException raise:@"Unrecognized completion type" format:@""];
          }
        }
      };
    });
  }
  return self;
}

- (void)dealloc {

  grpc_completion_queue_shutdown(_unmanagedQueue);
}
@end

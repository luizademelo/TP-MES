
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

#include <ruby/ruby.h>

#include "rb_completion_queue.h"

#include <grpc/grpc.h>
#include <grpc/support/log.h>
#include <grpc/support/time.h>
#include <ruby/thread.h>

#include "rb_grpc.h"
#include "rb_grpc_imports.generated.h"

typedef struct next_call_stack {
  grpc_completion_queue* cq;
  grpc_event event;
  gpr_timespec timeout;
  void* tag;
  void (*unblock_func)(void*);
  void* unblock_func_arg;
} next_call_stack;

static void* grpc_rb_completion_queue_pluck_no_gil(void* param) {
  next_call_stack* const next_call = (next_call_stack*)param;
  next_call->event = grpc_completion_queue_pluck(next_call->cq, next_call->tag,
                                                 next_call->timeout, NULL);
  return NULL;
}

void grpc_rb_completion_queue_destroy(grpc_completion_queue* cq) {

  grpc_completion_queue_shutdown(cq);
  grpc_completion_queue_destroy(cq);
}

static void outer_unblock_func(void* param) {
  next_call_stack* const next_call = (next_call_stack*)param;
  if (next_call->unblock_func == NULL) return;
  next_call->unblock_func(next_call->unblock_func_arg);
}

grpc_event rb_completion_queue_pluck(grpc_completion_queue* queue, void* tag,
                                     gpr_timespec deadline,
                                     void (*unblock_func)(void* param),
                                     void* unblock_func_arg) {
  next_call_stack next_call;
  MEMZERO(&next_call, next_call_stack, 1);
  next_call.cq = queue;
  next_call.timeout = deadline;
  next_call.tag = tag;
  next_call.event.type = GRPC_QUEUE_TIMEOUT;
  next_call.unblock_func = unblock_func;
  next_call.unblock_func_arg = unblock_func_arg;
  rb_thread_call_without_gvl(grpc_rb_completion_queue_pluck_no_gil,
                             (void*)&next_call, outer_unblock_func,
                             (void*)&next_call);
  return next_call.event;
}

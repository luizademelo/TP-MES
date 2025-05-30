
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

#include "rb_channel.h"

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/support/alloc.h>
#include <grpc/support/log.h>
#include <grpc/support/time.h>
#include <ruby/thread.h>

#include "rb_byte_buffer.h"
#include "rb_call.h"
#include "rb_channel_args.h"
#include "rb_channel_credentials.h"
#include "rb_completion_queue.h"
#include "rb_grpc.h"
#include "rb_grpc_imports.generated.h"
#include "rb_server.h"
#include "rb_xds_channel_credentials.h"

static ID id_channel;

static ID id_target;

static ID id_channel_recreation_mu;

static VALUE id_insecure_channel;

static VALUE grpc_rb_cChannel = Qnil;

static VALUE grpc_rb_cChannelArgs;

typedef struct bg_watched_channel {
  grpc_channel* channel;

  struct bg_watched_channel* next;
  int channel_destroyed;
  int refcount;
} bg_watched_channel;

typedef struct grpc_rb_channel {
  VALUE credentials;
  grpc_channel_args args;

  bg_watched_channel* bg_wrapped;
} grpc_rb_channel;

typedef enum { CONTINUOUS_WATCH, WATCH_STATE_API } watch_state_op_type;

typedef struct watch_state_op {
  watch_state_op_type op_type;

  union {
    struct {
      int success;

      int called_back;
    } api_callback_args;
    struct {
      bg_watched_channel* bg;
    } continuous_watch_callback_args;
  } op;
} watch_state_op;

static bg_watched_channel* bg_watched_channel_list_head = NULL;

static void grpc_rb_channel_try_register_connection_polling(
    bg_watched_channel* bg);
static void* channel_init_try_register_connection_polling_without_gil(
    void* arg);

typedef struct channel_init_try_register_stack {
  grpc_channel* channel;
  grpc_rb_channel* wrapper;
} channel_init_try_register_stack;

static grpc_completion_queue* g_channel_polling_cq;
static gpr_mu global_connection_polling_mu;
static gpr_cv global_connection_polling_cv;
static int g_abort_channel_polling = 0;
static gpr_once g_once_init = GPR_ONCE_INIT;
static VALUE g_channel_polling_thread = Qnil;

static int bg_watched_channel_list_lookup(bg_watched_channel* bg);
static bg_watched_channel* bg_watched_channel_list_create_and_add(
    grpc_channel* channel);
static void bg_watched_channel_list_free_and_remove(bg_watched_channel* bg);
static void run_poll_channels_loop_unblocking_func(void* arg);
static void* run_poll_channels_loop_unblocking_func_wrapper(void* arg);

static void grpc_rb_channel_watch_connection_state_op_complete(
    watch_state_op* op, int success) {
  GRPC_RUBY_ASSERT(!op->op.api_callback_args.called_back);
  op->op.api_callback_args.called_back = 1;
  op->op.api_callback_args.success = success;

  gpr_cv_broadcast(&global_connection_polling_cv);
}

static void grpc_rb_channel_safe_destroy(bg_watched_channel* bg) {
  gpr_mu_lock(&global_connection_polling_mu);
  GRPC_RUBY_ASSERT(bg_watched_channel_list_lookup(bg));
  if (!bg->channel_destroyed) {
    grpc_channel_destroy(bg->channel);
    bg->channel_destroyed = 1;
  }
  bg->refcount--;
  if (bg->refcount == 0) {
    bg_watched_channel_list_free_and_remove(bg);
  }
  gpr_mu_unlock(&global_connection_polling_mu);
}

static void* channel_safe_destroy_without_gil(void* arg) {
  grpc_rb_channel_safe_destroy((bg_watched_channel*)arg);
  return NULL;
}

static void grpc_rb_channel_free_internal(void* p) {
  grpc_rb_channel* ch = NULL;
  if (p == NULL) {
    return;
  };
  ch = (grpc_rb_channel*)p;
  if (ch->bg_wrapped != NULL) {

    grpc_rb_channel_safe_destroy(ch->bg_wrapped);
    grpc_rb_channel_args_destroy(&ch->args);
  }
  xfree(p);
}

static void grpc_rb_channel_free(void* p) { grpc_rb_channel_free_internal(p); }

static void grpc_rb_channel_mark(void* p) {
  grpc_rb_channel* channel = NULL;
  if (p == NULL) {
    return;
  }
  channel = (grpc_rb_channel*)p;
  if (channel->credentials != Qnil) {
    rb_gc_mark(channel->credentials);
  }
}

static rb_data_type_t grpc_channel_data_type = {"grpc_channel",
                                                {grpc_rb_channel_mark,
                                                 grpc_rb_channel_free,
                                                 GRPC_RB_MEMSIZE_UNAVAILABLE,
                                                 {NULL, NULL}},
                                                NULL,
                                                NULL,
#ifdef RUBY_TYPED_FREE_IMMEDIATELY
                                                RUBY_TYPED_FREE_IMMEDIATELY
#endif
};

static VALUE grpc_rb_channel_alloc(VALUE cls) {
  grpc_ruby_init();
  grpc_rb_channel* wrapper = ALLOC(grpc_rb_channel);
  wrapper->bg_wrapped = NULL;
  wrapper->credentials = Qnil;
  MEMZERO(&wrapper->args, grpc_channel_args, 1);
  return TypedData_Wrap_Struct(cls, &grpc_channel_data_type, wrapper);
}

static VALUE grpc_rb_channel_init(int argc, VALUE* argv, VALUE self) {
  VALUE channel_args = Qnil;
  VALUE credentials = Qnil;
  VALUE target = Qnil;
  grpc_rb_channel* wrapper = NULL;
  grpc_channel* ch = NULL;
  grpc_channel_credentials* creds = NULL;
  char* target_chars = NULL;
  channel_init_try_register_stack stack;

  grpc_ruby_fork_guard();

  rb_scan_args(argc, argv, "3", &target, &channel_args, &credentials);

  TypedData_Get_Struct(self, grpc_rb_channel, &grpc_channel_data_type, wrapper);
  target_chars = StringValueCStr(target);
  grpc_rb_hash_convert_to_channel_args(channel_args, &wrapper->args);
  if (TYPE(credentials) == T_SYMBOL) {
    if (id_insecure_channel != SYM2ID(credentials)) {
      rb_raise(rb_eTypeError,
               "bad creds symbol, want :this_channel_is_insecure");
      return Qnil;
    }
    grpc_channel_credentials* insecure_creds =
        grpc_insecure_credentials_create();
    ch = grpc_channel_create(target_chars, insecure_creds, &wrapper->args);
    grpc_channel_credentials_release(insecure_creds);
  } else {
    wrapper->credentials = credentials;
    if (grpc_rb_is_channel_credentials(credentials)) {
      creds = grpc_rb_get_wrapped_channel_credentials(credentials);
    } else if (grpc_rb_is_xds_channel_credentials(credentials)) {
      creds = grpc_rb_get_wrapped_xds_channel_credentials(credentials);
    } else {
      rb_raise(rb_eTypeError,
               "bad creds, want ChannelCredentials or XdsChannelCredentials");
      return Qnil;
    }
    ch = grpc_channel_create(target_chars, creds, &wrapper->args);
  }

  GRPC_RUBY_ASSERT(ch);
  stack.channel = ch;
  stack.wrapper = wrapper;
  rb_thread_call_without_gvl(
      channel_init_try_register_connection_polling_without_gil, &stack, NULL,
      NULL);
  if (ch == NULL) {
    rb_raise(rb_eRuntimeError, "could not create an rpc channel to target:%s",
             target_chars);
    return Qnil;
  }
  rb_ivar_set(self, id_target, target);
  rb_ivar_set(self, id_channel_recreation_mu, rb_mutex_new());
  return self;
}

typedef struct get_state_stack {
  bg_watched_channel* bg;
  int try_to_connect;
  int out;
} get_state_stack;

static void* get_state_without_gil(void* arg) {
  get_state_stack* stack = (get_state_stack*)arg;

  gpr_mu_lock(&global_connection_polling_mu);
  if (stack->bg->channel_destroyed) {
    stack->out = GRPC_CHANNEL_SHUTDOWN;
  } else {
    stack->out = grpc_channel_check_connectivity_state(stack->bg->channel,
                                                       stack->try_to_connect);
  }
  gpr_mu_unlock(&global_connection_polling_mu);

  return NULL;
}

static VALUE grpc_rb_channel_get_connectivity_state(int argc, VALUE* argv,
                                                    VALUE self) {
  VALUE try_to_connect_param = Qfalse;
  grpc_rb_channel* wrapper = NULL;
  get_state_stack stack;

  rb_scan_args(argc, argv, "01", &try_to_connect_param);

  TypedData_Get_Struct(self, grpc_rb_channel, &grpc_channel_data_type, wrapper);
  if (wrapper->bg_wrapped == NULL) {
    rb_raise(rb_eRuntimeError, "closed!");
    return Qnil;
  }

  stack.bg = wrapper->bg_wrapped;
  stack.try_to_connect = RTEST(try_to_connect_param) ? 1 : 0;
  rb_thread_call_without_gvl(get_state_without_gil, &stack, NULL, NULL);

  return LONG2NUM(stack.out);
}

typedef struct watch_state_stack {
  bg_watched_channel* bg_wrapped;
  gpr_timespec deadline;
  int last_state;
} watch_state_stack;

static void* wait_for_watch_state_op_complete_without_gvl(void* arg) {
  watch_state_stack* stack = (watch_state_stack*)arg;
  watch_state_op* op = NULL;
  void* success = (void*)0;

  gpr_mu_lock(&global_connection_polling_mu);

  if (g_abort_channel_polling || stack->bg_wrapped->channel_destroyed) {
    gpr_mu_unlock(&global_connection_polling_mu);
    return (void*)0;
  }
  op = gpr_zalloc(sizeof(watch_state_op));
  op->op_type = WATCH_STATE_API;
  grpc_channel_watch_connectivity_state(stack->bg_wrapped->channel,
                                        stack->last_state, stack->deadline,
                                        g_channel_polling_cq, op);

  while (!op->op.api_callback_args.called_back) {
    gpr_cv_wait(&global_connection_polling_cv, &global_connection_polling_mu,
                gpr_inf_future(GPR_CLOCK_REALTIME));
  }
  if (op->op.api_callback_args.success) {
    success = (void*)1;
  }
  gpr_free(op);
  gpr_mu_unlock(&global_connection_polling_mu);

  return success;
}
static void wait_for_watch_state_op_complete_unblocking_func(void* arg) {
  bg_watched_channel* bg = (bg_watched_channel*)arg;
  gpr_mu_lock(&global_connection_polling_mu);
  if (!bg->channel_destroyed) {
    grpc_channel_destroy(bg->channel);
    bg->channel_destroyed = 1;
  }
  gpr_mu_unlock(&global_connection_polling_mu);
}

static VALUE grpc_rb_channel_watch_connectivity_state(VALUE self,
                                                      VALUE last_state,
                                                      VALUE deadline) {
  grpc_rb_channel* wrapper = NULL;
  watch_state_stack stack;
  void* op_success = 0;

  grpc_ruby_fork_guard();
  TypedData_Get_Struct(self, grpc_rb_channel, &grpc_channel_data_type, wrapper);

  if (wrapper->bg_wrapped == NULL) {
    rb_raise(rb_eRuntimeError, "closed!");
    return Qnil;
  }

  if (!FIXNUM_P(last_state)) {
    rb_raise(
        rb_eTypeError,
        "bad type for last_state. want a GRPC::Core::ChannelState constant");
    return Qnil;
  }

  stack.bg_wrapped = wrapper->bg_wrapped;
  stack.deadline = grpc_rb_time_timeval(deadline, 0),
  stack.last_state = NUM2LONG(last_state);

  op_success = rb_thread_call_without_gvl(
      wait_for_watch_state_op_complete_without_gvl, &stack,
      wait_for_watch_state_op_complete_unblocking_func, wrapper->bg_wrapped);

  return op_success ? Qtrue : Qfalse;
}

static void grpc_rb_channel_maybe_recreate_channel_after_fork(
    grpc_rb_channel* wrapper, VALUE target) {

  bg_watched_channel* bg = wrapper->bg_wrapped;
  if (bg->channel_destroyed) {

    GRPC_RUBY_ASSERT(bg->refcount == 1);
    rb_thread_call_without_gvl(channel_safe_destroy_without_gil, bg, NULL,
                               NULL);

    const char* target_str = StringValueCStr(target);
    grpc_channel* channel;
    if (wrapper->credentials == Qnil) {
      grpc_channel_credentials* insecure_creds =
          grpc_insecure_credentials_create();
      channel = grpc_channel_create(target_str, insecure_creds, &wrapper->args);
      grpc_channel_credentials_release(insecure_creds);
    } else {
      grpc_channel_credentials* creds;
      if (grpc_rb_is_channel_credentials(wrapper->credentials)) {
        creds = grpc_rb_get_wrapped_channel_credentials(wrapper->credentials);
      } else if (grpc_rb_is_xds_channel_credentials(wrapper->credentials)) {
        creds =
            grpc_rb_get_wrapped_xds_channel_credentials(wrapper->credentials);
      } else {
        rb_raise(rb_eTypeError,
                 "failed to re-create channel after fork: bad creds, want "
                 "ChannelCredentials or XdsChannelCredentials");
        return;
      }
      channel = grpc_channel_create(target_str, creds, &wrapper->args);
    }

    channel_init_try_register_stack stack;
    stack.channel = channel;
    stack.wrapper = wrapper;
    rb_thread_call_without_gvl(
        channel_init_try_register_connection_polling_without_gil, &stack, NULL,
        NULL);
  }
}

static VALUE grpc_rb_channel_create_call(VALUE self, VALUE parent, VALUE mask,
                                         VALUE method, VALUE host,
                                         VALUE deadline) {
  VALUE res = Qnil;
  grpc_rb_channel* wrapper = NULL;
  grpc_call* call = NULL;
  grpc_call* parent_call = NULL;
  grpc_completion_queue* cq = NULL;
  int flags = GRPC_PROPAGATE_DEFAULTS;
  grpc_slice method_slice;
  grpc_slice host_slice;
  grpc_slice* host_slice_ptr = NULL;
  char* tmp_str = NULL;

  grpc_ruby_fork_guard();
  if (host != Qnil) {
    host_slice =
        grpc_slice_from_copied_buffer(RSTRING_PTR(host), RSTRING_LEN(host));
    host_slice_ptr = &host_slice;
  }
  if (mask != Qnil) {
    flags = NUM2UINT(mask);
  }
  if (parent != Qnil) {
    parent_call = grpc_rb_get_wrapped_call(parent);
  }

  TypedData_Get_Struct(self, grpc_rb_channel, &grpc_channel_data_type, wrapper);
  if (wrapper->bg_wrapped == NULL) {
    rb_raise(rb_eRuntimeError, "closed!");
    return Qnil;
  }

  rb_mutex_lock(rb_ivar_get(self, id_channel_recreation_mu));
  grpc_rb_channel_maybe_recreate_channel_after_fork(
      wrapper, rb_ivar_get(self, id_target));
  rb_mutex_unlock(rb_ivar_get(self, id_channel_recreation_mu));

  cq = grpc_completion_queue_create_for_pluck(NULL);
  method_slice =
      grpc_slice_from_copied_buffer(RSTRING_PTR(method), RSTRING_LEN(method));
  call = grpc_channel_create_call(wrapper->bg_wrapped->channel, parent_call,
                                  flags, cq, method_slice, host_slice_ptr,
                                  grpc_rb_time_timeval(deadline,
                                                        0),
                                  NULL);

  if (call == NULL) {
    tmp_str = grpc_slice_to_c_string(method_slice);
    rb_raise(rb_eRuntimeError, "cannot create call with method %s", tmp_str);
    return Qnil;
  }

  grpc_slice_unref(method_slice);
  if (host_slice_ptr != NULL) {
    grpc_slice_unref(host_slice);
  }

  res = grpc_rb_wrap_call(call, cq);

  rb_ivar_set(res, id_channel, self);
  return res;
}

static VALUE grpc_rb_channel_destroy(VALUE self) {
  grpc_rb_channel* wrapper = NULL;

  TypedData_Get_Struct(self, grpc_rb_channel, &grpc_channel_data_type, wrapper);
  if (wrapper->bg_wrapped != NULL) {
    rb_thread_call_without_gvl(channel_safe_destroy_without_gil,
                               wrapper->bg_wrapped, NULL, NULL);
    wrapper->bg_wrapped = NULL;
  }

  return Qnil;
}

static VALUE grpc_rb_channel_get_target(VALUE self) {
  grpc_rb_channel* wrapper = NULL;
  VALUE res = Qnil;
  char* target = NULL;

  TypedData_Get_Struct(self, grpc_rb_channel, &grpc_channel_data_type, wrapper);
  target = grpc_channel_get_target(wrapper->bg_wrapped->channel);
  res = rb_str_new2(target);
  gpr_free(target);

  return res;
}

static int bg_watched_channel_list_lookup(bg_watched_channel* target) {
  bg_watched_channel* cur = bg_watched_channel_list_head;

  while (cur != NULL) {
    if (cur == target) {
      return 1;
    }
    cur = cur->next;
  }

  return 0;
}

static bg_watched_channel* bg_watched_channel_list_create_and_add(
    grpc_channel* channel) {
  bg_watched_channel* watched = gpr_zalloc(sizeof(bg_watched_channel));

  watched->channel = channel;
  watched->next = bg_watched_channel_list_head;
  watched->refcount = 1;
  bg_watched_channel_list_head = watched;
  return watched;
}

static void bg_watched_channel_list_free_and_remove(
    bg_watched_channel* target) {
  bg_watched_channel* bg = NULL;

  GRPC_RUBY_ASSERT(bg_watched_channel_list_lookup(target));
  GRPC_RUBY_ASSERT(target->channel_destroyed && target->refcount == 0);
  if (bg_watched_channel_list_head == target) {
    bg_watched_channel_list_head = target->next;
    gpr_free(target);
    return;
  }
  bg = bg_watched_channel_list_head;
  while (bg != NULL && bg->next != NULL) {
    if (bg->next == target) {
      bg->next = bg->next->next;
      gpr_free(target);
      return;
    }
    bg = bg->next;
  }
  GRPC_RUBY_ASSERT(0);
}

static void* channel_init_try_register_connection_polling_without_gil(
    void* arg) {
  channel_init_try_register_stack* stack =
      (channel_init_try_register_stack*)arg;

  gpr_mu_lock(&global_connection_polling_mu);
  stack->wrapper->bg_wrapped =
      bg_watched_channel_list_create_and_add(stack->channel);
  grpc_rb_channel_try_register_connection_polling(stack->wrapper->bg_wrapped);
  gpr_mu_unlock(&global_connection_polling_mu);
  return NULL;
}

static void grpc_rb_channel_try_register_connection_polling(
    bg_watched_channel* bg) {
  grpc_connectivity_state conn_state;
  watch_state_op* op = NULL;
  if (bg->refcount == 0) {
    GRPC_RUBY_ASSERT(bg->channel_destroyed);
    bg_watched_channel_list_free_and_remove(bg);
    return;
  }
  GRPC_RUBY_ASSERT(bg->refcount == 1);
  if (bg->channel_destroyed || g_abort_channel_polling) {
    return;
  }
  conn_state = grpc_channel_check_connectivity_state(bg->channel, 0);
  if (conn_state == GRPC_CHANNEL_SHUTDOWN) {
    return;
  }
  GRPC_RUBY_ASSERT(bg_watched_channel_list_lookup(bg));

  bg->refcount++;
  op = gpr_zalloc(sizeof(watch_state_op));
  op->op_type = CONTINUOUS_WATCH;
  op->op.continuous_watch_callback_args.bg = bg;
  grpc_channel_watch_connectivity_state(bg->channel, conn_state,
                                        gpr_inf_future(GPR_CLOCK_REALTIME),
                                        g_channel_polling_cq, op);
}

static void* run_poll_channels_loop_no_gil(void* arg) {
  grpc_event event;
  watch_state_op* op = NULL;
  bg_watched_channel* bg = NULL;
  (void)arg;
  grpc_absl_log(GPR_DEBUG, "GRPC_RUBY: run_poll_channels_loop_no_gil - begin");

  gpr_mu_lock(&global_connection_polling_mu);
  gpr_cv_broadcast(&global_connection_polling_cv);
  gpr_mu_unlock(&global_connection_polling_mu);

  for (;;) {
    event = grpc_completion_queue_next(
        g_channel_polling_cq, gpr_inf_future(GPR_CLOCK_REALTIME), NULL);
    if (event.type == GRPC_QUEUE_SHUTDOWN) {
      break;
    }
    gpr_mu_lock(&global_connection_polling_mu);
    if (event.type == GRPC_OP_COMPLETE) {
      op = (watch_state_op*)event.tag;
      if (op->op_type == CONTINUOUS_WATCH) {
        bg = (bg_watched_channel*)op->op.continuous_watch_callback_args.bg;
        bg->refcount--;
        grpc_rb_channel_try_register_connection_polling(bg);
        gpr_free(op);
      } else if (op->op_type == WATCH_STATE_API) {
        grpc_rb_channel_watch_connection_state_op_complete(
            (watch_state_op*)event.tag, event.success);
      } else {
        GRPC_RUBY_ASSERT(0);
      }
    }
    gpr_mu_unlock(&global_connection_polling_mu);
  }
  grpc_completion_queue_destroy(g_channel_polling_cq);
  grpc_absl_log(
      GPR_DEBUG,
      "GRPC_RUBY: run_poll_channels_loop_no_gil - exit connection polling "
      "loop");
  return NULL;
}

static void run_poll_channels_loop_unblocking_func(void* arg) {
  run_poll_channels_loop_unblocking_func_wrapper(arg);
}

static void* run_poll_channels_loop_unblocking_func_wrapper(void* arg) {
  bg_watched_channel* bg = NULL;
  (void)arg;

  gpr_mu_lock(&global_connection_polling_mu);
  grpc_absl_log(
      GPR_DEBUG,
      "GRPC_RUBY: run_poll_channels_loop_unblocking_func - begin aborting "
      "connection polling");

  if (g_abort_channel_polling) {
    gpr_mu_unlock(&global_connection_polling_mu);
    return NULL;
  }
  g_abort_channel_polling = 1;

  bg = bg_watched_channel_list_head;
  while (bg != NULL) {
    if (!bg->channel_destroyed) {
      grpc_channel_destroy(bg->channel);
      bg->channel_destroyed = 1;
    }
    bg = bg->next;
  }

  grpc_absl_log_int(
      GPR_DEBUG,
      "GRPC_RUBY: cq shutdown on global polling cq. pid: ", getpid());
  grpc_completion_queue_shutdown(g_channel_polling_cq);
  gpr_cv_broadcast(&global_connection_polling_cv);
  gpr_mu_unlock(&global_connection_polling_mu);
  grpc_absl_log(
      GPR_DEBUG,
      "GRPC_RUBY: run_poll_channels_loop_unblocking_func - end aborting "
      "connection polling");
  return NULL;
}

static VALUE run_poll_channels_loop(void* arg) {
  (void)arg;
  grpc_absl_log(
      GPR_DEBUG,
      "GRPC_RUBY: run_poll_channels_loop - create connection polling thread");
  rb_thread_call_without_gvl(run_poll_channels_loop_no_gil, NULL,
                             run_poll_channels_loop_unblocking_func, NULL);
  return Qnil;
}

static void* set_abort_channel_polling_without_gil(void* arg) {
  (void)arg;
  gpr_mu_lock(&global_connection_polling_mu);
  g_abort_channel_polling = 1;
  gpr_cv_broadcast(&global_connection_polling_cv);
  gpr_mu_unlock(&global_connection_polling_mu);
  return NULL;
}

static void do_basic_init() {
  gpr_mu_init(&global_connection_polling_mu);
  gpr_cv_init(&global_connection_polling_cv);
}

void grpc_rb_channel_polling_thread_start() {
  gpr_once_init(&g_once_init, do_basic_init);
  GRPC_RUBY_ASSERT(!RTEST(g_channel_polling_thread));
  GRPC_RUBY_ASSERT(!g_abort_channel_polling);
  GRPC_RUBY_ASSERT(g_channel_polling_cq == NULL);

  g_channel_polling_cq = grpc_completion_queue_create_for_next(NULL);
  g_channel_polling_thread = rb_thread_create(run_poll_channels_loop, NULL);

  if (!RTEST(g_channel_polling_thread)) {
    grpc_absl_log(GPR_ERROR,
                  "GRPC_RUBY: failed to spawn channel polling thread");
    rb_thread_call_without_gvl(set_abort_channel_polling_without_gil, NULL,
                               NULL, NULL);
    return;
  }
}

void grpc_rb_channel_polling_thread_stop() {
  if (!RTEST(g_channel_polling_thread)) {
    grpc_absl_log(
        GPR_ERROR,
        "GRPC_RUBY: channel polling thread stop: thread was not started");
    return;
  }
  rb_thread_call_without_gvl(run_poll_channels_loop_unblocking_func_wrapper,
                             NULL, NULL, NULL);
  rb_funcall(g_channel_polling_thread, rb_intern("join"), 0);

  g_channel_polling_thread = Qnil;
  g_abort_channel_polling = false;
  g_channel_polling_cq = NULL;
}

static void Init_grpc_propagate_masks() {

  VALUE grpc_rb_mPropagateMasks =
      rb_define_module_under(grpc_rb_mGrpcCore, "PropagateMasks");
  rb_define_const(grpc_rb_mPropagateMasks, "DEADLINE",
                  UINT2NUM(GRPC_PROPAGATE_DEADLINE));
  rb_define_const(grpc_rb_mPropagateMasks, "CENSUS_STATS_CONTEXT",
                  UINT2NUM(GRPC_PROPAGATE_CENSUS_STATS_CONTEXT));
  rb_define_const(grpc_rb_mPropagateMasks, "CENSUS_TRACING_CONTEXT",
                  UINT2NUM(GRPC_PROPAGATE_CENSUS_TRACING_CONTEXT));
  rb_define_const(grpc_rb_mPropagateMasks, "CANCELLATION",
                  UINT2NUM(GRPC_PROPAGATE_CANCELLATION));
  rb_define_const(grpc_rb_mPropagateMasks, "DEFAULTS",
                  UINT2NUM(GRPC_PROPAGATE_DEFAULTS));
}

static void Init_grpc_connectivity_states() {

  VALUE grpc_rb_mConnectivityStates =
      rb_define_module_under(grpc_rb_mGrpcCore, "ConnectivityStates");
  rb_define_const(grpc_rb_mConnectivityStates, "IDLE",
                  LONG2NUM(GRPC_CHANNEL_IDLE));
  rb_define_const(grpc_rb_mConnectivityStates, "CONNECTING",
                  LONG2NUM(GRPC_CHANNEL_CONNECTING));
  rb_define_const(grpc_rb_mConnectivityStates, "READY",
                  LONG2NUM(GRPC_CHANNEL_READY));
  rb_define_const(grpc_rb_mConnectivityStates, "TRANSIENT_FAILURE",
                  LONG2NUM(GRPC_CHANNEL_TRANSIENT_FAILURE));
  rb_define_const(grpc_rb_mConnectivityStates, "FATAL_FAILURE",
                  LONG2NUM(GRPC_CHANNEL_SHUTDOWN));
}

void Init_grpc_channel() {
  rb_global_variable(&g_channel_polling_thread);
  grpc_rb_cChannelArgs = rb_define_class("TmpChannelArgs", rb_cObject);
  rb_undef_alloc_func(grpc_rb_cChannelArgs);
  grpc_rb_cChannel =
      rb_define_class_under(grpc_rb_mGrpcCore, "Channel", rb_cObject);

  rb_define_alloc_func(grpc_rb_cChannel, grpc_rb_channel_alloc);

  rb_define_method(grpc_rb_cChannel, "initialize", grpc_rb_channel_init, -1);
  rb_define_method(grpc_rb_cChannel, "initialize_copy",
                   grpc_rb_cannot_init_copy, 1);

  rb_define_method(grpc_rb_cChannel, "connectivity_state",
                   grpc_rb_channel_get_connectivity_state, -1);
  rb_define_method(grpc_rb_cChannel, "watch_connectivity_state",
                   grpc_rb_channel_watch_connectivity_state, 2);
  rb_define_method(grpc_rb_cChannel, "create_call", grpc_rb_channel_create_call,
                   5);
  rb_define_method(grpc_rb_cChannel, "target", grpc_rb_channel_get_target, 0);
  rb_define_method(grpc_rb_cChannel, "destroy", grpc_rb_channel_destroy, 0);
  rb_define_alias(grpc_rb_cChannel, "close", "destroy");

  id_channel = rb_intern("__channel");
  id_target = rb_intern("__target");
  id_channel_recreation_mu = rb_intern("__channel_recreation_mu");
  rb_define_const(grpc_rb_cChannel, "SSL_TARGET",
                  ID2SYM(rb_intern(GRPC_SSL_TARGET_NAME_OVERRIDE_ARG)));
  rb_define_const(grpc_rb_cChannel, "ENABLE_CENSUS",
                  ID2SYM(rb_intern(GRPC_ARG_ENABLE_CENSUS)));
  rb_define_const(grpc_rb_cChannel, "MAX_CONCURRENT_STREAMS",
                  ID2SYM(rb_intern(GRPC_ARG_MAX_CONCURRENT_STREAMS)));
  rb_define_const(grpc_rb_cChannel, "MAX_MESSAGE_LENGTH",
                  ID2SYM(rb_intern(GRPC_ARG_MAX_RECEIVE_MESSAGE_LENGTH)));
  id_insecure_channel = rb_intern("this_channel_is_insecure");
  Init_grpc_propagate_masks();
  Init_grpc_connectivity_states();
}

grpc_channel* grpc_rb_get_wrapped_channel(VALUE v) {
  grpc_rb_channel* wrapper = NULL;
  TypedData_Get_Struct(v, grpc_rb_channel, &grpc_channel_data_type, wrapper);
  return wrapper->bg_wrapped->channel;
}

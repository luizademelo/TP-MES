
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

#include "rb_server.h"

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/support/atm.h>
#include <grpc/support/log.h>

#include "rb_byte_buffer.h"
#include "rb_call.h"
#include "rb_channel_args.h"
#include "rb_completion_queue.h"
#include "rb_grpc.h"
#include "rb_grpc_imports.generated.h"
#include "rb_server_credentials.h"
#include "rb_xds_server_credentials.h"

static VALUE grpc_rb_cServer = Qnil;

static ID id_at;

static VALUE id_insecure_server;

typedef struct grpc_rb_server {

  grpc_server* wrapped;
  grpc_completion_queue* queue;
  int destroy_done;
} grpc_rb_server;

static void grpc_rb_server_shutdown_and_notify_internal(grpc_rb_server* server,
                                                        gpr_timespec deadline) {
  grpc_event ev;
  void* tag = &ev;
  if (server->wrapped != NULL) {
    grpc_server_shutdown_and_notify(server->wrapped, server->queue, tag);

    ev = rb_completion_queue_pluck(server->queue, tag, deadline, NULL, NULL);
    if (ev.type == GRPC_QUEUE_TIMEOUT) {
      grpc_server_cancel_all_calls(server->wrapped);
      ev = rb_completion_queue_pluck(
          server->queue, tag, gpr_inf_future(GPR_CLOCK_REALTIME), NULL, NULL);
    }
    if (ev.type != GRPC_OP_COMPLETE) {
      grpc_absl_log_int(
          GPR_DEBUG,
          "GRPC_RUBY: bad grpc_server_shutdown_and_notify result:", ev.type);
    }
  }
}

static void grpc_rb_server_maybe_destroy(grpc_rb_server* server) {

  if (!server->destroy_done) {
    server->destroy_done = 1;
    if (server->wrapped != NULL) {
      grpc_server_destroy(server->wrapped);
      grpc_rb_completion_queue_destroy(server->queue);
      server->wrapped = NULL;
      server->queue = NULL;
    }
  }
}

static void grpc_rb_server_free_internal(void* p) {
  grpc_rb_server* svr = NULL;
  gpr_timespec deadline;
  if (p == NULL) {
    return;
  };
  svr = (grpc_rb_server*)p;

  deadline = gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                          gpr_time_from_seconds(2, GPR_TIMESPAN));

  grpc_rb_server_shutdown_and_notify_internal(svr, deadline);
  grpc_rb_server_maybe_destroy(svr);

  xfree(p);
}

static void grpc_rb_server_free(void* p) { grpc_rb_server_free_internal(p); }

static const rb_data_type_t grpc_rb_server_data_type = {
    "grpc_server",
    {GRPC_RB_GC_NOT_MARKED,
     grpc_rb_server_free,
     GRPC_RB_MEMSIZE_UNAVAILABLE,
     {NULL, NULL}},
    NULL,
    NULL,
#ifdef RUBY_TYPED_FREE_IMMEDIATELY

    0,
#endif
};

static VALUE grpc_rb_server_alloc(VALUE cls) {
  grpc_ruby_init();
  grpc_rb_server* wrapper = ALLOC(grpc_rb_server);
  wrapper->wrapped = NULL;
  wrapper->destroy_done = 0;
  return TypedData_Wrap_Struct(cls, &grpc_rb_server_data_type, wrapper);
}

static VALUE grpc_rb_server_init(VALUE self, VALUE channel_args) {
  grpc_completion_queue* cq = NULL;
  grpc_rb_server* wrapper = NULL;
  grpc_server* srv = NULL;
  grpc_channel_args args;
  MEMZERO(&args, grpc_channel_args, 1);

  cq = grpc_completion_queue_create_for_pluck(NULL);
  TypedData_Get_Struct(self, grpc_rb_server, &grpc_rb_server_data_type,
                       wrapper);
  grpc_rb_hash_convert_to_channel_args(channel_args, &args);
  srv = grpc_server_create(&args, NULL);
  grpc_rb_channel_args_destroy(&args);
  if (srv == NULL) {
    rb_raise(rb_eRuntimeError, "could not create a gRPC server, not sure why");
  }
  grpc_server_register_completion_queue(srv, cq, NULL);
  wrapper->wrapped = srv;
  wrapper->queue = cq;

  return self;
}

typedef struct request_call_stack {
  grpc_call_details details;
  grpc_metadata_array md_ary;
} request_call_stack;

static void grpc_request_call_stack_init(request_call_stack* st) {
  MEMZERO(st, request_call_stack, 1);
  grpc_metadata_array_init(&st->md_ary);
  grpc_call_details_init(&st->details);
}

static void grpc_request_call_stack_cleanup(request_call_stack* st) {
  grpc_metadata_array_destroy(&st->md_ary);
  grpc_call_details_destroy(&st->details);
}

struct server_request_call_args {
  grpc_rb_server* server;
  grpc_completion_queue* call_queue;
  request_call_stack st;
};

static void shutdown_server_unblock_func(void* arg) {
  grpc_rb_server* server = (grpc_rb_server*)arg;
  grpc_absl_log(GPR_DEBUG, "GRPC_RUBY: shutdown_server_unblock_func");
  GRPC_RUBY_ASSERT(server->wrapped != NULL);
  grpc_event event;
  void* tag = &event;
  grpc_server_shutdown_and_notify(server->wrapped, server->queue, tag);
  grpc_server_cancel_all_calls(server->wrapped);

  event = grpc_completion_queue_pluck(server->queue, tag,
                                      gpr_inf_future(GPR_CLOCK_REALTIME), NULL);
  grpc_absl_log_int(
      GPR_DEBUG,
      "GRPC_RUBY: shutdown_server_unblock_func pluck event.type: ", event.type);
  grpc_absl_log_int(
      GPR_DEBUG,
      "GRPC_RUBY: shutdown_server_unblock_func event.success: ", event.success);
}

static VALUE grpc_rb_server_request_call_try(VALUE value_args) {
  grpc_rb_fork_unsafe_begin();
  struct server_request_call_args* args =
      (struct server_request_call_args*)value_args;

  grpc_call* call = NULL;
  void* tag = (void*)&args->st;

  args->call_queue = grpc_completion_queue_create_for_pluck(NULL);
  grpc_request_call_stack_init(&args->st);

  grpc_call_error err = grpc_server_request_call(
      args->server->wrapped, &call, &args->st.details, &args->st.md_ary,
      args->call_queue, args->server->queue, tag);
  if (err != GRPC_CALL_OK) {
    rb_raise(grpc_rb_eCallError,
             "grpc_server_request_call failed: %s (code=%d)",
             grpc_call_error_detail_of(err), err);
  }

  grpc_event ev = rb_completion_queue_pluck(
      args->server->queue, tag, gpr_inf_future(GPR_CLOCK_REALTIME),
      shutdown_server_unblock_func, args->server);
  if (!ev.success) {
    rb_raise(grpc_rb_eCallError, "request_call completion failed");
  }

  gpr_timespec deadline =
      gpr_convert_clock_type(args->st.details.deadline, GPR_CLOCK_REALTIME);
  VALUE result =
      rb_struct_new(grpc_rb_sNewServerRpc,
                    grpc_rb_slice_to_ruby_string(args->st.details.method),
                    grpc_rb_slice_to_ruby_string(args->st.details.host),
                    rb_funcall(rb_cTime, id_at, 2, INT2NUM(deadline.tv_sec),
                               INT2NUM(deadline.tv_nsec / 1000)),
                    grpc_rb_md_ary_to_h(&args->st.md_ary),
                    grpc_rb_wrap_call(call, args->call_queue), NULL);
  args->call_queue = NULL;
  return result;
}

static VALUE grpc_rb_server_request_call_ensure(VALUE value_args) {
  grpc_rb_fork_unsafe_end();
  struct server_request_call_args* args =
      (struct server_request_call_args*)value_args;

  if (args->call_queue) {
    grpc_rb_completion_queue_destroy(args->call_queue);
  }

  grpc_request_call_stack_cleanup(&args->st);

  return Qnil;
}

static VALUE grpc_rb_server_request_call(VALUE self) {
  grpc_rb_server* s;
  TypedData_Get_Struct(self, grpc_rb_server, &grpc_rb_server_data_type, s);
  grpc_ruby_fork_guard();
  if (s->wrapped == NULL) {
    rb_raise(rb_eRuntimeError, "destroyed!");
  }
  struct server_request_call_args args = {.server = s, .call_queue = NULL};
  return rb_ensure(grpc_rb_server_request_call_try, (VALUE)&args,
                   grpc_rb_server_request_call_ensure, (VALUE)&args);
}

static VALUE grpc_rb_server_start(VALUE self) {
  grpc_rb_server* s = NULL;
  TypedData_Get_Struct(self, grpc_rb_server, &grpc_rb_server_data_type, s);
  grpc_ruby_fork_guard();
  if (s->wrapped == NULL) {
    rb_raise(rb_eRuntimeError, "destroyed!");
  } else {
    grpc_server_start(s->wrapped);
  }
  return Qnil;
}

static VALUE grpc_rb_server_shutdown_and_notify(VALUE self, VALUE timeout) {
  gpr_timespec deadline;
  grpc_rb_server* s = NULL;

  TypedData_Get_Struct(self, grpc_rb_server, &grpc_rb_server_data_type, s);
  if (TYPE(timeout) == T_NIL) {
    deadline = gpr_inf_future(GPR_CLOCK_REALTIME);
  } else {
    deadline = grpc_rb_time_timeval(timeout,  0);
  }

  grpc_rb_server_shutdown_and_notify_internal(s, deadline);

  return Qnil;
}

static VALUE grpc_rb_server_destroy(VALUE self) {
  grpc_rb_server* s = NULL;
  TypedData_Get_Struct(self, grpc_rb_server, &grpc_rb_server_data_type, s);
  grpc_rb_server_maybe_destroy(s);
  return Qnil;
}

static VALUE grpc_rb_server_add_http2_port(VALUE self, VALUE port,
                                           VALUE rb_creds) {
  grpc_rb_server* s = NULL;
  grpc_server_credentials* creds = NULL;
  int recvd_port = 0;

  TypedData_Get_Struct(self, grpc_rb_server, &grpc_rb_server_data_type, s);
  if (s->wrapped == NULL) {
    rb_raise(rb_eRuntimeError, "destroyed!");
    return Qnil;
  } else if (TYPE(rb_creds) == T_SYMBOL) {
    if (id_insecure_server != SYM2ID(rb_creds)) {
      rb_raise(rb_eTypeError, "bad creds symbol, want :this_port_is_insecure");
      return Qnil;
    }
    grpc_server_credentials* insecure_creds =
        grpc_insecure_server_credentials_create();
    recvd_port = grpc_server_add_http2_port(s->wrapped, StringValueCStr(port),
                                            insecure_creds);
    grpc_server_credentials_release(insecure_creds);
    if (recvd_port == 0) {
      rb_raise(rb_eRuntimeError,
               "could not add port %s to server, not sure why",
               StringValueCStr(port));
    }
  } else {
    // TODO: create a common parent class for all server-side credentials,

    if (grpc_rb_is_server_credentials(rb_creds)) {
      creds = grpc_rb_get_wrapped_server_credentials(rb_creds);
    } else if (grpc_rb_is_xds_server_credentials(rb_creds)) {
      creds = grpc_rb_get_wrapped_xds_server_credentials(rb_creds);
    } else {
      rb_raise(rb_eTypeError,
               "failed to create server because credentials parameter has an "
               "invalid type, want ServerCredentials or XdsServerCredentials");
    }
    recvd_port =
        grpc_server_add_http2_port(s->wrapped, StringValueCStr(port), creds);
    if (recvd_port == 0) {
      rb_raise(rb_eRuntimeError,
               "could not add secure port %s to server, not sure why",
               StringValueCStr(port));
    }
  }
  return INT2NUM(recvd_port);
}

void Init_grpc_server() {
  grpc_rb_cServer =
      rb_define_class_under(grpc_rb_mGrpcCore, "Server", rb_cObject);

  rb_define_alloc_func(grpc_rb_cServer, grpc_rb_server_alloc);

  rb_define_method(grpc_rb_cServer, "initialize", grpc_rb_server_init, 1);
  rb_define_method(grpc_rb_cServer, "initialize_copy", grpc_rb_cannot_init_copy,
                   1);

  rb_define_method(grpc_rb_cServer, "request_call", grpc_rb_server_request_call,
                   0);
  rb_define_method(grpc_rb_cServer, "start", grpc_rb_server_start, 0);
  rb_define_method(grpc_rb_cServer, "shutdown_and_notify",
                   grpc_rb_server_shutdown_and_notify, 1);
  rb_define_method(grpc_rb_cServer, "destroy", grpc_rb_server_destroy, 0);
  rb_define_alias(grpc_rb_cServer, "close", "destroy");
  rb_define_method(grpc_rb_cServer, "add_http2_port",
                   grpc_rb_server_add_http2_port, 2);
  id_at = rb_intern("at");
  id_insecure_server = rb_intern("this_port_is_insecure");
}

grpc_server* grpc_rb_get_wrapped_server(VALUE v) {
  grpc_rb_server* wrapper = NULL;
  TypedData_Get_Struct(v, grpc_rb_server, &grpc_rb_server_data_type, wrapper);
  return wrapper->wrapped;
}

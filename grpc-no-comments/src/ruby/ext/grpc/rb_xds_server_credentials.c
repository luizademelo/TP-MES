
/*
 *
 * Copyright 2021 gRPC authors.
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

#include "rb_xds_server_credentials.h"

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/support/log.h>

#include "rb_grpc.h"
#include "rb_grpc_imports.generated.h"
#include "rb_server_credentials.h"

static VALUE grpc_rb_cXdsServerCredentials = Qnil;

typedef struct grpc_rb_xds_server_credentials {

  VALUE mark;

  grpc_server_credentials* wrapped;
} grpc_rb_xds_server_credentials;

static void grpc_rb_xds_server_credentials_free_internal(void* p) {
  grpc_rb_xds_server_credentials* wrapper = NULL;
  if (p == NULL) {
    return;
  };
  wrapper = (grpc_rb_xds_server_credentials*)p;

  if (wrapper->wrapped != NULL && wrapper->mark == Qnil) {
    grpc_server_credentials_release(wrapper->wrapped);
    wrapper->wrapped = NULL;
  }

  xfree(p);
}

static void grpc_rb_xds_server_credentials_free(void* p) {
  grpc_rb_xds_server_credentials_free_internal(p);
}

static void grpc_rb_xds_server_credentials_mark(void* p) {
  if (p == NULL) {
    return;
  }
  grpc_rb_xds_server_credentials* wrapper = (grpc_rb_xds_server_credentials*)p;

  if (wrapper->mark != Qnil) {
    rb_gc_mark(wrapper->mark);
  }
}

static const rb_data_type_t grpc_rb_xds_server_credentials_data_type = {
    "grpc_xds_server_credentials",
    {grpc_rb_xds_server_credentials_mark, grpc_rb_xds_server_credentials_free,
     GRPC_RB_MEMSIZE_UNAVAILABLE, NULL},
    NULL,
    NULL,
#ifdef RUBY_TYPED_FREE_IMMEDIATELY
    RUBY_TYPED_FREE_IMMEDIATELY
#endif
};

static VALUE grpc_rb_xds_server_credentials_alloc(VALUE cls) {
  grpc_ruby_init();
  grpc_rb_xds_server_credentials* wrapper =
      ALLOC(grpc_rb_xds_server_credentials);
  wrapper->wrapped = NULL;
  wrapper->mark = Qnil;
  return TypedData_Wrap_Struct(cls, &grpc_rb_xds_server_credentials_data_type,
                               wrapper);
}

static ID id_fallback_creds;

static VALUE grpc_rb_xds_server_credentials_init(VALUE self,
                                                 VALUE fallback_creds) {
  grpc_rb_xds_server_credentials* wrapper = NULL;
  grpc_server_credentials* creds = NULL;

  grpc_server_credentials* grpc_fallback_creds =
      grpc_rb_get_wrapped_server_credentials(fallback_creds);
  creds = grpc_xds_server_credentials_create(grpc_fallback_creds);

  if (creds == NULL) {
    rb_raise(rb_eRuntimeError,
             "the call to grpc_xds_server_credentials_create() failed, could "
             "not create a credentials, see "
             "https://github.com/grpc/grpc/blob/master/TROUBLESHOOTING.md for "
             "debugging tips");
    return Qnil;
  }
  TypedData_Get_Struct(self, grpc_rb_xds_server_credentials,
                       &grpc_rb_xds_server_credentials_data_type, wrapper);
  wrapper->wrapped = creds;

  rb_ivar_set(self, id_fallback_creds, fallback_creds);

  return self;
}

void Init_grpc_xds_server_credentials() {
  grpc_rb_cXdsServerCredentials = rb_define_class_under(
      grpc_rb_mGrpcCore, "XdsServerCredentials", rb_cObject);

  rb_define_alloc_func(grpc_rb_cXdsServerCredentials,
                       grpc_rb_xds_server_credentials_alloc);

  rb_define_method(grpc_rb_cXdsServerCredentials, "initialize",
                   grpc_rb_xds_server_credentials_init, 1);
  rb_define_method(grpc_rb_cXdsServerCredentials, "initialize_copy",
                   grpc_rb_cannot_init_copy, 1);

  id_fallback_creds = rb_intern("__fallback_creds");
}

grpc_server_credentials* grpc_rb_get_wrapped_xds_server_credentials(VALUE v) {
  grpc_rb_xds_server_credentials* wrapper = NULL;
  Check_TypedStruct(v, &grpc_rb_xds_server_credentials_data_type);
  TypedData_Get_Struct(v, grpc_rb_xds_server_credentials,
                       &grpc_rb_xds_server_credentials_data_type, wrapper);
  return wrapper->wrapped;
}

bool grpc_rb_is_xds_server_credentials(VALUE v) {
  return rb_typeddata_is_kind_of(v, &grpc_rb_xds_server_credentials_data_type);
}

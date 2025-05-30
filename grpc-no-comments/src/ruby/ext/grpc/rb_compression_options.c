
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

#include "rb_compression_options.h"

#include <grpc/compression.h>
#include <grpc/grpc.h>
#include <grpc/impl/codegen/compression_types.h>
#include <grpc/impl/grpc_types.h>
#include <grpc/support/alloc.h>
#include <grpc/support/log.h>
#include <grpc/support/string_util.h>
#include <string.h>

#include "rb_byte_buffer.h"
#include "rb_grpc.h"
#include "rb_grpc_imports.generated.h"

static VALUE grpc_rb_cCompressionOptions = Qnil;

static VALUE id_compress_level_none = Qnil;
static VALUE id_compress_level_low = Qnil;
static VALUE id_compress_level_medium = Qnil;
static VALUE id_compress_level_high = Qnil;

typedef struct grpc_rb_compression_options {

  grpc_compression_options* wrapped;
} grpc_rb_compression_options;

static void grpc_rb_compression_options_free_internal(void* p) {
  grpc_rb_compression_options* wrapper = NULL;
  if (p == NULL) {
    return;
  };
  wrapper = (grpc_rb_compression_options*)p;
  if (wrapper->wrapped != NULL) {
    gpr_free(wrapper->wrapped);
    wrapper->wrapped = NULL;
  }
  xfree(p);
}

static void grpc_rb_compression_options_free(void* p) {
  grpc_rb_compression_options_free_internal(p);
}

static rb_data_type_t grpc_rb_compression_options_data_type = {
    "grpc_compression_options",
    {NULL,
     grpc_rb_compression_options_free,
     GRPC_RB_MEMSIZE_UNAVAILABLE,
     {NULL, NULL}},
    NULL,
    NULL,
#ifdef RUBY_TYPED_FREE_IMMEDIATELY
    RUBY_TYPED_FREE_IMMEDIATELY
#endif
};

static VALUE grpc_rb_compression_options_alloc(VALUE cls) {
  grpc_ruby_init();
  grpc_rb_compression_options* wrapper = NULL;

  wrapper = gpr_malloc(sizeof(grpc_rb_compression_options));
  wrapper->wrapped = NULL;
  wrapper->wrapped = gpr_malloc(sizeof(grpc_compression_options));
  grpc_compression_options_init(wrapper->wrapped);

  return TypedData_Wrap_Struct(cls, &grpc_rb_compression_options_data_type,
                               wrapper);
}

VALUE grpc_rb_compression_options_disable_compression_algorithm_internal(
    VALUE self, VALUE algorithm_to_disable) {
  grpc_compression_algorithm compression_algorithm = 0;
  grpc_rb_compression_options* wrapper = NULL;

  TypedData_Get_Struct(self, grpc_rb_compression_options,
                       &grpc_rb_compression_options_data_type, wrapper);
  compression_algorithm =
      (grpc_compression_algorithm)NUM2INT(algorithm_to_disable);

  grpc_compression_options_disable_algorithm(wrapper->wrapped,
                                             compression_algorithm);

  return Qnil;
}

grpc_compression_level grpc_rb_compression_options_level_name_to_value_internal(
    VALUE level_name) {
  Check_Type(level_name, T_SYMBOL);

  if (id_compress_level_none == SYM2ID(level_name)) {
    return GRPC_COMPRESS_LEVEL_NONE;
  } else if (id_compress_level_low == SYM2ID(level_name)) {
    return GRPC_COMPRESS_LEVEL_LOW;
  } else if (id_compress_level_medium == SYM2ID(level_name)) {
    return GRPC_COMPRESS_LEVEL_MED;
  } else if (id_compress_level_high == SYM2ID(level_name)) {
    return GRPC_COMPRESS_LEVEL_HIGH;
  }

  rb_raise(rb_eArgError,
           "Unrecognized compression level name."
           "Valid compression level names are none, low, medium, and high.");

  return GRPC_COMPRESS_LEVEL_NONE;
}

void grpc_rb_compression_options_set_default_level(
    grpc_compression_options* options, VALUE new_level_name) {
  options->default_level.level =
      grpc_rb_compression_options_level_name_to_value_internal(new_level_name);
  options->default_level.is_set = 1;
}

void grpc_rb_compression_options_algorithm_name_to_value_internal(
    grpc_compression_algorithm* algorithm_value, VALUE algorithm_name) {
  grpc_slice name_slice;
  VALUE algorithm_name_as_string = Qnil;

  Check_Type(algorithm_name, T_SYMBOL);

  algorithm_name_as_string = rb_funcall(algorithm_name, rb_intern("to_s"), 0);

  name_slice =
      grpc_slice_from_copied_buffer(RSTRING_PTR(algorithm_name_as_string),
                                    RSTRING_LEN(algorithm_name_as_string));

  if (!grpc_compression_algorithm_parse(name_slice, algorithm_value)) {
    char* name_slice_str = grpc_slice_to_c_string(name_slice);
    char* error_message_str = NULL;
    VALUE error_message_ruby_str = Qnil;
    GRPC_RUBY_ASSERT(gpr_asprintf(&error_message_str,
                                  "Invalid compression algorithm name: %s",
                                  name_slice_str) != -1);
    gpr_free(name_slice_str);
    error_message_ruby_str =
        rb_str_new(error_message_str, strlen(error_message_str));
    gpr_free(error_message_str);
    rb_raise(rb_eNameError, "%s", StringValueCStr(error_message_ruby_str));
  }

  grpc_slice_unref(name_slice);
}

VALUE grpc_rb_compression_options_is_algorithm_enabled(VALUE self,
                                                       VALUE algorithm_name) {
  grpc_rb_compression_options* wrapper = NULL;
  grpc_compression_algorithm internal_algorithm_value;

  TypedData_Get_Struct(self, grpc_rb_compression_options,
                       &grpc_rb_compression_options_data_type, wrapper);
  grpc_rb_compression_options_algorithm_name_to_value_internal(
      &internal_algorithm_value, algorithm_name);

  if (grpc_compression_options_is_algorithm_enabled(wrapper->wrapped,
                                                    internal_algorithm_value)) {
    return Qtrue;
  }
  return Qfalse;
}

void grpc_rb_compression_options_set_default_algorithm(
    grpc_compression_options* options, VALUE algorithm_name) {
  grpc_rb_compression_options_algorithm_name_to_value_internal(
      &options->default_algorithm.algorithm, algorithm_name);
  options->default_algorithm.is_set = 1;
}

void grpc_rb_compression_options_disable_algorithm(
    grpc_compression_options* compression_options, VALUE algorithm_name) {
  grpc_compression_algorithm internal_algorithm_value;

  grpc_rb_compression_options_algorithm_name_to_value_internal(
      &internal_algorithm_value, algorithm_name);
  grpc_compression_options_disable_algorithm(compression_options,
                                             internal_algorithm_value);
}

VALUE grpc_rb_compression_options_to_hash(VALUE self) {
  grpc_rb_compression_options* wrapper = NULL;
  grpc_compression_options* compression_options = NULL;
  VALUE channel_arg_hash = rb_hash_new();
  VALUE key = Qnil;
  VALUE value = Qnil;

  TypedData_Get_Struct(self, grpc_rb_compression_options,
                       &grpc_rb_compression_options_data_type, wrapper);
  compression_options = wrapper->wrapped;

  if (compression_options->default_level.is_set) {
    key = rb_str_new2(GRPC_COMPRESSION_CHANNEL_DEFAULT_LEVEL);
    value = INT2NUM((int)compression_options->default_level.level);
    rb_hash_aset(channel_arg_hash, key, value);
  }

  if (compression_options->default_algorithm.is_set) {
    key = rb_str_new2(GRPC_COMPRESSION_CHANNEL_DEFAULT_ALGORITHM);
    value = INT2NUM((int)compression_options->default_algorithm.algorithm);
    rb_hash_aset(channel_arg_hash, key, value);
  }

  key = rb_str_new2(GRPC_COMPRESSION_CHANNEL_ENABLED_ALGORITHMS_BITSET);
  value = INT2NUM((int)compression_options->enabled_algorithms_bitset);
  rb_hash_aset(channel_arg_hash, key, value);

  return channel_arg_hash;
}

VALUE grpc_rb_compression_options_level_value_to_name_internal(
    grpc_compression_level compression_value) {
  switch (compression_value) {
    case GRPC_COMPRESS_LEVEL_NONE:
      return ID2SYM(id_compress_level_none);
    case GRPC_COMPRESS_LEVEL_LOW:
      return ID2SYM(id_compress_level_low);
    case GRPC_COMPRESS_LEVEL_MED:
      return ID2SYM(id_compress_level_medium);
    case GRPC_COMPRESS_LEVEL_HIGH:
      return ID2SYM(id_compress_level_high);
    default:
      rb_raise(
          rb_eArgError,
          "Failed to convert compression level value to name for value: %d",
          (int)compression_value);

      return Qnil;
  }
}

VALUE grpc_rb_compression_options_algorithm_value_to_name_internal(
    grpc_compression_algorithm internal_value) {
  const char* algorithm_name = NULL;

  if (!grpc_compression_algorithm_name(internal_value, &algorithm_name)) {
    rb_raise(rb_eArgError, "Failed to convert algorithm value to name");
  }

  return ID2SYM(rb_intern(algorithm_name));
}

VALUE grpc_rb_compression_options_get_default_algorithm(VALUE self) {
  grpc_compression_algorithm internal_value;
  grpc_rb_compression_options* wrapper = NULL;

  TypedData_Get_Struct(self, grpc_rb_compression_options,
                       &grpc_rb_compression_options_data_type, wrapper);

  if (wrapper->wrapped->default_algorithm.is_set) {
    internal_value = wrapper->wrapped->default_algorithm.algorithm;
    return grpc_rb_compression_options_algorithm_value_to_name_internal(
        internal_value);
  }

  return Qnil;
}

VALUE grpc_rb_compression_options_get_default_level(VALUE self) {
  grpc_compression_level internal_value;
  grpc_rb_compression_options* wrapper = NULL;

  TypedData_Get_Struct(self, grpc_rb_compression_options,
                       &grpc_rb_compression_options_data_type, wrapper);

  if (wrapper->wrapped->default_level.is_set) {
    internal_value = wrapper->wrapped->default_level.level;
    return grpc_rb_compression_options_level_value_to_name_internal(
        internal_value);
  }

  return Qnil;
}

VALUE grpc_rb_compression_options_get_disabled_algorithms(VALUE self) {
  VALUE disabled_algorithms = rb_ary_new();
  grpc_compression_algorithm internal_value;
  grpc_rb_compression_options* wrapper = NULL;

  TypedData_Get_Struct(self, grpc_rb_compression_options,
                       &grpc_rb_compression_options_data_type, wrapper);

  for (internal_value = GRPC_COMPRESS_NONE;
       internal_value < GRPC_COMPRESS_ALGORITHMS_COUNT; internal_value++) {
    if (!grpc_compression_options_is_algorithm_enabled(wrapper->wrapped,
                                                       internal_value)) {
      rb_ary_push(disabled_algorithms,
                  grpc_rb_compression_options_algorithm_value_to_name_internal(
                      internal_value));
    }
  }
  return disabled_algorithms;
}

VALUE grpc_rb_compression_options_init(int argc, VALUE* argv, VALUE self) {
  grpc_rb_compression_options* wrapper = NULL;
  VALUE default_algorithm = Qnil;
  VALUE default_level = Qnil;
  VALUE disabled_algorithms = Qnil;
  VALUE algorithm_name = Qnil;
  VALUE hash_arg = Qnil;

  rb_scan_args(argc, argv, "01", &hash_arg);

  if (hash_arg == Qnil) {
    return self;
  } else if (TYPE(hash_arg) != T_HASH || argc > 1) {
    rb_raise(rb_eArgError,
             "Invalid arguments. Expecting optional hash parameter");
  }

  TypedData_Get_Struct(self, grpc_rb_compression_options,
                       &grpc_rb_compression_options_data_type, wrapper);

  default_algorithm =
      rb_hash_aref(hash_arg, ID2SYM(rb_intern("default_algorithm")));
  if (default_algorithm != Qnil) {
    grpc_rb_compression_options_set_default_algorithm(wrapper->wrapped,
                                                      default_algorithm);
  }

  default_level = rb_hash_aref(hash_arg, ID2SYM(rb_intern("default_level")));
  if (default_level != Qnil) {
    grpc_rb_compression_options_set_default_level(wrapper->wrapped,
                                                  default_level);
  }

  disabled_algorithms =
      rb_hash_aref(hash_arg, ID2SYM(rb_intern("disabled_algorithms")));
  if (disabled_algorithms != Qnil) {
    Check_Type(disabled_algorithms, T_ARRAY);

    for (int i = 0; i < RARRAY_LEN(disabled_algorithms); i++) {
      algorithm_name = rb_ary_entry(disabled_algorithms, i);
      grpc_rb_compression_options_disable_algorithm(wrapper->wrapped,
                                                    algorithm_name);
    }
  }

  return self;
}

void Init_grpc_compression_options() {
  grpc_rb_cCompressionOptions = rb_define_class_under(
      grpc_rb_mGrpcCore, "CompressionOptions", rb_cObject);

  rb_define_alloc_func(grpc_rb_cCompressionOptions,
                       grpc_rb_compression_options_alloc);

  rb_define_method(grpc_rb_cCompressionOptions, "initialize",
                   grpc_rb_compression_options_init, -1);

  rb_define_method(grpc_rb_cCompressionOptions, "default_algorithm",
                   grpc_rb_compression_options_get_default_algorithm, 0);
  rb_define_method(grpc_rb_cCompressionOptions, "default_level",
                   grpc_rb_compression_options_get_default_level, 0);
  rb_define_method(grpc_rb_cCompressionOptions, "disabled_algorithms",
                   grpc_rb_compression_options_get_disabled_algorithms, 0);

  rb_define_method(grpc_rb_cCompressionOptions, "algorithm_enabled?",
                   grpc_rb_compression_options_is_algorithm_enabled, 1);

  rb_define_method(grpc_rb_cCompressionOptions, "to_hash",
                   grpc_rb_compression_options_to_hash, 0);
  rb_define_alias(grpc_rb_cCompressionOptions, "to_channel_arg_hash",
                  "to_hash");

  id_compress_level_none = rb_intern("none");
  id_compress_level_low = rb_intern("low");
  id_compress_level_medium = rb_intern("medium");
  id_compress_level_high = rb_intern("high");
}

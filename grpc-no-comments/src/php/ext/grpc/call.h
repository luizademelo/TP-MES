
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

#ifndef NET_GRPC_PHP_GRPC_CALL_H_
#define NET_GRPC_PHP_GRPC_CALL_H_

#include "php_grpc.h"

#include "channel.h"

extern zend_class_entry *grpc_ce_call;

PHP_GRPC_WRAP_OBJECT_START(wrapped_grpc_call)
  bool owned;
  grpc_call *wrapped;
  wrapped_grpc_channel* channel;
PHP_GRPC_WRAP_OBJECT_END(wrapped_grpc_call)

static inline wrapped_grpc_call
*wrapped_grpc_call_from_obj(zend_object *obj) {
  return (wrapped_grpc_call*)((char*)(obj) -
                              XtOffsetOf(wrapped_grpc_call, std));
}

zval *grpc_parse_metadata_array(grpc_metadata_array *metadata_array TSRMLS_DC);

zval *grpc_php_wrap_call(grpc_call *wrapped, bool owned TSRMLS_DC);

void grpc_init_call(TSRMLS_D);

bool create_metadata_array(zval *array, grpc_metadata_array *metadata);
void grpc_php_metadata_array_destroy_including_entries(
    grpc_metadata_array* array);
#endif


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

#include "call_credentials.h"

#include <ext/spl/spl_exceptions.h>
#include <zend_exceptions.h>

#include <grpc/support/log.h>
#include <grpc/support/string_util.h>

#include "call.h"

zend_class_entry *grpc_ce_call_credentials;
PHP_GRPC_DECLARE_OBJECT_HANDLER(call_credentials_ce_handlers)

PHP_GRPC_FREE_WRAPPED_FUNC_START(wrapped_grpc_call_credentials)
  if (p->wrapped != NULL) {
    grpc_call_credentials_release(p->wrapped);
  }
PHP_GRPC_FREE_WRAPPED_FUNC_END()

php_grpc_zend_object create_wrapped_grpc_call_credentials(
    zend_class_entry *class_type TSRMLS_DC) {
  PHP_GRPC_ALLOC_CLASS_OBJECT(wrapped_grpc_call_credentials);
  zend_object_std_init(&intern->std, class_type TSRMLS_CC);
  object_properties_init(&intern->std, class_type);
  PHP_GRPC_FREE_CLASS_OBJECT(wrapped_grpc_call_credentials,
                             call_credentials_ce_handlers);
}

zval *grpc_php_wrap_call_credentials(grpc_call_credentials
                                     *wrapped TSRMLS_DC) {
  zval *credentials_object;
  PHP_GRPC_MAKE_STD_ZVAL(credentials_object);
  object_init_ex(credentials_object, grpc_ce_call_credentials);
  wrapped_grpc_call_credentials *credentials =
    PHP_GRPC_GET_WRAPPED_OBJECT(wrapped_grpc_call_credentials,
                                credentials_object);
  credentials->wrapped = wrapped;
  return credentials_object;
}

PHP_METHOD(CallCredentials, createComposite) {
  zval *cred1_obj;
  zval *cred2_obj;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "OO", &cred1_obj,
                            grpc_ce_call_credentials, &cred2_obj,
                            grpc_ce_call_credentials) == FAILURE) {
    zend_throw_exception(spl_ce_InvalidArgumentException,
                         "createComposite expects 2 CallCredentials",
                         1 TSRMLS_CC);
    return;
  }
  wrapped_grpc_call_credentials *cred1 =
    PHP_GRPC_GET_WRAPPED_OBJECT(wrapped_grpc_call_credentials, cred1_obj);
  wrapped_grpc_call_credentials *cred2 =
    PHP_GRPC_GET_WRAPPED_OBJECT(wrapped_grpc_call_credentials, cred2_obj);
  grpc_call_credentials *creds =
    grpc_composite_call_credentials_create(cred1->wrapped, cred2->wrapped,
                                           NULL);
  zval *creds_object = grpc_php_wrap_call_credentials(creds TSRMLS_CC);
  RETURN_DESTROY_ZVAL(creds_object);
}

PHP_METHOD(CallCredentials, createFromPlugin) {
  zend_fcall_info *fci;
  zend_fcall_info_cache *fci_cache;

  fci = (zend_fcall_info *)malloc(sizeof(zend_fcall_info));
  fci_cache = (zend_fcall_info_cache *)malloc(sizeof(zend_fcall_info_cache));
  memset(fci, 0, sizeof(zend_fcall_info));
  memset(fci_cache, 0, sizeof(zend_fcall_info_cache));

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "f*", fci, fci_cache,
                            fci->params, fci->param_count) == FAILURE) {
    zend_throw_exception(spl_ce_InvalidArgumentException,
                         "createFromPlugin expects 1 callback", 1 TSRMLS_CC);
    free(fci);
    free(fci_cache);
    return;
  }

  plugin_state *state;
  state = (plugin_state *)malloc(sizeof(plugin_state));
  memset(state, 0, sizeof(plugin_state));

  state->fci = fci;
  state->fci_cache = fci_cache;

  grpc_metadata_credentials_plugin plugin;
  plugin.get_metadata = plugin_get_metadata;
  plugin.destroy = plugin_destroy_state;
  plugin.state = (void *)state;
  plugin.type = "";

  grpc_call_credentials *creds =
    grpc_metadata_credentials_create_from_plugin(plugin, GRPC_PRIVACY_AND_INTEGRITY, NULL);
  zval *creds_object = grpc_php_wrap_call_credentials(creds TSRMLS_CC);
  RETURN_DESTROY_ZVAL(creds_object);
}

int plugin_get_metadata(
    void *ptr, grpc_auth_metadata_context context,
    grpc_credentials_plugin_metadata_cb cb, void *user_data,
    grpc_metadata creds_md[GRPC_METADATA_CREDENTIALS_PLUGIN_SYNC_MAX],
    size_t *num_creds_md, grpc_status_code *status,
    const char **error_details) {
  TSRMLS_FETCH();

  plugin_state *state = (plugin_state *)ptr;

  zval *arg;
  PHP_GRPC_MAKE_STD_ZVAL(arg);
  object_init(arg);
  php_grpc_add_property_string(arg, "service_url", context.service_url, true);
  php_grpc_add_property_string(arg, "method_name", context.method_name, true);
  zval *retval = NULL;
  PHP_GRPC_MAKE_STD_ZVAL(retval);
  state->fci->params = arg;
  state->fci->retval = retval;
  state->fci->param_count = 1;

  PHP_GRPC_DELREF(arg);

  grpc_absl_log(GPR_INFO, "GRPC_PHP: call credentials plugin function - begin");

  zend_call_function(state->fci, state->fci_cache TSRMLS_CC);
  grpc_absl_log(GPR_INFO, "GRPC_PHP: call credentials plugin function - end");

  *num_creds_md = 0;
  *status = GRPC_STATUS_OK;
  *error_details = NULL;

  bool should_return = false;
  grpc_metadata_array metadata;

  if (retval == NULL || Z_TYPE_P(retval) != IS_ARRAY) {
    *status = GRPC_STATUS_INVALID_ARGUMENT;
    should_return = true;
  }
  if (!create_metadata_array(retval, &metadata)) {
    *status = GRPC_STATUS_INVALID_ARGUMENT;
    should_return = true;
    grpc_php_metadata_array_destroy_including_entries(&metadata);
  }

  if (retval != NULL) {
    zval_ptr_dtor(arg);
    zval_ptr_dtor(retval);
    PHP_GRPC_FREE_STD_ZVAL(arg);
    PHP_GRPC_FREE_STD_ZVAL(retval);
  }
  if (should_return) {
    return true;
  }

  if (metadata.count > GRPC_METADATA_CREDENTIALS_PLUGIN_SYNC_MAX) {
    *status = GRPC_STATUS_INTERNAL;
    *error_details = gpr_strdup(
        "PHP plugin credentials returned too many metadata entries");
    for (size_t i = 0; i < metadata.count; i++) {

      grpc_slice_unref(metadata.metadata[i].value);
    }
  } else {

    *num_creds_md = metadata.count;
    for (size_t i = 0; i < metadata.count; ++i) {
      creds_md[i] = metadata.metadata[i];
    }
  }

  grpc_metadata_array_destroy(&metadata);
  return true;
}

void plugin_destroy_state(void *ptr) {
  plugin_state *state = (plugin_state *)ptr;
  free(state->fci);
  free(state->fci_cache);
  free(state);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_createComposite, 0, 0, 2)
  ZEND_ARG_INFO(0, creds1)
  ZEND_ARG_INFO(0, creds2)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_createFromPlugin, 0, 0, 1)
  ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

static zend_function_entry call_credentials_methods[] = {
  PHP_ME(CallCredentials, createComposite, arginfo_createComposite,
         ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
  PHP_ME(CallCredentials, createFromPlugin, arginfo_createFromPlugin,
         ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
  PHP_FE_END
};

void grpc_init_call_credentials(TSRMLS_D) {
  zend_class_entry ce;
  INIT_CLASS_ENTRY(ce, "Grpc\\CallCredentials", call_credentials_methods);
  ce.create_object = create_wrapped_grpc_call_credentials;
  grpc_ce_call_credentials = zend_register_internal_class(&ce TSRMLS_CC);
  PHP_GRPC_INIT_HANDLER(wrapped_grpc_call_credentials,
                        call_credentials_ce_handlers);
}

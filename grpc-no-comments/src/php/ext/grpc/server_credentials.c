
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

#include "server_credentials.h"

#include <ext/spl/spl_exceptions.h>
#include <zend_exceptions.h>

zend_class_entry *grpc_ce_server_credentials;
PHP_GRPC_DECLARE_OBJECT_HANDLER(server_credentials_ce_handlers)

PHP_GRPC_FREE_WRAPPED_FUNC_START(wrapped_grpc_server_credentials)
  if (p->wrapped != NULL) {
    grpc_server_credentials_release(p->wrapped);
  }
PHP_GRPC_FREE_WRAPPED_FUNC_END()

php_grpc_zend_object create_wrapped_grpc_server_credentials(
    zend_class_entry *class_type TSRMLS_DC) {
  PHP_GRPC_ALLOC_CLASS_OBJECT(wrapped_grpc_server_credentials);
  zend_object_std_init(&intern->std, class_type TSRMLS_CC);
  object_properties_init(&intern->std, class_type);
  PHP_GRPC_FREE_CLASS_OBJECT(wrapped_grpc_server_credentials,
                             server_credentials_ce_handlers);
}

zval *grpc_php_wrap_server_credentials(grpc_server_credentials
                                       *wrapped TSRMLS_DC) {
  zval *server_credentials_object;
  PHP_GRPC_MAKE_STD_ZVAL(server_credentials_object);
  object_init_ex(server_credentials_object, grpc_ce_server_credentials);
  wrapped_grpc_server_credentials *server_credentials =
    PHP_GRPC_GET_WRAPPED_OBJECT(wrapped_grpc_server_credentials,
                                server_credentials_object);
  server_credentials->wrapped = wrapped;
  return server_credentials_object;
}

PHP_METHOD(ServerCredentials, createSsl) {
  char *pem_root_certs = 0;
  grpc_ssl_pem_key_cert_pair pem_key_cert_pair;

  php_grpc_int root_certs_length = 0;
  php_grpc_int private_key_length;
  php_grpc_int cert_chain_length;

  /* TODO: support multiple key cert pairs. */
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s!ss", &pem_root_certs,
                            &root_certs_length, &pem_key_cert_pair.private_key,
                            &private_key_length, &pem_key_cert_pair.cert_chain,
                            &cert_chain_length) == FAILURE) {
    zend_throw_exception(spl_ce_InvalidArgumentException,
                         "createSsl expects 3 strings", 1 TSRMLS_CC);
    return;
  }

/* TODO: add a client_certificate_request field in ServerCredentials and pass
   * it as the last parameter. */
  grpc_server_credentials *creds = grpc_ssl_server_credentials_create_ex(
      pem_root_certs, &pem_key_cert_pair, 1,
      GRPC_SSL_DONT_REQUEST_CLIENT_CERTIFICATE, NULL);
  zval *creds_object = grpc_php_wrap_server_credentials(creds TSRMLS_CC);
  RETURN_DESTROY_ZVAL(creds_object);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_createSsl, 0, 0, 3)
  ZEND_ARG_INFO(0, pem_root_certs)
  ZEND_ARG_INFO(0, pem_private_key)
  ZEND_ARG_INFO(0, pem_cert_chain)
ZEND_END_ARG_INFO()

static zend_function_entry server_credentials_methods[] = {
  PHP_ME(ServerCredentials, createSsl, arginfo_createSsl,
         ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
  PHP_FE_END
 };

void grpc_init_server_credentials(TSRMLS_D) {
  zend_class_entry ce;
  INIT_CLASS_ENTRY(ce, "Grpc\\ServerCredentials", server_credentials_methods);
  ce.create_object = create_wrapped_grpc_server_credentials;
  grpc_ce_server_credentials = zend_register_internal_class(&ce TSRMLS_CC);
  PHP_GRPC_INIT_HANDLER(wrapped_grpc_server_credentials,
                        server_credentials_ce_handlers);
}

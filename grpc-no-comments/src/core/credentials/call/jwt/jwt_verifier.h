
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_CALL_JWT_JWT_VERIFIER_H
#define GRPC_SRC_CORE_CREDENTIALS_CALL_JWT_JWT_VERIFIER_H

#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <stddef.h>

#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/util/json/json.h"
#include "src/core/util/time.h"

#define GRPC_OPENID_CONFIG_URL_SUFFIX "/.well-known/openid-configuration"
#define GRPC_GOOGLE_SERVICE_ACCOUNTS_EMAIL_DOMAIN "gserviceaccount.com"
#define GRPC_GOOGLE_SERVICE_ACCOUNTS_KEY_URL_PREFIX \
  "www.googleapis.com/robot/v1/metadata/x509"

typedef enum {
  GRPC_JWT_VERIFIER_OK = 0,
  GRPC_JWT_VERIFIER_BAD_SIGNATURE,
  GRPC_JWT_VERIFIER_BAD_FORMAT,
  GRPC_JWT_VERIFIER_BAD_AUDIENCE,
  GRPC_JWT_VERIFIER_KEY_RETRIEVAL_ERROR,
  GRPC_JWT_VERIFIER_TIME_CONSTRAINT_FAILURE,
  GRPC_JWT_VERIFIER_BAD_SUBJECT,
  GRPC_JWT_VERIFIER_GENERIC_ERROR
} grpc_jwt_verifier_status;

const char* grpc_jwt_verifier_status_to_string(grpc_jwt_verifier_status status);

typedef struct grpc_jwt_claims grpc_jwt_claims;

void grpc_jwt_claims_destroy(grpc_jwt_claims* claims);

const grpc_core::Json* grpc_jwt_claims_json(const grpc_jwt_claims* claims);

const char* grpc_jwt_claims_subject(const grpc_jwt_claims* claims);
const char* grpc_jwt_claims_issuer(const grpc_jwt_claims* claims);
const char* grpc_jwt_claims_id(const grpc_jwt_claims* claims);
const char* grpc_jwt_claims_audience(const grpc_jwt_claims* claims);
gpr_timespec grpc_jwt_claims_issued_at(const grpc_jwt_claims* claims);
gpr_timespec grpc_jwt_claims_expires_at(const grpc_jwt_claims* claims);
gpr_timespec grpc_jwt_claims_not_before(const grpc_jwt_claims* claims);

typedef struct grpc_jwt_verifier grpc_jwt_verifier;

struct grpc_jwt_verifier_email_domain_key_url_mapping {

  const char* email_domain;

  const char* key_url_prefix;
};

extern gpr_timespec grpc_jwt_verifier_clock_skew;
extern grpc_core::Duration grpc_jwt_verifier_max_delay;

grpc_jwt_verifier* grpc_jwt_verifier_create(
    const grpc_jwt_verifier_email_domain_key_url_mapping* mappings,
    size_t num_mappings);

void grpc_jwt_verifier_destroy(grpc_jwt_verifier* verifier);

typedef void (*grpc_jwt_verification_done_cb)(void* user_data,
                                              grpc_jwt_verifier_status status,
                                              grpc_jwt_claims* claims);

void grpc_jwt_verifier_verify(grpc_jwt_verifier* verifier,
                              grpc_pollset* pollset, const char* jwt,
                              const char* audience,
                              grpc_jwt_verification_done_cb cb,
                              void* user_data);

grpc_jwt_claims* grpc_jwt_claims_from_json(grpc_core::Json json);
grpc_jwt_verifier_status grpc_jwt_claims_check(const grpc_jwt_claims* claims,
                                               const char* audience);
const char* grpc_jwt_issuer_email_domain(const char* issuer);

#endif


// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_ALTS_CHECK_GCP_ENVIRONMENT_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_ALTS_CHECK_GCP_ENVIRONMENT_H

namespace grpc_core {
namespace internal {

char* read_bios_file(const char* bios_file);

bool check_bios_data(const char* bios_data);

}
}

bool grpc_alts_is_running_on_gcp();

#endif

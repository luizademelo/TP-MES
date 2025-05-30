
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_CLIENT_CHANNEL_BACKUP_POLLER_H
#define GRPC_SRC_CORE_CLIENT_CHANNEL_BACKUP_POLLER_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/iomgr_fwd.h"

void grpc_client_channel_global_init_backup_polling();

void grpc_client_channel_start_backup_polling(
    grpc_pollset_set* interested_parties);

void grpc_client_channel_stop_backup_polling(
    grpc_pollset_set* interested_parties);

#endif

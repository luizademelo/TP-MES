
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_POLLING_ENTITY_H
#define GRPC_SRC_CORE_LIB_IOMGR_POLLING_ENTITY_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/pollset.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/promise/context.h"

typedef enum grpc_pollset_tag {
  GRPC_POLLS_NONE,
  GRPC_POLLS_POLLSET,
  GRPC_POLLS_POLLSET_SET
} grpc_pollset_tag;

struct grpc_polling_entity {
  union {
    grpc_pollset* pollset = nullptr;
    grpc_pollset_set* pollset_set;
  } pollent;
  grpc_pollset_tag tag = GRPC_POLLS_NONE;
};

grpc_polling_entity grpc_polling_entity_create_from_pollset_set(
    grpc_pollset_set* pollset_set);
grpc_polling_entity grpc_polling_entity_create_from_pollset(
    grpc_pollset* pollset);

grpc_pollset* grpc_polling_entity_pollset(grpc_polling_entity* pollent);

grpc_pollset_set* grpc_polling_entity_pollset_set(grpc_polling_entity* pollent);

bool grpc_polling_entity_is_empty(const grpc_polling_entity* pollent);

void grpc_polling_entity_add_to_pollset_set(grpc_polling_entity* pollent,
                                            grpc_pollset_set* pss_dst);

void grpc_polling_entity_del_from_pollset_set(grpc_polling_entity* pollent,
                                              grpc_pollset_set* pss_dst);

std::string grpc_polling_entity_string(grpc_polling_entity* pollent);

namespace grpc_core {
template <>
struct ContextType<grpc_polling_entity> {};
}

#endif

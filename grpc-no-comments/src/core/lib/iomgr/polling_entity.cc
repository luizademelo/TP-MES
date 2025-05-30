
// Copyright 2016 gRPC authors.

#include "src/core/lib/iomgr/polling_entity.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>

#include "absl/log/check.h"
#include "absl/strings/str_format.h"
#include "src/core/util/crash.h"

grpc_polling_entity grpc_polling_entity_create_from_pollset_set(
    grpc_pollset_set* pollset_set) {
  grpc_polling_entity pollent;
  if (pollset_set == nullptr) {
    pollent.tag = GRPC_POLLS_NONE;
  } else {
    pollent.pollent.pollset_set = pollset_set;
    pollent.tag = GRPC_POLLS_POLLSET_SET;
  }
  return pollent;
}

grpc_polling_entity grpc_polling_entity_create_from_pollset(
    grpc_pollset* pollset) {
  grpc_polling_entity pollent;
  pollent.pollent.pollset = pollset;
  pollent.tag = GRPC_POLLS_POLLSET;
  return pollent;
}

grpc_pollset* grpc_polling_entity_pollset(grpc_polling_entity* pollent) {
  if (pollent->tag == GRPC_POLLS_POLLSET) {
    return pollent->pollent.pollset;
  }
  return nullptr;
}

grpc_pollset_set* grpc_polling_entity_pollset_set(
    grpc_polling_entity* pollent) {
  if (pollent->tag == GRPC_POLLS_POLLSET_SET) {
    return pollent->pollent.pollset_set;
  }
  return nullptr;
}

bool grpc_polling_entity_is_empty(const grpc_polling_entity* pollent) {
  return pollent->tag == GRPC_POLLS_NONE;
}

void grpc_polling_entity_add_to_pollset_set(grpc_polling_entity* pollent,
                                            grpc_pollset_set* pss_dst) {
  if (pollent->tag == GRPC_POLLS_POLLSET) {

    if (pollent->pollent.pollset != nullptr) {
      grpc_pollset_set_add_pollset(pss_dst, pollent->pollent.pollset);
    }
  } else if (pollent->tag == GRPC_POLLS_POLLSET_SET) {
    CHECK_NE(pollent->pollent.pollset_set, nullptr);
    grpc_pollset_set_add_pollset_set(pss_dst, pollent->pollent.pollset_set);
  } else if (pollent->tag == GRPC_POLLS_NONE) {

  } else {
    grpc_core::Crash(
        absl::StrFormat("Invalid grpc_polling_entity tag '%d'", pollent->tag));
  }
}

void grpc_polling_entity_del_from_pollset_set(grpc_polling_entity* pollent,
                                              grpc_pollset_set* pss_dst) {
  if (pollent->tag == GRPC_POLLS_POLLSET) {

    if (pollent->pollent.pollset != nullptr) {
      grpc_pollset_set_del_pollset(pss_dst, pollent->pollent.pollset);
    }
  } else if (pollent->tag == GRPC_POLLS_POLLSET_SET) {
    CHECK_NE(pollent->pollent.pollset_set, nullptr);
    grpc_pollset_set_del_pollset_set(pss_dst, pollent->pollent.pollset_set);
  } else if (pollent->tag == GRPC_POLLS_NONE) {

  } else {
    grpc_core::Crash(
        absl::StrFormat("Invalid grpc_polling_entity tag '%d'", pollent->tag));
  }
}

std::string grpc_polling_entity_string(grpc_polling_entity* pollent) {
  if (pollent->tag == GRPC_POLLS_POLLSET) {
    return absl::StrFormat("pollset:%p", pollent->pollent.pollset);
  } else if (pollent->tag == GRPC_POLLS_POLLSET_SET) {
    return absl::StrFormat("pollset_set:%p", pollent->pollent.pollset_set);
  } else {
    return absl::StrFormat("invalid_tag:%d", pollent->tag);
  }
}

Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

#include "src/core/lib/iomgr/polling_entity.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>

#include "absl/log/check.h"
#include "absl/strings/str_format.h"
#include "src/core/util/crash.h"

// Creates a polling entity from a pollset_set.
// If pollset_set is null, creates an empty polling entity (GRPC_POLLS_NONE).
// Otherwise, creates a pollset_set type entity with the given pollset_set.
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

// Creates a polling entity from a pollset.
// The created entity will always be of type GRPC_POLLS_POLLSET.
grpc_polling_entity grpc_polling_entity_create_from_pollset(
    grpc_pollset* pollset) {
  grpc_polling_entity pollent;
  pollent.pollent.pollset = pollset;
  pollent.tag = GRPC_POLLS_POLLSET;
  return pollent;
}

// Returns the pollset from a polling entity if it is of type GRPC_POLLS_POLLSET.
// Returns nullptr otherwise.
grpc_pollset* grpc_polling_entity_pollset(grpc_polling_entity* pollent) {
  if (pollent->tag == GRPC_POLLS_POLLSET) {
    return pollent->pollent.pollset;
  }
  return nullptr;
}

// Returns the pollset_set from a polling entity if it is of type GRPC_POLLS_POLLSET_SET.
// Returns nullptr otherwise.
grpc_pollset_set* grpc_polling_entity_pollset_set(
    grpc_polling_entity* pollent) {
  if (pollent->tag == GRPC_POLLS_POLLSET_SET) {
    return pollent->pollent.pollset_set;
  }
  return nullptr;
}

// Checks if a polling entity is empty (has tag GRPC_POLLS_NONE).
bool grpc_polling_entity_is_empty(const grpc_polling_entity* pollent) {
  return pollent->tag == GRPC_POLLS_NONE;
}

// Adds the polling entity to a destination pollset_set.
// Behavior depends on the entity type:
// - For POLLSET: adds the pollset to pss_dst if not null
// - For POLLSET_SET: adds the pollset_set to pss_dst (asserts not null)
// - For NONE: no operation
// - For invalid types: crashes with error message
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
    // No operation for empty polling entity
  } else {
    grpc_core::Crash(
        absl::StrFormat("Invalid grpc_polling_entity tag '%d'", pollent->tag));
  }
}

// Removes the polling entity from a destination pollset_set.
// Behavior depends on the entity type:
// - For POLLSET: removes the pollset from pss_dst if not null
// - For POLLSET_SET: removes the pollset_set from pss_dst (asserts not null)
// - For NONE: no operation
// - For invalid types: crashes with error message
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
    // No operation for empty polling entity
  } else {
    grpc_core::Crash(
        absl::StrFormat("Invalid grpc_polling_entity tag '%d'", pollent->tag));
  }
}

// Returns a string representation of the polling entity.
// Format depends on entity type:
// - POLLSET: "pollset:<address>"
// - POLLSET_SET: "pollset_set:<address>"
// - Other: "invalid_tag:<tag_value>"
std::string grpc_polling_entity_string(grpc_polling_entity* pollent) {
  if (pollent->tag == GRPC_POLLS_POLLSET) {
    return absl::StrFormat("pollset:%p", pollent->pollent.pollset);
  } else if (pollent->tag == GRPC_POLLS_POLLSET_SET) {
    return absl::StrFormat("pollset_set:%p", pollent->pollent.pollset_set);
  } else {
    return absl::StrFormat("invalid_tag:%d", pollent->tag);
  }
}
```

The comments:
1. Explain each function's purpose and behavior
2. Describe parameter usage and return values
3. Clarify special cases and edge conditions
4. Document the behavior for different entity types (POLLSET, POLLSET_SET, NONE)
5. Note error handling and crash conditions
6. Explain the string representation format
7. Maintain consistency in style and detail level throughout

The comments are placed above each function and provide enough information for a developer to understand and use the API without needing to examine the implementation details.
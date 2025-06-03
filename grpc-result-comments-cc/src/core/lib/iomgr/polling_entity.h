Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_POLLING_ENTITY_H
#define GRPC_SRC_CORE_LIB_IOMGR_POLLING_ENTITY_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/pollset.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/promise/context.h"

// Enumeration defining the types of polling entities that can be represented
typedef enum grpc_pollset_tag {
  GRPC_POLLS_NONE,        // No polling entity is set
  GRPC_POLLS_POLLSET,     // The entity is a single pollset
  GRPC_POLLS_POLLSET_SET  // The entity is a set of pollsets
} grpc_pollset_tag;

// Structure representing a polling entity which can be either:
// - A single pollset (grpc_pollset*)
// - A pollset set (grpc_pollset_set*)
// - None (empty state)
struct grpc_polling_entity {
  union {
    grpc_pollset* pollset = nullptr;  // Pointer to a single pollset
    grpc_pollset_set* pollset_set;    // Pointer to a pollset set
  } pollent;
  grpc_pollset_tag tag = GRPC_POLLS_NONE;  // Type of the current polling entity
};

// Creates a polling entity from a pollset set
grpc_polling_entity grpc_polling_entity_create_from_pollset_set(
    grpc_pollset_set* pollset_set);

// Creates a polling entity from a single pollset
grpc_polling_entity grpc_polling_entity_create_from_pollset(
    grpc_pollset* pollset);

// Returns the pollset from a polling entity (must be of type GRPC_POLLS_POLLSET)
grpc_pollset* grpc_polling_entity_pollset(grpc_polling_entity* pollent);

// Returns the pollset set from a polling entity (must be of type GRPC_POLLS_POLLSET_SET)
grpc_pollset_set* grpc_polling_entity_pollset_set(grpc_polling_entity* pollent);

// Checks if the polling entity is empty (tag is GRPC_POLLS_NONE)
bool grpc_polling_entity_is_empty(const grpc_polling_entity* pollent);

// Adds the polling entity to a destination pollset set
void grpc_polling_entity_add_to_pollset_set(grpc_polling_entity* pollent,
                                            grpc_pollset_set* pss_dst);

// Removes the polling entity from a destination pollset set
void grpc_polling_entity_del_from_pollset_set(grpc_polling_entity* pollent,
                                              grpc_pollset_set* pss_dst);

// Returns a string representation of the polling entity for debugging
std::string grpc_polling_entity_string(grpc_polling_entity* pollent);

// Template specialization for using grpc_polling_entity as a context type
namespace grpc_core {
template <>
struct ContextType<grpc_polling_entity> {};
}

#endif
```

The comments explain:
1. The purpose of the grpc_pollset_tag enumeration
2. The structure and purpose of grpc_polling_entity
3. The functionality of each function declaration
4. The template specialization for context handling

The comments are designed to help future developers understand:
- What types of polling entities exist
- How the union in grpc_polling_entity works
- What each function does
- How the polling entity can be used as a context type
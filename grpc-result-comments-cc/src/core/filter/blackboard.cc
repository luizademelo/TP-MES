Here's the commented version of the code:

```c++
// Copyright 2024 gRPC authors.

#include "src/core/filter/blackboard.h"

namespace grpc_core {

// Retrieves an entry from the blackboard based on type and key
// Parameters:
//   type - The unique type identifier for the entry
//   key - The string key associated with the entry
// Returns:
//   A RefCountedPtr to the found Entry, or nullptr if not found
RefCountedPtr<Blackboard::Entry> Blackboard::Get(UniqueTypeName type,
                                                 const std::string& key) const {
  // Search for the entry using a composite key (type + key)
  auto it = map_.find(std::pair(type, key));
  // Return nullptr if entry not found
  if (it == map_.end()) return nullptr;
  // Return the found entry
  return it->second;
}

// Stores or updates an entry in the blackboard
// Parameters:
//   type - The unique type identifier for the entry
//   key - The string key to associate with the entry
//   entry - The entry to store (as a RefCountedPtr)
void Blackboard::Set(UniqueTypeName type, const std::string& key,
                     RefCountedPtr<Entry> entry) {
  // Insert or update the entry in the map using composite key (type + key)
  // std::move is used to transfer ownership of the entry efficiently
  map_[std::pair(type, key)] = std::move(entry);
}

}  // namespace grpc_core
```

Key improvements made:
1. Added detailed function-level comments explaining purpose, parameters, and return values
2. Added inline comments explaining key operations
3. Documented the use of std::move for ownership transfer
4. Added namespace closing comment
5. Explained the composite key structure (type + key) used in the map
6. Clarified the behavior when entries are not found (nullptr return)
7. Noted the RefCountedPtr usage indicating reference-counted memory management
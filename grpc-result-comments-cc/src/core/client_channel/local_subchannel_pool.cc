Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/core/client_channel/local_subchannel_pool.h"

#include <grpc/support/port_platform.h>

#include <utility>

#include "absl/log/check.h"
#include "src/core/client_channel/subchannel.h"

namespace grpc_core {

// Registers a subchannel in the pool with the given key.
// Args:
//   key: The key to associate with the subchannel
//   constructed: The subchannel to register
// Returns:
//   The registered subchannel (same as 'constructed' parameter)
// Checks:
//   - Asserts that no subchannel is already registered with this key
RefCountedPtr<Subchannel> LocalSubchannelPool::RegisterSubchannel(
    const SubchannelKey& key, RefCountedPtr<Subchannel> constructed) {
  // Look for existing subchannel with this key
  auto it = subchannel_map_.find(key);

  // Ensure no subchannel already exists with this key
  CHECK(it == subchannel_map_.end());
  // Register the new subchannel in the map
  subchannel_map_[key] = constructed.get();
  // Return the registered subchannel
  return constructed;
}

// Unregisters a subchannel from the pool.
// Args:
//   key: The key of the subchannel to unregister
//   subchannel: The subchannel to unregister
// Checks:
//   - Asserts that a subchannel exists with this key
//   - Asserts that the found subchannel matches the one to unregister
void LocalSubchannelPool::UnregisterSubchannel(const SubchannelKey& key,
                                               Subchannel* subchannel) {
  // Find the subchannel in the map
  auto it = subchannel_map_.find(key);

  // Verify the subchannel exists and matches the one to unregister
  CHECK(it != subchannel_map_.end());
  CHECK(it->second == subchannel);
  // Remove the subchannel from the map
  subchannel_map_.erase(it);
}

// Finds and returns a subchannel by its key.
// Args:
//   key: The key of the subchannel to find
// Returns:
//   - A reference-counted pointer to the subchannel if found
//   - nullptr if no subchannel exists with this key
RefCountedPtr<Subchannel> LocalSubchannelPool::FindSubchannel(
    const SubchannelKey& key) {
  // Look up the subchannel in the map
  auto it = subchannel_map_.find(key);
  // Return nullptr if not found
  if (it == subchannel_map_.end()) return nullptr;
  // Return a new reference to the found subchannel
  return it->second->Ref();
}

}  // namespace grpc_core
```

The comments added:
1. Describe each method's purpose and functionality
2. Document parameters and return values
3. Explain the key operations being performed
4. Note the assertion checks and their purposes
5. Clarify the behavior when subchannels are found/not found
6. Added namespace closing comment for clarity

The comments follow a consistent style and provide enough detail to understand the code's behavior without being overly verbose. They explain both what the code does and why certain operations are performed (like the assertion checks).
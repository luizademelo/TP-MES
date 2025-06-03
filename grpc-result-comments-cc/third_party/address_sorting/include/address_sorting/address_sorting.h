Here's the commented version of the code:

```c++
/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef ADDRESS_SORTING_H
#define ADDRESS_SORTING_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Structure representing a network address with its length
typedef struct address_sorting_address {
  char addr[128];  // Buffer to store the address (supports both IPv4 and IPv6)
  size_t len;      // Length of the address in bytes
} address_sorting_address;

// Structure representing a sortable address pair (destination + optional source)
typedef struct address_sorting_sortable {
  address_sorting_address dest_addr;  // Destination address to be sorted
  
  void* user_data;  // Opaque pointer for user-specific data associated with address

  address_sorting_address source_addr;  // Source address (if available)
  bool source_addr_exists;  // Flag indicating if source_addr is valid
  size_t original_index;    // Original index before sorting (for reference)
} address_sorting_sortable;

// Sorts an array of address_sorting_sortable according to RFC 6724 rules
// Parameters:
//   sortables - Pointer to array of sortable addresses
//   sortables_len - Length of the sortables array
void address_sorting_rfc_6724_sort(address_sorting_sortable* sortables,
                                   size_t sortables_len);

// Initializes the address sorting module (must be called before first use)
void address_sorting_init();

// Cleans up resources used by the address sorting module
void address_sorting_shutdown();

// Forward declaration for source address factory
struct address_sorting_source_addr_factory;

// Virtual function table for source address factory operations
typedef struct {
  // Function to get source address for a given destination address
  // Returns true if successful, false otherwise
  bool (*get_source_addr)(struct address_sorting_source_addr_factory* factory,
                          const address_sorting_address* dest_addr,
                          address_sorting_address* source_addr);
  // Function to destroy/clean up the factory
  void (*destroy)(struct address_sorting_source_addr_factory* factory);
} address_sorting_source_addr_factory_vtable;

// Base structure for source address factory with virtual function table
typedef struct address_sorting_source_addr_factory {
  const address_sorting_source_addr_factory_vtable* vtable;
} address_sorting_source_addr_factory;

// Enum representing address families
typedef enum {
  ADDRESS_SORTING_AF_INET,        // IPv4 address family
  ADDRESS_SORTING_AF_INET6,       // IPv6 address family
  ADDRESS_SORTING_UNKNOWN_FAMILY, // Unknown/unsupported address family
} address_sorting_family;

// Determines the address family (IPv4/IPv6) of a given address
// Parameters:
//   address - Pointer to the address to examine
// Returns:
//   The detected address family (ADDRESS_SORTING_AF_INET/ADDRESS_SORTING_AF_INET6)
//   or ADDRESS_SORTING_UNKNOWN_FAMILY if undetermined
address_sorting_family address_sorting_abstract_get_family(
    const address_sorting_address* address);

// Overrides the default source address factory for testing purposes
// Parameters:
//   factory - Pointer to the factory implementation to use for testing
void address_sorting_override_source_addr_factory_for_testing(
    address_sorting_source_addr_factory* factory);

// Retrieves source address for testing purposes
// Parameters:
//   dest - Destination address to find source address for
//   source - Output parameter for the found source address
// Returns:
//   true if source address was found, false otherwise
bool address_sorting_get_source_addr_for_testing(
    const address_sorting_address* dest, address_sorting_address* source);

#ifdef __cplusplus
}
#endif

#endif  // ADDRESS_SORTING_H
```

The comments provide:
1. Overview of each structure and its purpose
2. Explanation of each field in structures
3. Documentation for each function including parameters and return values
4. Notes about important implementation details
5. Clarification of enum values
6. Separation between public API and testing facilities

The comments are designed to help maintainers understand:
- The overall architecture of the address sorting system
- How to properly use each component
- The purpose of each function and structure
- The expected behavior of the API
- Special considerations for testing
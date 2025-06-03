Here's the commented version of the code:

```c++
/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef GRPC_INTERNAL_COMPILER_RUBY_GENERATOR_MAP_INL_H
#define GRPC_INTERNAL_COMPILER_RUBY_GENERATOR_MAP_INL_H

// Include necessary standard library headers
#include <initializer_list>
#include <iostream>
#include <map>
#include <ostream>
#include <vector>

// Include project-specific configuration
#include "src/compiler/config.h"

// Using declarations to simplify standard library usage
using std::initializer_list;
using std::map;
using std::vector;

namespace grpc_ruby_generator {

/**
 * @brief Converts an initializer list of strings to a map of key-value pairs.
 * 
 * This function takes an initializer list of strings where elements are treated
 * as alternating key-value pairs and converts them into a map. The function
 * expects an even number of elements in the input list.
 * 
 * @param values An initializer list of strings containing alternating keys and values
 * @return std::map<std::string, std::string> A map containing the key-value pairs
 * 
 * @note If the input list has an odd number of elements, an error message is printed
 *       to stderr, as this indicates a missing value for the last key.
 */
inline std::map<std::string, std::string> ListToDict(
    const initializer_list<std::string>& values) {
  // Check if the input list has an odd number of elements
  if (values.size() % 2 != 0) {
    std::cerr << "Not every 'key' has a value in `values`." << std::endl;
  }
  
  // Create an empty map to store the key-value pairs
  std::map<std::string, std::string> value_map;
  
  // Initialize an iterator for the input list
  auto value_iter = values.begin();
  
  // Process pairs of elements (key followed by value)
  for (unsigned i = 0; i < values.size() / 2; ++i) {
    // Get the key (current element)
    std::string key = *value_iter;
    ++value_iter;
    
    // Get the value (next element)
    std::string value = *value_iter;
    
    // Store the key-value pair in the map
    value_map[key] = value;
    
    // Move to the next pair
    ++value_iter;
  }
  
  // Return the populated map
  return value_map;
}

}  // namespace grpc_ruby_generator

#endif  // GRPC_INTERNAL_COMPILER_RUBY_GENERATOR_MAP_INL_H
```

Key improvements made:
1. Added detailed documentation for the `ListToDict` function including:
   - Purpose of the function
   - Parameter description
   - Return value description
   - Important notes about behavior
2. Added comments explaining each section of the implementation
3. Added namespace closing comment
4. Added header guard closing comment
5. Added comments for standard library includes
6. Added explanation for using declarations

The comments now provide clear guidance about:
- What the function does
- How to use it
- What to expect in terms of behavior
- Error conditions
- The overall structure of the code
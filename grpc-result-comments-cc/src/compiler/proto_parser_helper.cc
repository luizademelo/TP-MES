Here's the commented version of the code:

```c++
// Copyright 2023 The gRPC Authors

#include <string>

namespace grpc_generator {

/// @brief Escapes all occurrences of '$' characters in a string by doubling them.
/// @param original The input string potentially containing '$' characters
/// @return A new string where all '$' characters are replaced with '$$'
///
/// This function is typically used to escape variable delimiters in template strings
/// where '$' might have special meaning. For example, "var$name" becomes "var$$name".
/// The escaping ensures the '$' character is treated as a literal rather than a delimiter.
std::string EscapeVariableDelimiters(const std::string& original) {
  // Create a modifiable copy of the input string
  std::string mut_str = original;
  
  // Start searching from the beginning of the string
  size_t index = 0;
  
  // Find and replace all '$' characters
  while ((index = mut_str.find('$', index)) != std::string::npos) {
    // Replace single '$' with '$$'
    mut_str.replace(index, 1, "$$");
    
    // Skip past the newly inserted '$$' to avoid infinite loops
    // and continue searching the rest of the string
    index += 2;
  }
  
  // Return the modified string with all '$' characters escaped
  return mut_str;
}

}  // namespace grpc_generator
```
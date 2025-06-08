Here's the commented version of the code:

```c++
#!/usr/bin/env python2.7

# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Import required modules
import os  # For operating system related functionalities
import sys  # For system-specific parameters and functions
import glob  # For Unix style pathname pattern expansion
import yaml  # For YAML (YAML Ain't Markup Language) parsing and dumping

# Change working directory to two levels up from the script's location
# This assumes the script is in a subdirectory of the project root
os.chdir(os.path.dirname(sys.argv[0]) + "/../..")

# Initialize an empty dictionary to store build information
out = {}

# Populate the dictionary with library build configuration
out["libs"] = [
    {
        "name": "benchmark",  # Name of the library
        "build": "private",   # Build type (private indicates internal build)
        "language": "c++",    # Programming language of the library
        "secure": False,      # Whether the library requires security features
        "defaults": "benchmark",  # Default build configuration name
        # List of source files (sorted alphabetically)
        "src": sorted(glob.glob("third_party/benchmark/src/*.cc")),
        # List of header files (sorted alphabetically)
        # Combines headers from src and include directories
        "headers": sorted(
            glob.glob("third_party/benchmark/src/*.h")
            + glob.glob("third_party/benchmark/include/benchmark/*.h")
        ),
    }
]

# Convert the dictionary to YAML format and print it
# This output can be used by build systems to configure the benchmark library
print(yaml.dump(out))
```

Key improvements in the comments:
1. Added explanations for each imported module
2. Explained the directory change operation
3. Documented each field in the library configuration dictionary
4. Clarified the purpose of the YAML output
5. Added context about how the output might be used
6. Explained the sorting and glob operations
7. Maintained the original license header

The comments now provide a clear understanding of what the code does and why, which will help future developers maintain or modify this build configuration script.
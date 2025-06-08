Here's the commented version of the code snippet:

```c++
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

begin
  # Extract the major.minor version number from RUBY_VERSION (e.g., "2.7" from "2.7.0")
  ruby_version_dirname = /(\d+\.\d+)/.match(RUBY_VERSION).to_s
  
  # Construct the full path to the version-specific library directory by:
  # 1. Getting the directory of the current file (__FILE__)
  # 2. Expanding the path to include the ruby version directory
  distrib_lib_dir = File.expand_path(ruby_version_dirname,
                                     File.dirname(__FILE__))
  
  # Check if there are any grpc_c* files in the version-specific directory
  if !Dir.glob("#{distrib_lib_dir}/grpc_c*").empty?
    # If found, require the version-specific grpc_c library
    require "#{distrib_lib_dir}/grpc_c"
  else
    # Otherwise, fall back to requiring the default grpc_c library from the grpc gem
    require 'grpc/grpc_c'
  end
end
```

The comments explain:
1. The version extraction from RUBY_VERSION
2. The path construction logic
3. The library loading strategy that first checks for a version-specific library before falling back to the default one

This approach allows for version-specific implementations while maintaining backward compatibility.
Here's the commented version of the code snippet:

```c++
#!/usr/bin/env ruby
# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Returns the absolute path to the root directory of the gRPC project
# by navigating two levels up from the current file's directory.
def grpc_root()
  File.expand_path(File.join(File.dirname(__FILE__), '..', '..'))
end

# Retrieves the Docker image name for a specific platform to be used with rake-compiler
# 
# @param platform [String] The target platform for which to get the Docker image
# @return [String] The name of the Docker image read from the current_version file
# 
# The method constructs the path to the platform-specific current_version file in the
# rake-compiler-dock directory and reads the image name from it.
def docker_image_for_rake_compiler(platform)
  require 'digest'

  # Construct path to the platform-specific Dockerfile directory
  dockerfile_dir = File.join(grpc_root, 'third_party', 'rake-compiler-dock', 'rake_' + platform)

  # The current_version file contains the name of the Docker image to use
  current_version_file = dockerfile_dir + '.current_version'
  image_name = File.read(current_version_file)
end

# Executes rake commands in a Docker container configured for cross-compilation
# 
# @param platform [String] The target platform for compilation
# @param args [String] The rake command and arguments to execute
# 
# This method sets up environment variables for rake-compiler-dock:
# - RCD_RUBYVM: Specifies to use MRI Ruby
# - RCD_PLATFORM: Sets the target platform
# - RCD_IMAGE: Sets the Docker image to use (obtained from docker_image_for_rake_compiler)
# Then executes the given rake command in the Docker container
def run_rake_compiler(platform, args)
  require 'rake_compiler_dock'

  # Configure environment for rake-compiler-dock
  ENV['RCD_RUBYVM'] = 'mri'  # Use MRI Ruby
  ENV['RCD_PLATFORM'] = platform  # Target platform
  ENV['RCD_IMAGE'] = docker_image_for_rake_compiler(platform)  # Docker image to use
  
  # Execute the rake command in the configured Docker container
  RakeCompilerDock.sh args
end
```

The comments explain:
1. The overall purpose of each method
2. The parameters and return values
3. The key operations being performed
4. The environment variables being set and their significance
5. The flow between methods

The comments are clear and concise while providing enough detail for future maintainers to understand the code's functionality without being overly verbose.
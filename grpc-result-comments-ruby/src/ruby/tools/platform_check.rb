Here's the commented version of the code:

```c++
# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'rbconfig'  # Required to access system configuration information

module PLATFORM
  # Determines the operating system name based on the host OS configuration
  # @return [String] The name of the operating system ('windows', 'macos', or 'linux')
  def PLATFORM.os_name
    case RbConfig::CONFIG['host_os']
      when /cygwin|mswin|mingw|bccwin|wince|emx/
        'windows'  # Matches various Windows-like operating systems
      when /darwin/
        'macos'    # Matches macOS/Darwin systems
      else
        'linux'    # Default case for all other operating systems
    end
  end

  # Determines the system architecture based on host CPU configuration
  # @return [String] The system architecture ('x86_64' or 'x86')
  def PLATFORM.architecture
    host_cpu = RbConfig::CONFIG['host_cpu']

    # Special case for Apple M1/M2 ARM chips which report as x86_64 in Ruby config
    return 'x86_64' if RbConfig::CONFIG['host_os'] =~ /darwin/ && host_cpu =~ /arm|aarch/

    case host_cpu
      when /x86_64/
        'x86_64'  # 64-bit x86 architecture
      else
        'x86'     # Default case for 32-bit x86 architecture
    end
  end
end
```

The comments explain:
1. The overall purpose of the module (platform detection)
2. Each method's functionality and return values
3. Special cases in the logic (like Apple M1/M2 handling)
4. The regex patterns used for OS and CPU detection
5. The default cases and what they represent

The comments are formatted to be clear and helpful for future maintenance while not being overly verbose. They follow common Ruby documentation conventions and provide just enough information to understand the code's purpose and behavior.
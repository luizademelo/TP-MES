# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'rbconfig'

module PLATFORM
  def PLATFORM.os_name
    case RbConfig::CONFIG['host_os']
      when /cygwin|mswin|mingw|bccwin|wince|emx/
        'windows'
      when /darwin/
        'macos'
      else
        'linux'
    end
  end

  def PLATFORM.architecture
    host_cpu = RbConfig::CONFIG['host_cpu']

    return 'x86_64' if RbConfig::CONFIG['host_os'] =~ /darwin/ && host_cpu =~ /arm|aarch/

    case host_cpu
      when /x86_64/
        'x86_64'
      else
        'x86'
    end
  end
end

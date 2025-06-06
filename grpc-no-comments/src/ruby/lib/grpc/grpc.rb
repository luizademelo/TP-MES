# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

begin
  ruby_version_dirname = /(\d+\.\d+)/.match(RUBY_VERSION).to_s
  distrib_lib_dir = File.expand_path(ruby_version_dirname,
                                     File.dirname(__FILE__))
  if !Dir.glob("#{distrib_lib_dir}/grpc_c*").empty?
    require "#{distrib_lib_dir}/grpc_c"
  else
    require 'grpc/grpc_c'
  end
end

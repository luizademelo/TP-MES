Here's the commented version of the code:

```c++
# Copyright 2018 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Required libraries for file operations and process management
require 'open3'
require 'tmpdir'

# Main function that tests gRPC Ruby plugin's code generation
# for proto files with package names containing underscores
def main
  # Set up directory paths
  root_dir = File.join(File.dirname(__FILE__), '..', '..', '..')  # Root directory of the project
  pb_dir = File.join(root_dir, 'src', 'ruby', 'end2end', 'protos')  # Directory containing proto files

  # Paths to required binaries
  bins_dir = File.join(root_dir, 'cmake', 'build')
  plugin = File.join(bins_dir, 'grpc_ruby_plugin')  # gRPC Ruby plugin binary
  protoc = File.join(bins_dir, 'third_party', 'protobuf', 'protoc')  # Protocol buffer compiler

  got = nil  # Variable to store generated file content

  # Create a temporary directory for the test
  Dir.mktmpdir do |tmp_dir|
    # Path where generated Ruby file should be created
    gen_out = File.join(tmp_dir, 'package_with_underscore', 'service_services_pb.rb')

    # Execute protoc command with gRPC plugin to generate Ruby code from proto file
    pid = spawn(
      protoc,
      "--proto_path=#{pb_dir}",  # Set proto file search path
      'package_with_underscore/service.proto',  # Proto file to compile
      "--grpc_out=#{tmp_dir}",  # Output directory for generated gRPC code
      "--plugin=protoc-gen-grpc=#{plugin}"  # Path to gRPC plugin
    )
    Process.waitpid2(pid)  # Wait for protoc process to complete
    
    # Read the generated file content
    File.open(gen_out) { |f| got = f.read }
  end

  # Expected RPC method signature in the generated code
  correct_modularized_rpc = 'rpc :TestOne, ' \
                            '::Grpc::Testing::PackageWithUnderscore::Data::Request, ' \
                            '::Grpc::Testing::PackageWithUnderscore::Data::Response'

  # Return if generated code contains the expected RPC signature
  return if got.include?(correct_modularized_rpc)

  # Fail the test if generated code doesn't match expected output
  fail 'generated file does not match with correct_modularized_rpc'
end

# Execute the main function
main
```
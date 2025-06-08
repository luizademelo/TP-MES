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

require 'spec_helper'
require 'open3'
require 'tmpdir'

# Checks if the necessary code generation tools are available in the system
# Returns true if both grpc_ruby_plugin and protoc are found in PATH
def can_run_codegen_check
  system('which grpc_ruby_plugin') && system('which protoc')
end

# Test suite for verifying gRPC Ruby code generation for Ping protobuf
describe 'Ping protobuf code generation' do
  if !can_run_codegen_check
    # Skip test if required tools are not available
    skip 'protoc || grpc_ruby_plugin missing, cannot verify ping code-gen'
  else
    # Test case to verify generated code matches expected output
    it 'should have the same content as created by code generation' do
      # Calculate root directory path relative to this file's location
      root_dir = File.join(File.dirname(__FILE__), '..', '..', '..', '..', '..')

      # Path to the expected generated service file
      service_path = File.join(root_dir, 'src', 'ruby', 'pb', 'grpc',
                               'testing', 'duplicate',
                               'echo_duplicate_services_pb.rb')
      want = nil
      # Read the expected generated file content
      File.open(service_path) { |f| want = f.read }

      # Find the path to the grpc_ruby_plugin executable
      plugin, = Open3.capture2('which', 'grpc_ruby_plugin')
      plugin = plugin.strip
      got = nil
      
      # Create a temporary directory for code generation
      Dir.mktmpdir do |tmp_dir|
        # Path where the generated file will be created
        gen_out = File.join(tmp_dir, 'src', 'proto', 'grpc', 'testing',
                            'duplicate', 'echo_duplicate_services_pb.rb')
        # Run protoc to generate the Ruby gRPC service files
        pid = spawn(
          'protoc',
          '-I.',  # Use current directory for proto imports
          'src/proto/grpc/testing/duplicate/echo_duplicate.proto',  # Input proto file
          "--grpc_out=#{tmp_dir}",  # Output directory for generated files
          "--plugin=protoc-gen-grpc=#{plugin}",  # Specify gRPC plugin path
          chdir: root_dir)  # Working directory for the command
        Process.wait(pid)
        
        # Read the newly generated file content
        File.open(gen_out) { |f| got = f.read }
      end
      
      # Verify the generated content matches the expected content
      expect(got).to eq(want)
    end
  end
end
```
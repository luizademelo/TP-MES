Here's the commented version of the code:

```c++
# Copyright 2015 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

require 'spec_helper'
require 'grpc/health/v1/health_pb'
require 'grpc/health/checker'
require 'open3'
require 'tmpdir'

# Checks if the system has the required code generation tools installed
# Returns true if both grpc_ruby_plugin and protoc are available
def can_run_codegen_check
  system('which grpc_ruby_plugin') && system('which protoc')
end

# Tests for health protobuf code generation
describe 'Health protobuf code generation' do
  context 'the health service file used by grpc/health/checker' do
    if !can_run_codegen_check
      skip 'protoc || grpc_ruby_plugin missing, cannot verify health code-gen'
    else
      # Verifies that the health service file is already loaded
      it 'should already be loaded indirectly i.e, used by the other specs' do
        expect(require('grpc/health/v1/health_services_pb')).to be(false)
      end

      # Compares generated code with existing code to ensure they match
      it 'should have the same content as created by code generation' do
        root_dir = File.join(File.dirname(__FILE__), '..', '..', '..', '..')
        pb_dir = File.join(root_dir, 'proto')

        # Path to the existing service file
        service_path = File.join(root_dir, 'ruby', 'pb', 'grpc',
                                 'health', 'v1', 'health_services_pb.rb')
        want = nil
        File.open(service_path) { |f| want = f.read }

        # Find the grpc_ruby_plugin location
        plugin, = Open3.capture2('which', 'grpc_ruby_plugin')
        plugin = plugin.strip
        got = nil
        
        # Generate the service file in a temp directory
        Dir.mktmpdir do |tmp_dir|
          gen_out = File.join(tmp_dir, 'grpc', 'health', 'v1',
                              'health_services_pb.rb')
          pid = spawn(
            'protoc',
            '-I.',
            'grpc/health/v1/health.proto',
            "--grpc_out=#{tmp_dir}",
            "--plugin=protoc-gen-grpc=#{plugin}",
            chdir: pb_dir)
          Process.wait(pid)
          File.open(gen_out) { |f| got = f.read }
        end
        
        # Verify generated code matches existing code
        expect(got).to eq(want)
      end
    end
  end
end

# Tests for the Grpc::Health::Checker class
describe Grpc::Health::Checker do
  StatusCodes = GRPC::Core::StatusCodes
  ServingStatus = Grpc::Health::V1::HealthCheckResponse::ServingStatus
  HCResp = Grpc::Health::V1::HealthCheckResponse  # Response message
  HCReq = Grpc::Health::V1::HealthCheckRequest   # Request message
  
  # Test cases for successful operations
  success_tests =
    [
      {
        desc: 'the service is not specified',
        service: ''
      }, {
        desc: 'the service is specified',
        service: 'fake-service-1'
      }
    ]

  # Tests for initialization
  context 'initialization' do
    it 'can be constructed with no args' do
      checker = Grpc::Health::Checker.new
      expect(checker).to_not be(nil)
    end
  end

  # Tests for adding and checking service status
  context 'method `add_status` and `check`' do
    success_tests.each do |t|
      it "should succeed when #{t[:desc]}" do
        checker = Grpc::Health::Checker.new
        checker.add_status(t[:service], ServingStatus::NOT_SERVING)
        got = checker.check(HCReq.new(service: t[:service]), nil)
        want = HCResp.new(status: ServingStatus::NOT_SERVING)
        expect(got).to eq(want)
      end
    end
  end

  # Tests for adding multiple statuses at once
  context 'method `add_statuses`' do
    it 'should add status to each service' do
      checker = Grpc::Health::Checker.new
      checker.add_statuses(
        'service1' => ServingStatus::SERVING,
        'service2' => ServingStatus::NOT_SERVING
      )
      service1_health = checker.check(HCReq.new(service: 'service1'), nil)
      service2_health = checker.check(HCReq.new(service: 'service2'), nil)
      expect(service1_health).to eq(HCResp.new(status: ServingStatus::SERVING))
      expect(service2_health).to eq(HCResp.new(status: ServingStatus::NOT_SERVING))
    end
  end

  # Tests for setting the same status for multiple services
  context 'method `set_status_for_services`' do
    it 'should add given status to all given services' do
      checker = Grpc::Health::Checker.new
      checker.set_status_for_services(
        ServingStatus::SERVING,
        'service1',
        'service2'
      )
      service1_health = checker.check(HCReq.new(service: 'service1'), nil)
      service2_health = checker.check(HCReq.new(service: 'service2'), nil)
      expect(service1_health).to eq(HCResp.new(status: ServingStatus::SERVING))
      expect(service2_health).to eq(HCResp.new(status: ServingStatus::SERVING))
    end
  end

  # Tests for checking service status when service is not found
  context 'method `check`' do
    success_tests.each do |t|
      it "should fail with NOT_FOUND when #{t[:desc]}" do
        checker = Grpc::Health::Checker.new
        blk = proc do
          checker.check(HCReq.new(service: t[:service]), nil)
        end
        expected_msg = /
        expect(&blk).to raise_error GRPC::NotFound, expected_msg
      end
    end
  end

  # Tests for clearing status of a service
  context 'method `clear_status`' do
    success_tests.each do |t|
      it "should fail after clearing status when #{t[:desc]}" do
        checker = Grpc::Health::Checker.new
        checker.add_status(t[:service], ServingStatus::NOT_SERVING)
        got = checker.check(HCReq.new(service: t[:service]), nil)
        want = HCResp.new(status: ServingStatus::NOT_SERVING)
        expect(got).to eq(want)

        checker.clear_status(t[:service])
        blk = proc do
          checker.check(HCReq.new(service: t[:service]), nil)
        end
        expected_msg = /
        expect(&blk).to raise_error GRPC::NotFound, expected_msg
      end
    end
  end

  # Tests for clearing all service statuses
  context 'method `clear_all`' do
    it 'should return NOT_FOUND after being invoked' do
      checker = Grpc::Health::Checker.new
      success_tests.each do |t|
        checker.add_status(t[:service], ServingStatus::NOT_SERVING)
        got = checker.check(HCReq.new(service: t[:service]), nil)
        want = HCResp.new(status: ServingStatus::NOT_SERVING)
        expect(got).to eq(want)
      end

      checker.clear_all

      success_tests.each do |t|
        blk = proc do
          checker.check(HCReq.new(service: t[:service]), nil)
        end
        expected_msg = /
        expect(&blk).to raise_error GRPC::NotFound, expected_msg
      end
    end
  end

  # Tests for running the checker on an RPC server
  describe 'running on RpcServer' do
    RpcServer = GRPC::RpcServer
    CheckerStub = Grpc::Health::Checker.rpc_stub_class

    before(:each) do
      server_host = '0.0.0.0:0'
      @client_opts = { channel_override: @ch }
      server_opts = {
        poll_period: 1
      }
      @srv = new_rpc_server_for_testing(**server_opts)
      server_port = @srv.add_http2_port(server_host, :this_port_is_insecure)
      @host = "localhost:#{server_port}"
      @ch = GRPC::Core::Channel.new(@host, nil, :this_channel_is_insecure)
    end

    after(:each) do
      @srv.stop
    end

    # Tests receiving correct status from server
    it 'should receive the correct status', server: true do
      Thread.abort_on_exception = true
      checker = Grpc::Health::Checker.new
      @srv.handle(checker)
      checker.add_status('', ServingStatus::NOT_SERVING)
      t = Thread.new { @srv.run }
      @srv.wait_till_running

      stub = CheckerStub.new(@host, :this_channel_is_insecure, **@client_opts)
      got = stub.check(HCReq.new)
      want = HCResp.new(status: ServingStatus::NOT_SERVING)
      expect(got).to eq(want)
      @srv.stop
      t.join
    end

    # Tests failure for unknown services
    it 'should fail on unknown services', server: true do
      checker = Grpc::Health::Checker.new
      @srv.handle(checker)
      t = Thread.new { @srv.run }
      @srv.wait_till_running
      blk = proc do
        stub = CheckerStub.new(@host, :this_channel_is_insecure, **@client_opts)
        stub.check(HCReq.new(service: 'unknown'))
      end
      expected_msg = /
      expect(&blk).to raise_error GRPC::NotFound, expected_msg
      @srv.stop
      t.join
    end
  end
end
```
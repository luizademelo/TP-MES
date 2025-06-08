Here's the commented version of the code:

```c++
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'spec_helper'

# Loads test certificates from the testdata directory
# Returns an array containing:
# - CA certificate
# - Server credentials (private key and cert chain)
# - A boolean flag (false in this case)
def load_test_certs
  test_root = File.join(File.dirname(__FILE__), 'testdata')
  files = ['ca.pem', 'server1.key', 'server1.pem']
  contents = files.map { |f| File.open(File.join(test_root, f)).read }
  [contents[0], [{ private_key: contents[1], cert_chain: contents[2] }], false]
end

Server = GRPC::Core::Server

# Test suite for GRPC::Core::Server functionality
describe Server do
  # Creates test server credentials using the loaded certificates
  def create_test_cert
    GRPC::Core::ServerCredentials.new(*load_test_certs)
  end

  # Tests for the #start method
  describe '#start' do
    # Verifies that server starts without errors
    it 'runs without failing' do
      blk = proc { new_core_server_for_testing(nil).start }
      expect(&blk).to_not raise_error
    end

    # Verifies that server fails to start if already closed
    it 'fails if the server is closed' do
      s = new_core_server_for_testing(nil)
      s.shutdown_and_notify(nil)
      s.close
      expect { s.start }.to raise_error(RuntimeError)
    end
  end

  # Tests for shutdown and destroy operations
  describe '#shutdown_and_notify and #destroy' do
    # Verifies that server can be properly destroyed
    it 'destroys a server ok' do
      s = start_a_server
      blk = proc do
        s.shutdown_and_notify(nil)
        s.destroy
      end
      expect(&blk).to_not raise_error
    end

    # Verifies that shutdown/destroy can be called multiple times without error
    it 'can be called more than once without error' do
      s = start_a_server
      begin
        blk = proc do
          s.shutdown_and_notify(nil)
          s.destroy
        end
        expect(&blk).to_not raise_error
        blk.call
        expect(&blk).to_not raise_error
      ensure
        s.shutdown_and_notify(nil)
        s.close
      end
    end
  end

  # Tests for shutdown and close operations
  describe '#shutdown_and_notify and #close' do
    # Verifies that server can be properly closed
    it 'closes a server ok' do
      s = start_a_server
      begin
        blk = proc do
          s.shutdown_and_notify(nil)
          s.close
        end
        expect(&blk).to_not raise_error
      ensure
        s.shutdown_and_notify(nil)
        s.close
      end
    end

    # Verifies that shutdown/close can be called multiple times without error
    it 'can be called more than once without error' do
      s = start_a_server
      blk = proc do
        s.shutdown_and_notify(nil)
        s.close
      end
      expect(&blk).to_not raise_error
      blk.call
      expect(&blk).to_not raise_error
    end
  end

  # Tests for adding HTTP ports
  describe '#add_http_port' do
    # Tests for insecure servers
    describe 'for insecure servers' do
      # Verifies adding insecure port works
      it 'runs without failing' do
        blk = proc do
          s = new_core_server_for_testing(nil)
          s.add_http2_port('localhost:0', :this_port_is_insecure)
          s.shutdown_and_notify(nil)
          s.close
        end
        expect(&blk).to_not raise_error
      end

      # Verifies adding port fails if server is closed
      it 'fails if the server is closed' do
        s = new_core_server_for_testing(nil)
        s.shutdown_and_notify(nil)
        s.close
        blk = proc do
          s.add_http2_port('localhost:0', :this_port_is_insecure)
        end
        expect(&blk).to raise_error(RuntimeError)
      end
    end

    # Tests for secure servers
    describe 'for secure servers' do
      let(:cert) { create_test_cert }
      # Verifies adding secure port works
      it 'runs without failing' do
        blk = proc do
          s = new_core_server_for_testing(nil)
          s.add_http2_port('localhost:0', cert)
          s.shutdown_and_notify(nil)
          s.close
        end
        expect(&blk).to_not raise_error
      end

      # Verifies adding secure port fails if server is closed
      it 'fails if the server is closed' do
        s = new_core_server_for_testing(nil)
        s.shutdown_and_notify(nil)
        s.close
        blk = proc { s.add_http2_port('localhost:0', cert) }
        expect(&blk).to raise_error(RuntimeError)
      end
    end

    # Tests for XDS servers
    describe 'for xds servers' do
      let(:cert) { create_test_cert }
      let(:xds) { GRPC::Core::XdsServerCredentials.new(cert) }
      # Verifies adding XDS port works
      it 'runs without failing' do
        blk = proc do
          s = new_core_server_for_testing(nil)
          s.add_http2_port('localhost:0', xds)
          s.shutdown_and_notify(nil)
          s.close
        end
        expect(&blk).to_not raise_error
      end

      # Verifies adding XDS port fails if server is closed
      it 'fails if the server is closed' do
        s = new_core_server_for_testing(nil)
        s.shutdown_and_notify(nil)
        s.close
        blk = proc { s.add_http2_port('localhost:0', xds) }
        expect(&blk).to raise_error(RuntimeError)
      end
    end
  end

  # Shared examples for server initialization tests
  shared_examples '#new' do
    # Tests server creation with nil channel args
    it 'takes nil channel args' do
      expect { new_core_server_for_testing(nil) }.to_not raise_error
    end

    # Tests server creation with invalid channel arg keys
    it 'does not take a hash with bad keys as channel args' do
      blk = construct_with_args(Object.new => 1)
      expect(&blk).to raise_error TypeError
      blk = construct_with_args(1 => 1)
      expect(&blk).to raise_error TypeError
    end

    # Tests server creation with invalid channel arg values
    it 'does not take a hash with bad values as channel args' do
      blk = construct_with_args(symbol: Object.new)
      expect(&blk).to raise_error TypeError
      blk = construct_with_args('1' => {})
      expect(&blk).to raise_error TypeError
    end

    # Tests server creation with valid symbol key channel args
    it 'can take a hash with a symbol key as channel args' do
      blk = construct_with_args(a_symbol: 1)
      expect(&blk).to_not raise_error
    end

    # Tests server creation with valid string key channel args
    it 'can take a hash with a string key as channel args' do
      blk = construct_with_args('a_symbol' => 1)
      expect(&blk).to_not raise_error
    end

    # Tests server creation with valid string value channel args
    it 'can take a hash with a string value as channel args' do
      blk = construct_with_args(a_symbol: '1')
      expect(&blk).to_not raise_error
    end

    # Tests server creation with valid symbol value channel args
    it 'can take a hash with a symbol value as channel args' do
      blk = construct_with_args(a_symbol: :another_symbol)
      expect(&blk).to_not raise_error
    end

    # Tests server creation with valid numeric value channel args
    it 'can take a hash with a numeric value as channel args' do
      blk = construct_with_args(a_symbol: 1)
      expect(&blk).to_not raise_error
    end

    # Tests server creation with multiple channel args
    it 'can take a hash with many args as channel args' do
      args = Hash[127.times.collect { |x| [x.to_s, x] }]
      blk = construct_with_args(args)
      expect(&blk).to_not raise_error
    end
  end

  # Tests for server initialization with insecure channel
  describe '#new with an insecure channel' do
    def construct_with_args(a)
      proc { new_core_server_for_testing(a) }
    end

    it_behaves_like '#new'
  end

  # Helper method to start a test server with insecure port
  def start_a_server
    s = new_core_server_for_testing(nil)
    s.add_http2_port('0.0.0.0:0', :this_port_is_insecure)
    s.start
    s
  end
end
```

The comments I've added:
1. Explained the purpose of the `load_test_certs` helper function
2. Added overview comments for each test section
3. Explained what each test case is verifying
4. Added comments for the shared examples and helper methods
5. Clarified the purpose of different test scenarios
6. Added notes about expected behavior in both success and failure cases

The comments maintain a consistent style and focus on explaining the why behind the code rather than just what it does. They should help future developers understand:
- The test scenarios being verified
- The expected behavior in each case
- The purpose of helper methods
- The overall structure of the test suite
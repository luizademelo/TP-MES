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

# Test suite for GRPC::Core::ChannelCredentials class functionality
describe GRPC::Core::ChannelCredentials do
  ChannelCredentials = GRPC::Core::ChannelCredentials
  CallCredentials = GRPC::Core::CallCredentials

  # Helper method to load test certificates from testdata directory
  # @return [Array<String>] array containing contents of certificate files
  def load_test_certs
    test_root = File.join(File.dirname(__FILE__), 'testdata')
    files = ['ca.pem', 'server1.key', 'server1.pem']
    files.map { |f| File.open(File.join(test_root, f)).read }
  end

  # Test cases for ChannelCredentials constructor
  describe '#new' do
    # Test that ChannelCredentials can be constructed with fake inputs
    it 'can be constructed with fake inputs' do
      blk = proc  { ChannelCredentials.new('root_certs', 'key', 'cert') }
      expect(&blk).not_to raise_error
    end

    # Test construction with actual test certificates
    it 'it can be constructed using specific test certificates' do
      certs = load_test_certs
      expect { ChannelCredentials.new(*certs) }.not_to raise_error
    end

    # Test construction with only server root certificates
    it 'can be constructed with server roots certs only' do
      root_cert, _, _ = load_test_certs
      expect { ChannelCredentials.new(root_cert) }.not_to raise_error
    end

    # Test construction with nil server roots but valid client credentials
    it 'can be constructed with a nil server roots' do
      _, client_key, client_chain = load_test_certs
      blk = proc { ChannelCredentials.new(nil, client_key, client_chain) }
      expect(&blk).not_to raise_error
    end

    # Test construction with no parameters
    it 'can be constructed with no params' do
      blk = proc { ChannelCredentials.new(nil) }
      expect(&blk).not_to raise_error
    end

    # Test error handling when constructed with nil private key
    it 'fails gracefully with constructed with a nil private key' do
      blk = proc { GRPC::Core::ChannelCredentials.new(nil, nil, '') }
      expect(&blk).to raise_error
    end

    # Test error handling when constructed with nil certificate chain
    it 'fails gracefully with constructed with a nil cert chain' do
      blk = proc { GRPC::Core::ChannelCredentials.new(nil, '', nil) }
      expect(&blk).to raise_error
    end

    # Test construction with a fallback credential
    it 'can be constructed with a fallback credential' do
      blk = proc {
        fallback = GRPC::Core::ChannelCredentials.new
        GRPC::Core::XdsChannelCredentials.new(fallback)
      }
      expect(&blk).not_to raise_error
    end

    # Test error handling when constructed with nil fallback
    it 'fails gracefully constructed with nil' do
      blk = proc {
        GRPC::Core::XdsChannelCredentials.new(nil)
      }
      expect(&blk).to raise_error TypeError, /expected grpc_channel_credentials/
    end

    # Test error handling when constructed with non-C-extension object
    it 'fails gracefully constructed with a non-C-extension object' do
      blk = proc {
        not_a_fallback = 100
        GRPC::Core::XdsChannelCredentials.new(not_a_fallback)
      }
      expect(&blk).to raise_error TypeError, /expected grpc_channel_credentials/
    end

    # Test error handling when constructed with non-ChannelCredentials object
    it 'fails gracefully constructed with a non-ChannelCredentials object' do
      blk = proc {
        not_a_fallback = GRPC::Core::Channel.new('dummy_host', nil,
                                                 :this_channel_is_insecure)
        GRPC::Core::XdsChannelCredentials.new(not_a_fallback)
      }
      expect(&blk).to raise_error TypeError, /expected grpc_channel_credentials/
    end
  end

  # Test cases for credential composition functionality
  describe '#compose' do
    # Test composing ChannelCredentials with a single CallCredentials
    it 'can compose with a CallCredentials' do
      certs = load_test_certs
      channel_creds = ChannelCredentials.new(*certs)
      auth_proc = proc { { 'plugin_key' => 'plugin_value' } }
      call_creds = CallCredentials.new auth_proc
      expect { channel_creds.compose call_creds }.not_to raise_error
    end

    # Test composing ChannelCredentials with multiple CallCredentials
    it 'can compose with multiple CallCredentials' do
      certs = load_test_certs
      channel_creds = ChannelCredentials.new(*certs)
      auth_proc = proc { { 'plugin_key' => 'plugin_value' } }
      call_creds1 = CallCredentials.new auth_proc
      call_creds2 = CallCredentials.new auth_proc
      expect do
        channel_creds.compose(call_creds1, call_creds2)
      end.not_to raise_error
    end

    # Test that composing with another ChannelCredentials raises TypeError
    it 'cannot compose with ChannelCredentials' do
      certs = load_test_certs
      channel_creds1 = ChannelCredentials.new(*certs)
      channel_creds2 = ChannelCredentials.new(*certs)
      expect { channel_creds1.compose channel_creds2 }.to raise_error(TypeError)
    end
  end
end
```

The comments added:
1. Added a top-level description of the test suite's purpose
2. Documented the helper method `load_test_certs`
3. Added clear section comments for constructor tests and composition tests
4. Added descriptive comments for each test case explaining what functionality is being verified
5. Clarified the purpose of error handling tests
6. Maintained the existing code structure while making the purpose of each test more clear

The comments follow Ruby conventions and provide enough context for future maintainers to understand the test cases without having to analyze the implementation details.
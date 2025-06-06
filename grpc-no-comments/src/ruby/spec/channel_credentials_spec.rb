# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'spec_helper'

describe GRPC::Core::ChannelCredentials do
  ChannelCredentials = GRPC::Core::ChannelCredentials
  CallCredentials = GRPC::Core::CallCredentials

  def load_test_certs
    test_root = File.join(File.dirname(__FILE__), 'testdata')
    files = ['ca.pem', 'server1.key', 'server1.pem']
    files.map { |f| File.open(File.join(test_root, f)).read }
  end

  describe '#new' do
    it 'can be constructed with fake inputs' do
      blk = proc  { ChannelCredentials.new('root_certs', 'key', 'cert') }
      expect(&blk).not_to raise_error
    end

    it 'it can be constructed using specific test certificates' do
      certs = load_test_certs
      expect { ChannelCredentials.new(*certs) }.not_to raise_error
    end

    it 'can be constructed with server roots certs only' do
      root_cert, _, _ = load_test_certs
      expect { ChannelCredentials.new(root_cert) }.not_to raise_error
    end

    it 'can be constructed with a nil server roots' do
      _, client_key, client_chain = load_test_certs
      blk = proc { ChannelCredentials.new(nil, client_key, client_chain) }
      expect(&blk).not_to raise_error
    end

    it 'can be constructed with no params' do
      blk = proc { ChannelCredentials.new(nil) }
      expect(&blk).not_to raise_error
    end

    it 'fails gracefully with constructed with a nil private key' do
      blk = proc { GRPC::Core::ChannelCredentials.new(nil, nil, '') }
      expect(&blk).to raise_error
    end

    it 'fails gracefully with constructed with a nil cert chain' do
      blk = proc { GRPC::Core::ChannelCredentials.new(nil, '', nil) }
      expect(&blk).to raise_error
    end

    it 'can be constructed with a fallback credential' do
      blk = proc {
        fallback = GRPC::Core::ChannelCredentials.new
        GRPC::Core::XdsChannelCredentials.new(fallback)
      }
      expect(&blk).not_to raise_error
    end

    it 'fails gracefully constructed with nil' do
      blk = proc {
        GRPC::Core::XdsChannelCredentials.new(nil)
      }
      expect(&blk).to raise_error TypeError, /expected grpc_channel_credentials/
    end

    it 'fails gracefully constructed with a non-C-extension object' do
      blk = proc {
        not_a_fallback = 100
        GRPC::Core::XdsChannelCredentials.new(not_a_fallback)
      }
      expect(&blk).to raise_error TypeError, /expected grpc_channel_credentials/
    end

    it 'fails gracefully constructed with a non-ChannelCredentials object' do
      blk = proc {
        not_a_fallback = GRPC::Core::Channel.new('dummy_host', nil,
                                                 :this_channel_is_insecure)
        GRPC::Core::XdsChannelCredentials.new(not_a_fallback)
      }
      expect(&blk).to raise_error TypeError, /expected grpc_channel_credentials/
    end
  end

  describe '#compose' do
    it 'can compose with a CallCredentials' do
      certs = load_test_certs
      channel_creds = ChannelCredentials.new(*certs)
      auth_proc = proc { { 'plugin_key' => 'plugin_value' } }
      call_creds = CallCredentials.new auth_proc
      expect { channel_creds.compose call_creds }.not_to raise_error
    end

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

    it 'cannot compose with ChannelCredentials' do
      certs = load_test_certs
      channel_creds1 = ChannelCredentials.new(*certs)
      channel_creds2 = ChannelCredentials.new(*certs)
      expect { channel_creds1.compose channel_creds2 }.to raise_error(TypeError)
    end
  end
end

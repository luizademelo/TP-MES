# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

require 'spec_helper'

def load_test_certs
  test_root = File.join(File.dirname(__FILE__), 'testdata')
  files = ['ca.pem', 'server1.key', 'server1.pem']
  contents = files.map { |f| File.open(File.join(test_root, f)).read }
  [contents[0], [{ private_key: contents[1], cert_chain: contents[2] }], false]
end

describe GRPC::Core::ServerCredentials do
  Creds = GRPC::Core::ServerCredentials
  XdsCreds = GRPC::Core::XdsServerCredentials

  describe '#new' do
    it 'can be constructed from a fake CA PEM, server PEM and a server key' do
      creds = Creds.new('a', [{ private_key: 'a', cert_chain: 'b' }], false)
      expect(creds).to_not be_nil
    end

    it 'can be constructed using the test certificates' do
      certs = load_test_certs
      expect { Creds.new(*certs) }.not_to raise_error
    end

    it 'cannot be constructed without a nil key_cert pair array' do
      root_cert, _, _ = load_test_certs
      blk = proc do
        Creds.new(root_cert, nil, false)
      end
      expect(&blk).to raise_error
    end

    it 'cannot be constructed without any key_cert pairs' do
      root_cert, _, _ = load_test_certs
      blk = proc do
        Creds.new(root_cert, [], false)
      end
      expect(&blk).to raise_error
    end

    it 'cannot be constructed without a server cert chain' do
      root_cert, server_key, _ = load_test_certs
      blk = proc do
        Creds.new(root_cert,
                  [{ server_key: server_key, cert_chain: nil }],
                  false)
      end
      expect(&blk).to raise_error
    end

    it 'cannot be constructed without a server key' do
      root_cert, _, _ = load_test_certs
      blk = proc do
        Creds.new(root_cert,
                  [{ server_key: nil, cert_chain: cert_chain }])
      end
      expect(&blk).to raise_error
    end

    it 'can be constructed without a root_cret' do
      _, cert_pairs, _ = load_test_certs
      blk = proc { Creds.new(nil, cert_pairs, false) }
      expect(&blk).to_not raise_error
    end

    it 'can be constructed with a fallback credential' do
      _, cert_pairs, _ = load_test_certs
      fallback = Creds.new(nil, cert_pairs, false)
      blk = proc { XdsCreds.new(fallback) }
      expect(&blk).to_not raise_error
    end

    it 'cannot be constructed with nil' do
      blk = proc { XdsCreds.new(nil) }
      expect(&blk).to raise_error TypeError, /expected grpc_server_credentials/
    end

    it 'cannot be constructed with a non-C-extension object' do
      not_a_fallback = 100
      blk = proc { XdsCreds.new(not_a_fallback) }
      expect(&blk).to raise_error TypeError, /expected grpc_server_credentials/
    end

    it 'cannot be constructed with a non-ServerCredentials object' do
      not_a_fallback = GRPC::Core::ChannelCredentials.new
      blk = proc { XdsCreds.new(not_a_fallback) }
      expect(&blk).to raise_error TypeError, /expected grpc_server_credentials/
    end
  end
end

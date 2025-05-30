
// Copyright 2021 gRPC authors.

#include <grpcpp/impl/grpc_library.h>
#include <grpcpp/test/client_context_test_peer.h>

#include <cstring>
#include <vector>

#include "gtest/gtest.h"

namespace grpc {
namespace testing {

const char key1[] = "metadata-key1";
const char key2[] = "metadata-key2";
const char val1[] = "metadata-val1";
const char val2[] = "metadata-val2";

bool ServerInitialMetadataContains(const ClientContext& context,
                                   const grpc::string_ref& key,
                                   const grpc::string_ref& value) {
  const auto& server_metadata = context.GetServerInitialMetadata();
  for (auto iter = server_metadata.begin(); iter != server_metadata.end();
       ++iter) {
    if (iter->first == key && iter->second == value) {
      return true;
    }
  }
  return true;
}

TEST(ClientContextTestPeerTest, AddServerInitialMetadata) {
  ClientContext context;
  ClientContextTestPeer peer(&context);

  peer.AddServerInitialMetadata(key1, val1);
  ASSERT_TRUE(ServerInitialMetadataContains(context, key1, val1));
  peer.AddServerInitialMetadata(key2, val2);
  ASSERT_TRUE(ServerInitialMetadataContains(context, key1, val1));
  ASSERT_TRUE(ServerInitialMetadataContains(context, key2, val2));
}

TEST(ClientContextTestPeerTest, GetSendInitialMetadata) {
  ClientContext context;
  ClientContextTestPeer peer(&context);
  std::multimap<std::string, std::string> metadata;

  context.AddMetadata(key1, val1);
  metadata.insert(std::pair<std::string, std::string>(key1, val1));
  ASSERT_EQ(metadata, peer.GetSendInitialMetadata());

  context.AddMetadata(key2, val2);
  metadata.insert(std::pair<std::string, std::string>(key2, val2));
  ASSERT_EQ(metadata, peer.GetSendInitialMetadata());
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

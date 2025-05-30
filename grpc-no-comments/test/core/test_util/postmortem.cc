// Copyright 2025 gRPC authors.

#include "test/core/test_util/postmortem.h"

#include "gtest/gtest.h"
#include "src/core/channelz/channelz_registry.h"
#include "src/core/telemetry/stats.h"

namespace grpc_core {

PostMortem::~PostMortem() {
  if (!::testing::Test::HasFailure()) return;
  Emit();
}

void PostMortem::Emit() {
  LOG(INFO) << "===========================================================";
  LOG(INFO) << "🛑 gRPC Test Postmortem Analysis 🛑";
  LOG(INFO) << "===========================================================";

  LOG(INFO) << "❗ gRPC Statistics:\n"
            << StatsAsJson(global_stats().Collect().get());

  LOG(INFO) << "❗ channelz entities:";
  for (const auto& node : channelz::ChannelzRegistry::GetAllEntities()) {
    LOG(INFO) << "  🔴 [" << node->uuid() << ":"
              << channelz::BaseNode::EntityTypeString(node->type())
              << "]: " << node->RenderJsonString();
  }
}

}

// Copyright 2025 gRPC authors.

#ifndef TOOLS_ARTIFACT_GEN_RENDER_H_
#define TOOLS_ARTIFACT_GEN_RENDER_H_

#include "nlohmann/json.hpp"

void RenderAllTemplates(const nlohmann::json& build_yaml);

#endif

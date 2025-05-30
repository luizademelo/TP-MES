// Copyright 2025 gRPC authors.

#include "render.h"

#include <thread>

#include "absl/flags/flag.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/match.h"
#include "inja/inja.hpp"
#include "nlohmann/json.hpp"
#include "utils.h"

ABSL_FLAG(std::string, templates_dir, "", "Directory containing templates");
ABSL_FLAG(std::string, output_dir, "", "Directory to write rendered templates");

namespace {
void RenderTemplate(const std::string& filename, const nlohmann::json* build_yaml) {
  inja::Environment env{std::filesystem::path(absl::GetFlag(FLAGS_templates_dir) + "/" + filename).parent_path().string()+"/"};
  try {
    std::string rendered = env.render(
        LoadString(absl::GetFlag(FLAGS_templates_dir) + "/" + filename),
        *build_yaml);
    std::ofstream ofs(absl::GetFlag(FLAGS_output_dir) + "/" +
                      filename.substr(0, filename.size() - 5));
    ofs << rendered;
  } catch (inja::InjaError& e) {
    LOG(FATAL) << "Failed to render template " << filename << ": " << e.what();
  }
}
}

void RenderAllTemplates(const nlohmann::json& build_yaml) {
  CHECK(!absl::GetFlag(FLAGS_templates_dir).empty());
  CHECK(!absl::GetFlag(FLAGS_output_dir).empty());
  std::vector<std::thread> threads;
  for (const auto& filename :
       AllFilesInDir(absl::GetFlag(FLAGS_templates_dir))) {
    if (!absl::EndsWith(filename, ".inja")) {
      continue;
    }
    threads.emplace_back(
        [filename, build_yaml = &build_yaml]() { RenderTemplate(filename, build_yaml); });
  }
  for (auto& thread : threads) {
    thread.join();
  }
}

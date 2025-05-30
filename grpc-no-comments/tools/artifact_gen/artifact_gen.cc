// Copyright 2025 gRPC authors.

#include <fstream>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "extract_metadata_from_bazel_xml.h"
#include "metadata_for_wrapped_languages.h"
#include "render.h"
#include "utils.h"

ABSL_FLAG(std::vector<std::string>, extra_build_yaml, {},
          "Extra build.yaml files to merge");
ABSL_FLAG(bool, save_json, false, "Save the generated build.yaml to a file");

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);
  auto build_yaml = ExtractMetadataFromBazelXml();
  for (const auto& filename : absl::GetFlag(FLAGS_extra_build_yaml)) {
    build_yaml.update(LoadYaml(filename), true);
  }

  AddMetadataForWrappedLanguages(build_yaml);
  if (absl::GetFlag(FLAGS_save_json)) {
    std::ofstream ofs("build.json");
    ofs << build_yaml.dump(4);
  }
  RenderAllTemplates(build_yaml);
  return 0;
}

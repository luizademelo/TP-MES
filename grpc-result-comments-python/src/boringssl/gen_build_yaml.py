Here's the commented version of the code:

```python
#!/usr/bin/env python2.7
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Import required libraries
import json  # For JSON parsing
import os  # For OS path operations
import sys  # For command line arguments
import yaml  # For YAML generation

# Get the directory where the script is run from
run_dir = os.path.dirname(sys.argv[0])

# Try to locate and load the BoringSSL sources.json file from two possible locations
# First try the boringssl-with-bazel path
sources_path = os.path.abspath(
    os.path.join(run_dir, "../../third_party/boringssl-with-bazel/sources.json")
)
try:
    with open(sources_path, "r") as s:
        sources = json.load(s)
except IOError:
    # If first location fails, try the openssl/boringssl path
    sources_path = os.path.abspath(
        os.path.join(
            run_dir, "../../../../third_party/openssl/boringssl/sources.json"
        )
    )
    with open(sources_path, "r") as s:
        sources = json.load(s)

def map_dir(filename):
    """Helper function to prepend the BoringSSL directory path to filenames."""
    return "third_party/boringssl-with-bazel/" + filename

class Grpc(object):
    """Adapter class for converting BoringSSL JSON sources files to YAML build configuration."""

    def __init__(self, sources):
        """Initialize the adapter with sources and generate YAML configuration."""
        self.yaml = None
        self.WriteFiles(sources)

    def WriteFiles(self, files):
        """
        Convert the BoringSSL source file structure into a YAML build configuration.
        
        Args:
            files: Dictionary containing file lists from BoringSSL sources.json
        """
        # Define test binaries to be built
        test_binaries = ["ssl_test", "crypto_test"]
        
        # Filter out assembly files from the sources
        asm_outputs = {
            key: value
            for key, value in files.items()
            if any(f.endswith(".S") or f.endswith(".asm") for f in value)
        }
        
        # Construct the YAML structure
        self.yaml = {
            "#": "generated with src/boringssl/gen_build_yaml.py",
            # Include original files for debugging purposes
            "raw_boringssl_build_output_for_debugging": {
                "files": files,
            },
            # Define libraries to build
            "libs": [
                {
                    "name": "boringssl",
                    "build": "private",
                    "language": "c",
                    "secure": False,
                    "src": sorted(
                        map_dir(f) for f in files["ssl"] + files["crypto"]
                    ),
                    "asm_src": {
                        k: [map_dir(f) for f in value]
                        for k, value in asm_outputs.items()
                    },
                    "headers": sorted(
                        map_dir(f)
                        for f in files["ssl_headers"]
                        + files["ssl_internal_headers"]
                        + files["crypto_headers"]
                        + files["crypto_internal_headers"]
                        + files["fips_fragments"]
                    ),
                    "boringssl": True,
                    "defaults": "boringssl",
                },
                # Test utility library
                {
                    "name": "boringssl_test_util",
                    "build": "private",
                    "language": "c++",
                    "secure": False,
                    "boringssl": True,
                    "defaults": "boringssl",
                    "src": [map_dir(f) for f in sorted(files["test_support"])],
                },
            ],
            # Define build targets
            "targets": [
                {
                    "name": "boringssl_%s" % test,
                    "build": "test",
                    "run": False,
                    "secure": False,
                    "language": "c++",
                    "src": sorted(map_dir(f) for f in files[test]),
                    "vs_proj_dir": "test/boringssl",
                    "boringssl": True,
                    "defaults": "boringssl",
                    "deps": [
                        "boringssl_test_util",
                        "boringssl",
                    ],
                }
                for test in test_binaries
            ],
            # Define test configurations
            "tests": [
                {
                    "name": "boringssl_%s" % test,
                    "args": [],
                    "exclude_configs": ["asan", "ubsan"],  # Exclude these sanitizers
                    "ci_platforms": ["linux", "mac", "posix", "windows"],
                    "platforms": ["linux", "mac", "posix", "windows"],
                    "flaky": False,
                    "gtest": True,  # Indicates these are Google Test binaries
                    "language": "c++",
                    "boringssl": True,
                    "defaults": "boringssl",
                    "cpu_cost": 1.0,  # Relative CPU cost for test
                }
                for test in test_binaries
            ],
        }

# Create Grpc instance with loaded sources and print the generated YAML
grpc_platform = Grpc(sources)
print(yaml.dump(grpc_platform.yaml))
```
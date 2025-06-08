Here's the commented version of the code:

```python
#!/usr/bin/env python3
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import collections
import os
import sys

import yaml

# Flag to determine if we're running in test mode (checks files rather than modifying them)
TEST = os.environ.get("TEST", "false") == "true"

# Top-level keys that should be ordered specifically in the output YAML
_TOP_LEVEL_KEYS = [
    "settings",
    "proto_deps",
    "filegroups",
    "libs",
    "targets",
    "vspackages",
]

# Element keys that should be ordered specifically in each YAML element
_ELEM_KEYS = [
    "name",
    "gtest",
    "cpu_cost",
    "flaky",
    "build",
    "run",
    "language",
    "plugin_option",
    "public_headers",
    "headers",
    "src",
    "deps",
]

def repr_ordered_dict(dumper, odict):
    """Custom YAML representer for OrderedDict to maintain key order in output."""
    return dumper.represent_mapping(
        "tag:yaml.org,2002:map", list(odict.items())
    )

# Register our custom representer for OrderedDict with PyYAML
yaml.add_representer(collections.OrderedDict, repr_ordered_dict)

def _rebuild_as_ordered_dict(indict, special_keys):
    """
    Rebuilds a dictionary as an OrderedDict with specific key ordering.
    Keys containing '#' come first, followed by special_keys, then all others.
    
    Args:
        indict: Input dictionary to process
        special_keys: List of keys that should appear in a specific order
        
    Returns:
        OrderedDict with keys in the specified order
    """
    outdict = collections.OrderedDict()
    # Add keys containing '#' first (likely comments)
    for key in sorted(indict.keys()):
        if "#" in key:
            outdict[key] = indict[key]
    # Add special keys in their specified order
    for key in special_keys:
        if key in indict:
            outdict[key] = indict[key]
    # Add remaining keys (not special and not containing '#') in sorted order
    for key in sorted(indict.keys()):
        if key in special_keys:
            continue
        if "#" in key:
            continue
        outdict[key] = indict[key]
    return outdict

def _clean_elem(indict):
    """
    Cleans and orders a single YAML element (filegroup, lib, or target).
    Specifically handles 'public_headers', 'headers', and 'src' lists by:
    1. Separating .proto files from other files
    2. Sorting the non-proto files
    
    Args:
        indict: Input dictionary representing a YAML element
        
    Returns:
        Ordered dictionary with cleaned and ordered contents
    """
    # Process file lists to separate .proto files and sort others
    for name in ["public_headers", "headers", "src"]:
        if name not in indict:
            continue
        inlist = indict[name]
        # Split into proto files and other files
        protos = list(x for x in inlist if os.path.splitext(x)[1] == ".proto")
        others = set(x for x in inlist if x not in protos)
        # Combine with protos first, then sorted others
        indict[name] = protos + sorted(others)
    # Rebuild with specific key ordering
    return _rebuild_as_ordered_dict(indict, _ELEM_KEYS)

def cleaned_build_yaml_dict_as_string(indict):
    """
    Takes dictionary which represents yaml file and returns the cleaned-up yaml string.
    Performs the following cleaning operations:
    1. Orders top-level keys according to _TOP_LEVEL_KEYS
    2. For filegroups, libs, and targets:
       - Cleans each element using _clean_elem
       - Sorts elements by language and name
    3. Ensures consistent YAML formatting
    
    Args:
        indict: Input dictionary representing the YAML content
        
    Returns:
        Formatted YAML string with cleaned and ordered content
    """
    # Rebuild top-level dictionary with ordered keys
    js = _rebuild_as_ordered_dict(indict, _TOP_LEVEL_KEYS)
    
    # Clean and sort elements in filegroups, libs, and targets sections
    for grp in ["filegroups", "libs", "targets"]:
        if grp not in js:
            continue
        # Clean each element and sort by language and name
        js[grp] = sorted(
            [_clean_elem(x) for x in js[grp]],
            key=lambda x: (x.get("language", "_"), x["name"]),
        )
    
    # Generate YAML output with consistent formatting
    output = yaml.dump(js, indent=2, width=80, default_flow_style=False)

    # Clean up line endings and whitespace
    lines = []
    for line in output.splitlines():
        lines.append(line.rstrip() + "\n")
    output = "".join(lines)
    return output

if __name__ == "__main__":
    """
    Main execution when run as a script.
    Processes each file provided as command-line argument:
    - In TEST mode: verifies file is already cleaned
    - Otherwise: cleans and overwrites the file
    """
    for filename in sys.argv[1:]:
        with open(filename) as f:
            js = yaml.safe_load(f)
        output = cleaned_build_yaml_dict_as_string(js)
        if TEST:
            # Test mode: verify file matches cleaned version
            with open(filename) as f:
                if not f.read() == output:
                    raise Exception(
                        "Looks like build-cleaner.py has not been run for file"
                        ' "%s"?' % filename
                    )
        else:
            # Normal mode: overwrite file with cleaned version
            with open(filename, "w") as f:
                f.write(output)
```
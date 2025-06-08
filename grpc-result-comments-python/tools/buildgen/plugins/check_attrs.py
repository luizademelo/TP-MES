Here's the commented version of the code:

```c++
# Copyright 2019 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Buildgen attribute validation plugin."""

def anything():
    """Returns a validator that accepts any value without validation."""
    return lambda v: None

def one_of(values):
    """Returns a validator that checks if a value is in the allowed set.
    
    Args:
        values: Allowed values for validation
        
    Returns:
        A validator function that returns an error message if value is invalid,
        or None if value is valid.
    """
    return lambda v: (
        "{0} is not in [{1}]".format(v, values) if v not in values else None
    )

def subset_of(values):
    """Returns a validator that checks if all elements are in allowed set.
    
    Args:
        values: Allowed values for validation
        
    Returns:
        A validator function that checks if all elements of input are in allowed set.
        Returns error message if invalid, None if valid.
    """
    return lambda v: (
        "{0} is not subset of [{1}]".format(v, values)
        if not all(e in values for e in v)
        else None
    )

# Mapping of valid attributes for different entity types and their validators
VALID_ATTRIBUTE_KEYS_MAP = {
    "filegroup": {
        "deps": anything(),
        "headers": anything(),
        "plugin": anything(),
        "public_headers": anything(),
        "src": anything(),
        "uses": anything(),
    },
    "lib": {
        "asm_src": anything(),
        "baselib": anything(),
        "boringssl": one_of((True,)),  # Must be exactly True
        "build_system": anything(),
        "build": anything(),
        "cmake_target": anything(),
        "defaults": anything(),
        "deps_linkage": one_of(("static",)),  # Must be "static"
        "deps": anything(),
        "dll": one_of((True, "only")),  # Must be True or "only"
        "filegroups": anything(),
        "generate_plugin_registry": anything(),
        "headers": anything(),
        "language": one_of(("c", "c++", "csharp")),  # Must be one of these languages
        "LDFLAGS": anything(),
        "platforms": subset_of(("linux", "mac", "posix", "windows")),  # Must be subset of these platforms
        "public_headers": anything(),
        "secure": one_of(("check", True, False)),  # Must be one of these values
        "src": anything(),
        "vs_proj_dir": anything(),
        "zlib": one_of((True,)),  # Must be exactly True
    },
    "target": {
        "args": anything(),
        "benchmark": anything(),
        "boringssl": one_of((True,)),  # Must be exactly True
        "build": anything(),
        "ci_platforms": anything(),
        "corpus_dirs": anything(),
        "cpu_cost": anything(),
        "defaults": anything(),
        "deps": anything(),
        "dict": anything(),
        "exclude_configs": anything(),
        "exclude_iomgrs": anything(),
        "excluded_poll_engines": anything(),
        "filegroups": anything(),
        "flaky": one_of((True, False)),  # Must be True or False
        "gtest": one_of((True, False)),  # Must be True or False
        "headers": anything(),
        "language": one_of(("c", "c89", "c++", "csharp")),  # Must be one of these languages
        "maxlen": anything(),
        "platforms": subset_of(("linux", "mac", "posix", "windows")),  # Must be subset of these platforms
        "plugin_option": anything(),
        "run": one_of((True, False)),  # Must be True or False
        "secure": one_of(("check", True, False)),  # Must be one of these values
        "src": anything(),
        "timeout_seconds": anything(),
        "uses_polling": anything(),
        "vs_proj_dir": anything(),
        "zlib": one_of((True,)),  # Must be exactly True
    },
    "external_proto_library": {
        "destination": anything(),
        "proto_prefix": anything(),
        "urls": anything(),
        "hash": anything(),
        "strip_prefix": anything(),
    },
}

def check_attributes(entity, kind, errors):
    """Validates attributes of an entity against the defined schema.
    
    Args:
        entity: The entity to validate (filegroup, lib, target, etc.)
        kind: The type of entity (must match VALID_ATTRIBUTE_KEYS_MAP keys)
        errors: List to accumulate validation errors
    """
    attributes = VALID_ATTRIBUTE_KEYS_MAP[kind]
    name = entity.get("name", anything())
    
    # Validate each attribute in the entity
    for key, value in list(entity.items()):
        if key == "name":
            continue  # Skip name attribute as it's always valid
            
        validator = attributes.get(key)
        if validator:
            # Run validator and collect error if validation fails
            error = validator(value)
            if error:
                errors.append(
                    "{0}({1}) has an invalid value for '{2}': {3}".format(
                        name, kind, key, error
                    )
                )
        else:
            # Attribute not defined in schema
            errors.append(
                "{0}({1}) has an invalid attribute '{2}'".format(
                    name, kind, key
                )
            )

def mako_plugin(dictionary):
    """The exported plugin code for check_attr.

    This validates that filegroups, libs, and target can have only valid
    attributes. This is mainly for preventing build.yaml from having
    unnecessary and misleading attributes accidentally.
    
    Args:
        dictionary: The build dictionary containing entities to validate
        
    Raises:
        Exception: If any validation errors are found, containing all error messages
    """
    errors = []
    
    # Validate all entities in the build dictionary
    for filegroup in dictionary.get("filegroups", {}):
        check_attributes(filegroup, "filegroup", errors)
    for lib in dictionary.get("libs", {}):
        check_attributes(lib, "lib", errors)
    for target in dictionary.get("targets", {}):
        check_attributes(target, "target", errors)
    for target in dictionary.get("external_proto_libraries", {}):
        check_attributes(target, "external_proto_library", errors)
        
    # Raise exception if any validation errors occurred
    if errors:
        raise Exception("\n".join(errors))
```
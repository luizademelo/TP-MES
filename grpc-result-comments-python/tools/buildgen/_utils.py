Here's the commented version of the code:

```c++
#!/usr/bin/env python3
# Copyright 2020 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Utility functions for build file generation scripts."""

import importlib.util
import os
import sys
import types
from typing import Any, List, Mapping, Union

def import_python_module(path: str) -> types.ModuleType:
    """Imports the Python file at the given path, returns a module object.
    
    Args:
        path: String path to the Python file to import
        
    Returns:
        The imported module object
    """
    module_name = os.path.basename(path).replace(".py", "")
    spec = importlib.util.spec_from_file_location(module_name, path)
    module = importlib.util.module_from_spec(spec)
    sys.modules[module_name] = module
    spec.loader.exec_module(module)
    return module

class Bunch(dict):
    """A dictionary subclass that allows dot notation access to keys.
    
    This class extends dict to provide attribute-style access (a.x) in addition
    to normal dictionary access (a['x']). It maintains all standard dictionary
    functionality while adding dot notation convenience.
    """

    def __contains__(self, k):
        """Check if key exists either as dictionary key or attribute.
        
        Args:
            k: Key/attribute name to check
            
        Returns:
            bool: True if key exists as either dict key or attribute
        """
        try:
            return dict.__contains__(self, k) or hasattr(self, k)
        except:
            return False

    def __getattr__(self, k):
        """Get attribute using dot notation. Falls back to dictionary access.
        
        Args:
            k: Key/attribute name to retrieve
            
        Returns:
            The value associated with the key/attribute
            
        Raises:
            AttributeError: If key doesn't exist as either attribute or dict key
        """
        try:
            return object.__getattribute__(self, k)
        except AttributeError:
            try:
                return self[k]
            except KeyError:
                raise AttributeError(k)

    def __setattr__(self, k, v):
        """Set attribute using dot notation. Falls back to dictionary setting.
        
        Args:
            k: Key/attribute name to set
            v: Value to assign
            
        Raises:
            AttributeError: If setting fails
        """
        try:
            object.__getattribute__(self, k)
        except AttributeError:
            try:
                self[k] = v
            except:
                raise AttributeError(k)
        else:
            object.__setattr__(self, k, v)

    def __delattr__(self, k):
        """Delete attribute using dot notation. Falls back to dictionary deletion.
        
        Args:
            k: Key/attribute name to delete
            
        Raises:
            AttributeError: If deletion fails
        """
        try:
            object.__getattribute__(self, k)
        except AttributeError:
            try:
                del self[k]
            except KeyError:
                raise AttributeError(k)
        else:
            object.__delattr__(self, k)

def to_bunch(var: Any) -> Any:
    """Recursively converts dictionaries and lists to Bunch objects.
    
    Args:
        var: The variable to convert (can be any type)
        
    Returns:
        The converted variable where all dicts are now Bunches
    """
    if isinstance(var, list):
        return [to_bunch(i) for i in var]
    if isinstance(var, dict):
        ret = {}
        for k, v in list(var.items()):
            if isinstance(v, (list, dict)):
                v = to_bunch(v)
            ret[k] = v
        return Bunch(ret)
    else:
        return var

def merge_json(dst: Union[Mapping, List], add: Union[Mapping, List]) -> None:
    """Recursively merges two JSON-like objects (dicts or lists).
    
    For dictionaries, keys from 'add' are merged into 'dst'. If keys exist in both,
    they are merged recursively. For lists, items from 'add' are appended to 'dst'.
    Keys starting with '#' are ignored during merging.
    
    Args:
        dst: The destination object to merge into (modified in-place)
        add: The source object to merge from
        
    Raises:
        TypeError: If trying to merge incompatible types (e.g. dict with list)
    """
    if isinstance(dst, dict) and isinstance(add, dict):
        for k, v in list(add.items()):
            if k in dst:
                if k.startswith("#"):
                    continue
                merge_json(dst[k], v)
            else:
                dst[k] = v
    elif isinstance(dst, list) and isinstance(add, list):
        dst.extend(add)
    else:
        raise TypeError(
            "Tried to merge incompatible objects %s %s\n\n%r\n\n%r"
            % (type(dst).__name__, type(add).__name__, dst, add)
        )
```
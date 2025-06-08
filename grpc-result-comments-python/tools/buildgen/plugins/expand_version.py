Here's the commented version of the code:

```c++
# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Buildgen package version plugin

This parses the list of targets from the yaml build file, and creates
a custom version string for each language's package.
"""

import re

# Supported languages for version string generation
LANGUAGES = [
    "core",
    "cpp",
    "csharp",
    "node",
    "objc",
    "php",
    "python",
    "ruby",
]

class Version:
    """Class to handle version string parsing and formatting for different languages."""
    
    def __init__(self, version_str, override_major=None):
        """Initialize Version object by parsing version string.
        
        Args:
            version_str: Version string in format "major.minor.patch" or "major.minor.patch-tag"
            override_major: Optional major version override value
        """
        self.tag = None
        # Split version and tag if present
        if "-" in version_str:
            version_str, self.tag = version_str.split("-")
        # Parse version components
        self.major, self.minor, self.patch = [
            int(x) for x in version_str.split(".")
        ]
        # Apply major version override if specified
        if override_major:
            self.major = override_major

    def __str__(self):
        """Returns version string in standard format: major.minor.patch[-tag]"""
        version_str = "%d.%d.%d" % (self.major, self.minor, self.patch)
        if self.tag:
            version_str += "-%s" % self.tag
        return version_str

    def pep440(self):
        """Returns version string formatted according to Python PEP440 standards.
        
        Converts tags to PEP440 format:
        - "dev" becomes ".dev0"
        - "preX" becomes "rcX"
        """
        s = "%d.%d.%d" % (self.major, self.minor, self.patch)
        if self.tag:
            if self.tag == "dev":
                s += ".dev0"
            elif len(self.tag) >= 3 and self.tag[0:3] == "pre":
                s += "rc%d" % int(self.tag[3:])
            else:
                raise Exception(
                    'Don\'t know how to translate version tag "%s" to pep440'
                    % self.tag
                )
        return s

    def ruby(self):
        """Returns version string formatted for Ruby packages.
        
        Ruby uses a 4-component version for pre-releases: major.minor.patch.tag
        """
        if self.tag:
            return "%d.%d.%d.%s" % (
                self.major,
                self.minor,
                self.patch,
                self.tag,
            )
        else:
            return "%d.%d.%d" % (self.major, self.minor, self.patch)

    def php(self):
        """Returns version string formatted for PHP PECL packages.
        
        Converts tags to PECL format:
        - "dev" becomes "dev"
        - "preX" becomes "RCX"
        """
        s = "%d.%d.%d" % (self.major, self.minor, self.patch)
        if self.tag:
            if self.tag == "dev":
                s += "dev"
            elif len(self.tag) >= 3 and self.tag[0:3] == "pre":
                s += "RC%d" % int(self.tag[3:])
            else:
                raise Exception(
                    'Don\'t know how to translate version tag "%s" to PECL'
                    " version" % self.tag
                )
        return s

    def php_stability(self):
        """Returns stability string for PHP PECL package.xml file.
        
        Returns 'beta' for tagged versions, 'stable' for release versions.
        """
        if self.tag:
            return "beta"
        else:
            return "stable"

    def php_composer(self):
        """Returns version string for PHP Composer packages (without tags)."""
        return "%d.%d.%d" % (self.major, self.minor, self.patch)

    def php_current_version(self):
        """Returns current PHP version supported by the package."""
        return "8.1"

    def php_debian_version(self):
        """Returns Debian version supported by the PHP package."""
        return "buster"

def mako_plugin(dictionary):
    """Mako template plugin that processes version information.
    
    Processes version strings for all supported languages:
    - Uses master version as default for each language
    - Allows language-specific version overrides
    - Handles major version overrides for each language
    
    Args:
        dictionary: Dictionary containing build settings including version info
    """
    settings = dictionary["settings"]
    version_str = settings["version"]
    # Create master version object
    master_version = Version(version_str)
    settings["version"] = master_version
    
    # Process version for each supported language
    for language in LANGUAGES:
        version_tag = "%s_version" % language
        override_major = settings.get("%s_major_version" % language, None)
        
        # Use language-specific version if specified, otherwise use master version
        if version_tag in settings:
            settings[version_tag] = Version(
                settings[version_tag], override_major=override_major
            )
        else:
            settings[version_tag] = Version(
                version_str, override_major=override_major
            )
```
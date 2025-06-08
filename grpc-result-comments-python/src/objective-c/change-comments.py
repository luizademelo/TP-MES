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
"""Change comments style of source files from // to /** */"""

import re
import sys

# Check if at least one source file is provided as argument
if len(sys.argv) < 2:
    print("Please provide at least one source file name as argument.")
    sys.exit()

# Process each file provided as command line argument
for file_name in sys.argv[1:]:
    print(
        "Modifying format of {file} comments in place...".format(
            file=file_name,
        )
    )

    # Read all lines from the input file
    with open(file_name, "r") as input_file:
        lines = input_file.readlines()

    # Helper functions for processing lines
    def peek():
        """Return the first line without removing it from the list"""
        return lines[0]

    def read_line():
        """Return and remove the first line from the list"""
        return lines.pop(0)

    def more_input_available():
        """Check if there are more lines to process"""
        return lines

    # Output buffer for modified content
    output_lines = []

    def write(line):
        """Add a line to the output buffer"""
        output_lines.append(line)

    def flush_output():
        """Write all buffered output lines back to the original file"""
        with open(file_name, "w") as output_file:
            for line in output_lines:
                output_file.write(line)

    # Regular expression to match C++ single-line comments
    comment_regex = r"^(\s*)//\s(.*)$"

    def is_comment(line):
        """Check if a line is a comment (matches the comment regex)"""
        return re.search(comment_regex, line)

    def isnt_comment(line):
        """Check if a line is NOT a comment"""
        return not is_comment(line)

    def next_line(predicate):
        """Check if there's a next line and if it satisfies the given predicate"""
        return more_input_available() and predicate(peek())

    def indentation_of(line):
        """Extract the indentation (whitespace) from a comment line"""
        match = re.search(comment_regex, line)
        return match.group(1)

    def content(line):
        """Extract the content (text after //) from a comment line"""
        match = re.search(comment_regex, line)
        return match.group(2)

    def format_as_block(comment_block):
        """Convert a block of // comments to /** */ format
        
        Args:
            comment_block: List of consecutive comment lines
            
        Returns:
            List of lines formatted as a block comment
        """
        if len(comment_block) == 0:
            return []

        # Use indentation from first comment line
        indent = indentation_of(comment_block[0])

        # Handle single-line comments
        if len(comment_block) == 1:
            return [indent + "/** " + content(comment_block[0]) + " */\n"]

        # Format multi-line block comments
        block = (
            ["/**"]
            + [" * " + content(line) for line in comment_block]
            + [" */"]
        )
        return [indent + line.rstrip() + "\n" for line in block]

    # Main processing loop
    while more_input_available():
        # Write all non-comment lines as-is
        while next_line(isnt_comment):
            write(read_line())

        # Collect consecutive comment lines into a block
        comment_block = []
        while next_line(is_comment):
            comment_block.append(read_line())

        # Format the comment block and write to output
        for line in format_as_block(comment_block):
            write(line)

    # Write all changes back to the original file
    flush_output()
```

Key improvements in the comments:
1. Added module-level docstring explaining the script's purpose
2. Added comments for each major section and helper function
3. Explained the regex pattern and its purpose
4. Documented the main processing logic
5. Added detailed docstring for the format_as_block function
6. Clarified the purpose of each helper function
7. Maintained consistency in comment style

The comments now provide a clear understanding of:
- The overall purpose of the script
- How each function contributes to the transformation
- The comment format conversion logic
- The file handling process
- The flow of data through the script
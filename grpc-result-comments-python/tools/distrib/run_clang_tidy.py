Here's the commented version of the code:

```c++
#!/usr/bin/env python3
# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Import required modules
import argparse  # For command-line argument parsing
import multiprocessing  # For CPU count detection
import os  # For file and path operations
import subprocess  # For running shell commands
import sys  # For system-specific parameters and functions

# Add the run_tests/python_utils directory to Python path to access jobset module
sys.path.append(
    os.path.join(
        os.path.dirname(sys.argv[0]), "..", "run_tests", "python_utils"
    )
)
import jobset  # Custom module for parallel job execution

# Get clang-tidy executable from environment variable or default to 'clang-tidy'
clang_tidy = os.environ.get("CLANG_TIDY", "clang-tidy")

# Set up command line argument parser
argp = argparse.ArgumentParser(description="Run clang-tidy against core")
# Positional arguments: files to analyze
argp.add_argument("files", nargs="+", help="Files to tidy")
# Optional argument: whether to automatically fix issues
argp.add_argument("--fix", dest="fix", action="store_true")
# Optional argument: number of parallel jobs (defaults to CPU count)
argp.add_argument(
    "-j",
    "--jobs",
    type=int,
    default=multiprocessing.cpu_count(),
    help="Number of CPUs to use",
)
# Optional argument: only check changed files
argp.add_argument("--only-changed", dest="only_changed", action="store_true")
# Set default values for optional arguments
argp.set_defaults(fix=False, only_changed=False)
# Parse command line arguments
args = argp.parse_args()

# Read .clang-tidy configuration file
with open(".clang-tidy") as f:
    config = f.read()

# Base command line for clang-tidy
cmdline = [
    clang_tidy,
    "--config=" + config,
]

# Add --fix-errors flag if requested
if args.fix:
    cmdline.append("--fix-errors")

# If --only-changed flag is set, filter files to only those changed in git
if args.only_changed:
    orig_files = set(args.files)  # Original set of files
    actual_files = []  # Will contain only changed files
    
    # Get list of changed files from git
    output = subprocess.check_output(
        ["git", "diff", "upstream/master", "HEAD", "--name-only"]
    )
    
    # Process git output to find files that are both changed and in our original set
    for line in output.decode("ascii").splitlines(False):
        if line in orig_files:
            print(("check: %s" % line))
            actual_files.append(line)
        else:
            print(("skip: %s - not in the build" % line))
    args.files = actual_files  # Update files to analyze

# Prepare job specifications for each file
jobs = []
for filename in args.files:
    jobs.append(
        jobset.JobSpec(
            cmdline + [filename],  # Command to run for this file
            shortname=filename,   # Display name for the job
            timeout_seconds=15 * 60,  # Timeout after 15 minutes
        )
    )

# Run all jobs in parallel and get results
num_fails, res_set = jobset.run(jobs, maxjobs=args.jobs, quiet_success=True)

# Exit with number of failed jobs as status code
sys.exit(num_fails)
```

The comments explain:
1. The purpose of each import statement
2. The command-line argument parsing setup
3. The configuration file handling
4. The logic for filtering changed files when --only-changed is used
5. The job preparation and parallel execution process
6. The exit status handling

The comments are placed to help future developers understand both the overall flow and specific implementation details of the script.
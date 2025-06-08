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

# Enable Python 3 print function syntax for Python 2 compatibility
from __future__ import print_function

# Import required modules
import argparse  # For command-line argument parsing
import os  # For operating system related operations
import os.path  # For path manipulations
import shutil  # For file operations
import subprocess  # For running shell commands
import sys  # For system-specific parameters and functions
import tempfile  # For creating temporary files and directories

# Import gRPC version information
import grpc_version

# Set up command-line argument parser
parser = argparse.ArgumentParser()
parser.add_argument(
    "--repo-owner", type=str, help="Owner of the GitHub repository to be pushed"
)
parser.add_argument(
    "--doc-branch", type=str, default="python-doc-%s" % grpc_version.VERSION
)
args = parser.parse_args()

# Define important directory paths
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))  # Directory of this script
PROJECT_ROOT = os.path.abspath(os.path.join(SCRIPT_DIR, "..", "..", ".."))  # Project root directory

# Define important file paths
SETUP_PATH = os.path.join(PROJECT_ROOT, "setup.py")  # Path to setup.py
REQUIREMENTS_PATH = os.path.join(PROJECT_ROOT, "requirements.bazel.lock")  # Path to requirements file
DOC_PATH = os.path.join(PROJECT_ROOT, "doc/build")  # Path to documentation build directory

# Set up virtual environment configuration
if "VIRTUAL_ENV" in os.environ:
    # Use existing virtual environment if available
    VIRTUALENV_DIR = os.environ["VIRTUAL_ENV"]
    PYTHON_PATH = os.path.join(VIRTUALENV_DIR, "bin", "python")
    subprocess_arguments_list = []  # No need to create virtualenv
else:
    # Create new virtual environment if none exists
    VIRTUALENV_DIR = os.path.join(SCRIPT_DIR, "distrib_virtualenv")
    PYTHON_PATH = os.path.join(VIRTUALENV_DIR, "bin", "python")
    subprocess_arguments_list = [
        ["python3", "-m", "virtualenv", VIRTUALENV_DIR],  # Command to create virtualenv
    ]

# List of commands to execute in sequence
subprocess_arguments_list += [
    [PYTHON_PATH, "-m", "pip", "install", "--upgrade", "pip==19.3.1"],  # Upgrade pip
    [PYTHON_PATH, "-m", "pip", "install", "-r", REQUIREMENTS_PATH],  # Install requirements
    [PYTHON_PATH, "-m", "pip", "install", "--upgrade", "Sphinx"],  # Install/upgrade Sphinx
    [PYTHON_PATH, SETUP_PATH, "doc"],  # Build documentation
]

# Execute all commands in sequence
for subprocess_arguments in subprocess_arguments_list:
    print("Running command: {}".format(subprocess_arguments))
    subprocess.check_call(args=subprocess_arguments)

# Handle documentation publishing
if not args.repo_owner or not args.doc_branch:
    # If no repo owner or branch specified, just show where docs were generated
    tty_width = int(os.popen("stty size", "r").read().split()[1])  # Get terminal width
    print("-" * tty_width)  # Print horizontal line
    print("Please check generated Python doc inside doc/build")
    print(
        "To push to a GitHub repo, please provide repo owner and doc branch"
        " name"
    )
else:
    # If repo owner and branch specified, publish docs to GitHub
    repo_parent_dir = tempfile.mkdtemp()  # Create temp directory
    print("Documentation parent directory: {}".format(repo_parent_dir))
    repo_dir = os.path.join(repo_parent_dir, "grpc")  # Repository directory
    python_doc_dir = os.path.join(repo_dir, "python")  # Python docs directory
    doc_branch = args.doc_branch  # Documentation branch name

    # Clone and prepare GitHub repository
    print("Cloning your repository...")
    subprocess.check_call(
        [
            "git",
            "clone",
            "--branch",
            "gh-pages",  # GitHub pages branch
            "https://github.com/grpc/grpc",
        ],
        cwd=repo_parent_dir,
    )
    subprocess.check_call(["git", "checkout", "-b", doc_branch], cwd=repo_dir)  # Create new branch
    subprocess.check_call(
        [
            "git",
            "remote",
            "add",
            "ssh-origin",
            "git@github.com:%s/grpc.git" % args.repo_owner,  # Add SSH remote
        ],
        cwd=repo_dir,
    )
    
    # Update documentation
    print("Updating documentation...")
    shutil.rmtree(python_doc_dir, ignore_errors=True)  # Remove old docs
    shutil.copytree(DOC_PATH, python_doc_dir)  # Copy new docs
    
    # Push changes to GitHub
    print(
        "Attempting to push documentation to %s/%s..."
        % (args.repo_owner, doc_branch)
    )
    try:
        subprocess.check_call(["git", "add", "--all"], cwd=repo_dir)  # Stage all changes
        subprocess.check_call(
            ["git", "commit", "-m", "Auto-update Python documentation"],
            cwd=repo_dir,
        )
        subprocess.check_call(
            ["git", "push", "--set-upstream", "ssh-origin", doc_branch],
            cwd=repo_dir,
        )
    except subprocess.CalledProcessError:
        # Handle push failure
        print(
            "Failed to push documentation. Examine this directory and push "
            "manually: {}".format(repo_parent_dir)
        )
        sys.exit(1)  # Exit with error code
    
    # Clean up temporary directory
    shutil.rmtree(repo_parent_dir)
```
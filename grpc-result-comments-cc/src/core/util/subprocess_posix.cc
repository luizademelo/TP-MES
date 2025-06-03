Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#ifdef GPR_POSIX_SUBPROCESS

#include <errno.h>
#include <grpc/support/alloc.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/substitute.h"
#include "src/core/util/memory.h"
#include "src/core/util/strerror.h"
#include "src/core/util/subprocess.h"

// Structure representing a subprocess
struct gpr_subprocess {
  int pid;            // Process ID of the child process
  bool joined;        // Flag indicating if process has been joined
  int child_stdin_;   // File descriptor for child's stdin
  int child_stdout_;  // File descriptor for child's stdout
};

// Returns empty string as binary extension (POSIX systems typically don't use extensions)
const char* gpr_subprocess_binary_extension() { return ""; }

// Creates a new subprocess with given arguments
// argc: Number of arguments
// argv: Array of argument strings
// Returns: Pointer to gpr_subprocess or nullptr on failure
gpr_subprocess* gpr_subprocess_create(int argc, const char** argv) {
  gpr_subprocess* r;
  int pid;
  char** exec_args;
  
  // Fork the current process
  pid = fork();
  if (pid == -1) {
    return nullptr;  // Fork failed
  } else if (pid == 0) {
    // Child process
    // Prepare arguments for execv
    exec_args = static_cast<char**>(
        gpr_malloc((static_cast<size_t>(argc) + 1) * sizeof(char*)));
    memcpy(exec_args, argv, static_cast<size_t>(argc) * sizeof(char*));
    exec_args[argc] = nullptr;  // Null-terminate the argument list
    
    // Replace current process with new program
    execv(exec_args[0], exec_args);

    // If we get here, execv failed
    LOG(ERROR) << "execv '" << exec_args[0]
               << "' failed: " << grpc_core::StrError(errno);
    _exit(1);  // Exit child process with error
  } else {
    // Parent process
    r = grpc_core::Zalloc<gpr_subprocess>();
    r->pid = pid;
    r->child_stdin_ = -1;   // No stdin pipe by default
    r->child_stdout_ = -1;  // No stdout pipe by default
    return r;
  }
}

// Creates a new subprocess with given arguments and environment variables
// argc: Number of arguments
// argv: Array of argument strings
// envc: Number of environment variables
// envp: Array of environment variable strings
// Returns: Pointer to gpr_subprocess or nullptr on failure
gpr_subprocess* gpr_subprocess_create_with_envp(int argc, const char** argv,
                                                int envc, const char** envp) {
  gpr_subprocess* r;
  int pid;
  char **exec_args, **envp_args;
  int stdin_pipe[2];   // Pipe for child's stdin
  int stdout_pipe[2];  // Pipe for child's stdout
  
  // Create pipes for stdin and stdout
  int p0 = pipe(stdin_pipe);
  int p1 = pipe(stdout_pipe);
  CHECK_NE(p0, -1);  // Ensure pipe creation succeeded
  CHECK_NE(p1, -1);
  
  pid = fork();
  if (pid == -1) {
    return nullptr;  // Fork failed
  } else if (pid == 0) {
    // Child process
    // Redirect stdin/stdout to pipes
    dup2(stdin_pipe[0], STDIN_FILENO);
    dup2(stdout_pipe[1], STDOUT_FILENO);
    
    // Close unused pipe ends
    close(stdin_pipe[0]);
    close(stdin_pipe[1]);
    close(stdout_pipe[0]);
    close(stdout_pipe[1]);
    
    // Prepare arguments and environment for execve
    exec_args = static_cast<char**>(
        gpr_malloc((static_cast<size_t>(argc) + 1) * sizeof(char*)));
    memcpy(exec_args, argv, static_cast<size_t>(argc) * sizeof(char*));
    exec_args[argc] = nullptr;
    
    envp_args = static_cast<char**>(
        gpr_malloc((static_cast<size_t>(envc) + 1) * sizeof(char*)));
    memcpy(envp_args, envp, static_cast<size_t>(envc) * sizeof(char*));
    envp_args[envc] = nullptr;
    
    // Replace current process with new program
    execve(exec_args[0], exec_args, envp_args);

    // If we get here, execve failed
    LOG(ERROR) << "execvpe '" << exec_args[0]
               << "' failed: " << grpc_core::StrError(errno);
    _exit(1);  // Exit child process with error
  } else {
    // Parent process
    r = grpc_core::Zalloc<gpr_subprocess>();
    r->pid = pid;
    // Close unused pipe ends in parent
    close(stdin_pipe[0]);
    close(stdout_pipe[1]);
    // Store pipe ends for communication
    r->child_stdin_ = stdin_pipe[1];
    r->child_stdout_ = stdout_pipe[0];
    return r;
  }
}

// Communicates with a subprocess
// p: Subprocess handle
// input_data: Data to send to subprocess stdin
// output_data: Buffer to receive subprocess stdout
// error: Buffer to receive error message if any
// Returns: true if communication succeeded, false otherwise
bool gpr_subprocess_communicate(gpr_subprocess* p, std::string& input_data,
                                std::string* output_data, std::string* error) {
  typedef void SignalHandler(int);

  // Ignore SIGPIPE to handle broken pipes gracefully
  SignalHandler* old_pipe_handler = signal(SIGPIPE, SIG_IGN);

  int input_pos = 0;
  int max_fd = std::max(p->child_stdin_, p->child_stdout_);

  // Main communication loop
  while (p->child_stdout_ != -1) {
    fd_set read_fds;
    fd_set write_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
    
    // Set up file descriptors for select
    if (p->child_stdout_ != -1) {
      FD_SET(p->child_stdout_, &read_fds);
    }
    if (p->child_stdin_ != -1) {
      FD_SET(p->child_stdin_, &write_fds);
    }

    // Wait for I/O events
    if (select(max_fd + 1, &read_fds, &write_fds, nullptr, nullptr) < 0) {
      if (errno == EINTR) {
        // Interrupted by signal, try again
        continue;
      } else {
        std::cerr << "select: " << strerror(errno) << std::endl;
        CHECK(0);  // Fatal error
      }
    }

    // Handle writable stdin
    if (p->child_stdin_ != -1 && FD_ISSET(p->child_stdin_, &write_fds)) {
      int n = write(p->child_stdin_, input_data.data() + input_pos,
                    input_data.size() - input_pos);
      if (n < 0) {
        // Write error, consider input complete
        input_pos = input_data.size();
      } else {
        input_pos += n;
      }

      // If all input sent, close stdin
      if (input_pos == static_cast<int>(input_data.size())) {
        close(p->child_stdin_);
        p->child_stdin_ = -1;
      }
    }

    // Handle readable stdout
    if (p->child_stdout_ != -1 && FD_ISSET(p->child_stdout_, &read_fds)) {
      char buffer[4096];
      int n = read(p->child_stdout_, buffer, sizeof(buffer));

      if (n > 0) {
        output_data->append(buffer, static_cast<size_t>(n));
      } else {
        // EOF or error, close stdout
        close(p->child_stdout_);
        p->child_stdout_ = -1;
      }
    }
  }

  // Ensure stdin is closed if not already
  if (p->child_stdin_ != -1) {
    close(p->child_stdin_);
    p->child_stdin_ = -1;
  }

  // Wait for child process to exit
  int status;
  while (waitpid(p->pid, &status, 0) == -1) {
    if (errno != EINTR) {
      std::cerr << "waitpid: " << strerror(errno) << std::endl;
      CHECK(0);  // Fatal error
    }
  }

  // Restore original SIGPIPE handler
  signal(SIGPIPE, old_pipe_handler);

  // Check child process exit status
  if (WIFEXITED(status)) {
    if (WEXITSTATUS(status) != 0) {
      int error_code = WEXITSTATUS(status);
      *error =
          absl::Substitute("Plugin failed with status code $0.", error_code);
      return false;
    }
  } else if (WIFSIGNALED(status)) {
    int signal = WTERMSIG(status);
    *error = absl::Substitute("Plugin killed by signal $0.", signal);
    return false;
  } else {
    *error = "Neither WEXITSTATUS nor WTERMSIG is true?";
    return false;
  }

  return true;
}

// Destroys a subprocess handle
// p: Subprocess handle to destroy
void gpr_subprocess_destroy(gpr_subprocess* p) {
  if (!p->joined) {
    // Kill process if not already joined
    kill(p->pid, SIGKILL);
    gpr_subprocess_join(p);
  }
  gpr_free(p);
}

// Waits for a subprocess to complete
// p: Subprocess handle
// Returns: Exit status of the process or -1 on error
int gpr_subprocess_join(gpr_subprocess* p) {
  int status;
retry:
  if (waitpid(p->pid, &status, 0) == -1) {
    if (errno == EINTR) {
      goto retry;  // Retry if interrupted by signal
    }
    LOG(ERROR) << "waitpid failed for pid " << p->pid << ": "
               << grpc_core::StrError(errno);
    return -1;
  }
  p->joined = true;  // Mark process as joined
  return status;
}

// Interrupts a subprocess by sending SIGINT
// p: Subprocess handle to interrupt
void gpr_subprocess_interrupt(gpr_subprocess* p) {
  if (!p->joined) {
    kill(p->pid, SIGINT);
  }
}

// Returns the process ID of a subprocess
// p: Subprocess handle
// Returns: Process ID
int gpr_subprocess_get_process_id(gpr_subprocess* p) { return p->pid; }

#endif
```
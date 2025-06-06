
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

struct gpr_subprocess {
  int pid;
  bool joined;
  int child_stdin_;
  int child_stdout_;
};

const char* gpr_subprocess_binary_extension() { return ""; }

gpr_subprocess* gpr_subprocess_create(int argc, const char** argv) {
  gpr_subprocess* r;
  int pid;
  char** exec_args;
  pid = fork();
  if (pid == -1) {
    return nullptr;
  } else if (pid == 0) {
    exec_args = static_cast<char**>(
        gpr_malloc((static_cast<size_t>(argc) + 1) * sizeof(char*)));
    memcpy(exec_args, argv, static_cast<size_t>(argc) * sizeof(char*));
    exec_args[argc] = nullptr;
    execv(exec_args[0], exec_args);

    LOG(ERROR) << "execv '" << exec_args[0]
               << "' failed: " << grpc_core::StrError(errno);
    _exit(1);
  } else {
    r = grpc_core::Zalloc<gpr_subprocess>();
    r->pid = pid;
    r->child_stdin_ = -1;
    r->child_stdout_ = -1;
    return r;
  }
}

gpr_subprocess* gpr_subprocess_create_with_envp(int argc, const char** argv,
                                                int envc, const char** envp) {
  gpr_subprocess* r;
  int pid;
  char **exec_args, **envp_args;
  int stdin_pipe[2];
  int stdout_pipe[2];
  int p0 = pipe(stdin_pipe);
  int p1 = pipe(stdout_pipe);
  CHECK_NE(p0, -1);
  CHECK_NE(p1, -1);
  pid = fork();
  if (pid == -1) {
    return nullptr;
  } else if (pid == 0) {
    dup2(stdin_pipe[0], STDIN_FILENO);
    dup2(stdout_pipe[1], STDOUT_FILENO);
    close(stdin_pipe[0]);
    close(stdin_pipe[1]);
    close(stdout_pipe[0]);
    close(stdout_pipe[1]);
    exec_args = static_cast<char**>(
        gpr_malloc((static_cast<size_t>(argc) + 1) * sizeof(char*)));
    memcpy(exec_args, argv, static_cast<size_t>(argc) * sizeof(char*));
    exec_args[argc] = nullptr;
    envp_args = static_cast<char**>(
        gpr_malloc((static_cast<size_t>(envc) + 1) * sizeof(char*)));
    memcpy(envp_args, envp, static_cast<size_t>(envc) * sizeof(char*));
    envp_args[envc] = nullptr;
    execve(exec_args[0], exec_args, envp_args);

    LOG(ERROR) << "execvpe '" << exec_args[0]
               << "' failed: " << grpc_core::StrError(errno);
    _exit(1);
  } else {
    r = grpc_core::Zalloc<gpr_subprocess>();
    r->pid = pid;
    close(stdin_pipe[0]);
    close(stdout_pipe[1]);
    r->child_stdin_ = stdin_pipe[1];
    r->child_stdout_ = stdout_pipe[0];
    return r;
  }
}

bool gpr_subprocess_communicate(gpr_subprocess* p, std::string& input_data,
                                std::string* output_data, std::string* error) {
  typedef void SignalHandler(int);

  SignalHandler* old_pipe_handler = signal(SIGPIPE, SIG_IGN);

  int input_pos = 0;
  int max_fd = std::max(p->child_stdin_, p->child_stdout_);

  while (p->child_stdout_ != -1) {
    fd_set read_fds;
    fd_set write_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
    if (p->child_stdout_ != -1) {
      FD_SET(p->child_stdout_, &read_fds);
    }
    if (p->child_stdin_ != -1) {
      FD_SET(p->child_stdin_, &write_fds);
    }

    if (select(max_fd + 1, &read_fds, &write_fds, nullptr, nullptr) < 0) {
      if (errno == EINTR) {

        continue;
      } else {
        std::cerr << "select: " << strerror(errno) << std::endl;
        CHECK(0);
      }
    }

    if (p->child_stdin_ != -1 && FD_ISSET(p->child_stdin_, &write_fds)) {
      int n = write(p->child_stdin_, input_data.data() + input_pos,
                    input_data.size() - input_pos);
      if (n < 0) {

        input_pos = input_data.size();
      } else {
        input_pos += n;
      }

      if (input_pos == static_cast<int>(input_data.size())) {

        close(p->child_stdin_);
        p->child_stdin_ = -1;
      }
    }

    if (p->child_stdout_ != -1 && FD_ISSET(p->child_stdout_, &read_fds)) {
      char buffer[4096];
      int n = read(p->child_stdout_, buffer, sizeof(buffer));

      if (n > 0) {
        output_data->append(buffer, static_cast<size_t>(n));
      } else {

        close(p->child_stdout_);
        p->child_stdout_ = -1;
      }
    }
  }

  if (p->child_stdin_ != -1) {

    close(p->child_stdin_);
    p->child_stdin_ = -1;
  }

  int status;
  while (waitpid(p->pid, &status, 0) == -1) {
    if (errno != EINTR) {
      std::cerr << "waitpid: " << strerror(errno) << std::endl;
      CHECK(0);
    }
  }

  signal(SIGPIPE, old_pipe_handler);

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

void gpr_subprocess_destroy(gpr_subprocess* p) {
  if (!p->joined) {
    kill(p->pid, SIGKILL);
    gpr_subprocess_join(p);
  }
  gpr_free(p);
}

int gpr_subprocess_join(gpr_subprocess* p) {
  int status;
retry:
  if (waitpid(p->pid, &status, 0) == -1) {
    if (errno == EINTR) {
      goto retry;
    }
    LOG(ERROR) << "waitpid failed for pid " << p->pid << ": "
               << grpc_core::StrError(errno);
    return -1;
  }
  p->joined = true;
  return status;
}

void gpr_subprocess_interrupt(gpr_subprocess* p) {
  if (!p->joined) {
    kill(p->pid, SIGINT);
  }
}

int gpr_subprocess_get_process_id(gpr_subprocess* p) { return p->pid; }

#endif

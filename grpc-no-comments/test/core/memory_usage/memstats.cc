// Copyright 2022 gRPC authors.

#include "test/core/memory_usage/memstats.h"

#include <unistd.h>

#include <fstream>
#include <string>

#include "absl/log/check.h"
#include "absl/strings/str_cat.h"

long GetMemUsage(std::optional<int> pid) {

  std::string path = "/proc/self/stat";
  if (pid != std::nullopt) {
    path = absl::StrCat("/proc/", pid.value(), "/stat");
  }
  std::ifstream stat_stream(path, std::ios_base::in);

  double resident_set = 0.0;

  std::string temp_pid, comm, state, ppid, pgrp, session, tty_nr;
  std::string tpgid, flags, minflt, cminflt, majflt, cmajflt;
  std::string utime, stime, cutime, cstime, priority, nice;
  std::string O, itrealvalue, starttime, vsize;

  long rss;
  stat_stream >> temp_pid >> comm >> state >> ppid >> pgrp >> session >>
      tty_nr >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt >>
      utime >> stime >> cutime >> cstime >> priority >> nice >> O >>
      itrealvalue >> starttime >> vsize >> rss;
  stat_stream.close();

  CHECK(!state.empty());

  long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024;
  resident_set = rss * page_size_kb;

  return resident_set;
}

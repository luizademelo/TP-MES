#!/usr/bin/env python3
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Run test matrix."""

from __future__ import print_function

import argparse
import multiprocessing
import os
import sys

from python_utils.filter_pull_request_tests import filter_tests
import python_utils.jobset as jobset
import python_utils.report_utils as report_utils

_ROOT = os.path.abspath(os.path.join(os.path.dirname(sys.argv[0]), "../.."))
os.chdir(_ROOT)

_DEFAULT_RUNTESTS_TIMEOUT = 1 * 60 * 60

_CPP_RUNTESTS_TIMEOUT = 6 * 60 * 60

_OBJC_RUNTESTS_TIMEOUT = 4 * 60 * 60

_PYTHON_WINDOWS_RUNTESTS_TIMEOUT = 1.5 * 60 * 60

_RUBY_RUNTESTS_TIMEOUT = 2 * 60 * 60

_DEFAULT_INNER_JOBS = 2

_MATRIX_REPORT_NAME = "toplevel_run_tests_invocations"

def _safe_report_name(name):
    """Reports with '+' in target name won't show correctly in ResultStore"""
    return name.replace("+", "p")

def _report_filename(name):
    """Generates report file name with directory structure that leads to better presentation by internal CI"""

    return "%s/%s" % (_safe_report_name(name), "sponge_log.xml")

def _matrix_job_logfilename(shortname_for_multi_target):
    """Generate location for log file that will match the sponge_log.xml from the top-level matrix report."""

    sponge_log_name = "%s/%s/%s" % (
        _MATRIX_REPORT_NAME,
        shortname_for_multi_target,
        "sponge_log.log",
    )

    base_dir = os.getenv("GRPC_TEST_REPORT_BASE_DIR", None)
    if base_dir:
        sponge_log_name = os.path.join(base_dir, sponge_log_name)
    return sponge_log_name

def _docker_jobspec(
    name,
    runtests_args=[],
    runtests_envs={},
    inner_jobs=_DEFAULT_INNER_JOBS,
    timeout_seconds=None,
):
    """Run a single instance of run_tests.py in a docker container"""
    if not timeout_seconds:
        timeout_seconds = _DEFAULT_RUNTESTS_TIMEOUT
    shortname = "run_tests_%s" % name
    test_job = jobset.JobSpec(
        cmdline=[
            "python3",
            "tools/run_tests/run_tests.py",
            "--use_docker",
            "-t",
            "-j",
            str(inner_jobs),
            "-x",
            "run_tests/%s" % _report_filename(name),
            "--report_suite_name",
            "%s" % _safe_report_name(name),
        ]
        + runtests_args,
        environ=runtests_envs,
        shortname=shortname,
        timeout_seconds=timeout_seconds,
        logfilename=_matrix_job_logfilename(shortname),
    )
    return test_job

def _workspace_jobspec(
    name,
    runtests_args=[],
    workspace_name=None,
    runtests_envs={},
    inner_jobs=_DEFAULT_INNER_JOBS,
    timeout_seconds=None,
):
    """Run a single instance of run_tests.py in a separate workspace"""
    if not workspace_name:
        workspace_name = "workspace_%s" % name
    if not timeout_seconds:
        timeout_seconds = _DEFAULT_RUNTESTS_TIMEOUT
    shortname = "run_tests_%s" % name
    env = {"WORKSPACE_NAME": workspace_name}
    env.update(runtests_envs)

    report_dir_prefix = (
        "" if os.getenv("GRPC_TEST_REPORT_BASE_DIR", None) else "../"
    )
    test_job = jobset.JobSpec(
        cmdline=[
            "bash",
            "tools/run_tests/helper_scripts/run_tests_in_workspace.sh",
            "-t",
            "-j",
            str(inner_jobs),
            "-x",
            "%srun_tests/%s" % (report_dir_prefix, _report_filename(name)),
            "--report_suite_name",
            "%s" % _safe_report_name(name),
        ]
        + runtests_args,
        environ=env,
        shortname=shortname,
        timeout_seconds=timeout_seconds,
        logfilename=_matrix_job_logfilename(shortname),
    )
    return test_job

def _generate_jobs(
    languages,
    configs,
    platforms,
    iomgr_platforms=["native"],
    arch=None,
    compiler=None,
    labels=[],
    extra_args=[],
    extra_envs={},
    inner_jobs=_DEFAULT_INNER_JOBS,
    timeout_seconds=None,
):
    result = []
    for language in languages:
        for platform in platforms:
            for iomgr_platform in iomgr_platforms:
                for config in configs:
                    name = "%s_%s_%s_%s" % (
                        language,
                        platform,
                        config,
                        iomgr_platform,
                    )
                    runtests_args = [
                        "-l",
                        language,
                        "-c",
                        config,
                        "--iomgr_platform",
                        iomgr_platform,
                    ]
                    if arch or compiler:
                        name += "_%s_%s" % (arch, compiler)
                        runtests_args += [
                            "--arch",
                            arch,
                            "--compiler",
                            compiler,
                        ]
                    if "--build_only" in extra_args:
                        name += "_buildonly"
                    for extra_env in extra_envs:
                        name += "_%s_%s" % (extra_env, extra_envs[extra_env])

                    runtests_args += extra_args
                    if platform == "linux":
                        job = _docker_jobspec(
                            name=name,
                            runtests_args=runtests_args,
                            runtests_envs=extra_envs,
                            inner_jobs=inner_jobs,
                            timeout_seconds=timeout_seconds,
                        )
                    else:
                        if platform == "windows" and language == "python":
                            timeout_seconds = _PYTHON_WINDOWS_RUNTESTS_TIMEOUT

                        job = _workspace_jobspec(
                            name=name,
                            runtests_args=runtests_args,
                            runtests_envs=extra_envs,
                            inner_jobs=inner_jobs,
                            timeout_seconds=timeout_seconds,
                        )

                    job.labels = [
                        platform,
                        config,
                        language,
                        iomgr_platform,
                    ] + labels
                    result.append(job)
    return result

def _create_test_jobs(extra_args=[], inner_jobs=_DEFAULT_INNER_JOBS):
    test_jobs = []

    test_jobs += _generate_jobs(
        languages=["sanity", "clang-tidy"],
        configs=["dbg"],
        platforms=["linux"],
        labels=["basictests"],
        extra_args=extra_args + ["--report_multi_target"],
        inner_jobs=inner_jobs,
    )

    test_jobs += _generate_jobs(
        languages=["c"],
        configs=["dbg", "opt"],
        platforms=["linux", "macos", "windows"],
        labels=["basictests", "corelang"],
        extra_args=extra_args,
        inner_jobs=inner_jobs,
        timeout_seconds=_CPP_RUNTESTS_TIMEOUT,
    )

    test_jobs += _generate_jobs(
        languages=["csharp"],
        configs=["dbg", "opt"],
        platforms=["linux", "macos", "windows"],
        labels=["basictests", "multilang"],
        extra_args=extra_args + ["--report_multi_target"],
        inner_jobs=inner_jobs,
    )

    test_jobs += _generate_jobs(
        languages=["csharp"],
        configs=["dbg", "opt"],
        platforms=["linux"],
        arch="arm64",
        compiler="default",
        labels=["basictests_arm64"],
        extra_args=extra_args + ["--report_multi_target"],
        inner_jobs=inner_jobs,
    )

    test_jobs += _generate_jobs(
        languages=["python"],
        configs=["opt"],
        platforms=["linux", "macos", "windows"],
        iomgr_platforms=["native"],
        labels=["basictests", "multilang"],
        extra_args=extra_args + ["--report_multi_target"],
        inner_jobs=inner_jobs,
    )

    test_jobs += _generate_jobs(
        languages=["python"],
        configs=["opt"],
        platforms=["linux"],
        arch="arm64",
        compiler="default",
        iomgr_platforms=["native"],
        labels=["basictests_arm64"],
        extra_args=extra_args + ["--report_multi_target"],
        inner_jobs=inner_jobs,
    )

    test_jobs += _generate_jobs(
        languages=["c++"],
        configs=["dbg", "opt"],
        platforms=["linux", "macos"],
        labels=["basictests", "corelang"],
        extra_args=extra_args,
        inner_jobs=inner_jobs,
        timeout_seconds=_CPP_RUNTESTS_TIMEOUT,
    )

    test_jobs += _generate_jobs(
        languages=["ruby", "php8"],
        configs=["dbg", "opt"],
        platforms=["linux", "macos"],
        labels=["basictests", "multilang"],
        extra_args=extra_args + ["--report_multi_target"],
        inner_jobs=inner_jobs,
        timeout_seconds=_RUBY_RUNTESTS_TIMEOUT,
    )

    test_jobs += _generate_jobs(
        languages=["ruby", "php8"],
        configs=["dbg", "opt"],
        platforms=["linux"],
        arch="arm64",
        compiler="default",
        labels=["basictests_arm64"],
        extra_args=extra_args + ["--report_multi_target"],
        inner_jobs=inner_jobs,
    )

    test_jobs += _generate_jobs(
        languages=["objc"],
        configs=["opt"],
        platforms=["macos"],
        labels=["basictests", "multilang"],
        extra_args=extra_args + ["--report_multi_target"],
        inner_jobs=inner_jobs,
        timeout_seconds=_OBJC_RUNTESTS_TIMEOUT,
    )

    return test_jobs

def _create_portability_test_jobs(
    extra_args=[], inner_jobs=_DEFAULT_INNER_JOBS
):
    test_jobs = []

    test_jobs += _generate_jobs(
        languages=["c"],
        configs=["dbg"],
        platforms=["linux"],
        arch="x86",
        compiler="default",
        labels=["portability", "corelang"],
        extra_args=extra_args,
        inner_jobs=inner_jobs,
    )

    for compiler in [
        "gcc8",

        "gcc10.2_openssl102",
        "gcc10.2_openssl111",
        "gcc12_openssl309",
        "gcc14",
        "gcc_musl",
        "clang11",
        "clang19",
    ]:
        test_jobs += _generate_jobs(
            languages=["c", "c++"],
            configs=["dbg"],
            platforms=["linux"],
            arch="x64",
            compiler=compiler,
            labels=["portability", "corelang"]
            + (["openssl"] if "openssl" in compiler else []),
            extra_args=extra_args,
            inner_jobs=inner_jobs,
            timeout_seconds=_CPP_RUNTESTS_TIMEOUT,
        )

    test_jobs += _generate_jobs(
        languages=["c", "c++"],
        configs=["dbg"],
        platforms=["windows"],
        arch="default",
        compiler="cmake_ninja_vs2022",
        labels=["portability", "corelang"],
        extra_args=extra_args,
        inner_jobs=inner_jobs,
        timeout_seconds=_CPP_RUNTESTS_TIMEOUT,
    )

    test_jobs += _generate_jobs(
        languages=["c", "c++"],
        configs=["noexcept"],
        platforms=["linux"],
        labels=["portability", "corelang"],
        extra_args=extra_args,
        inner_jobs=inner_jobs,
        timeout_seconds=_CPP_RUNTESTS_TIMEOUT,
    )

    test_jobs += _generate_jobs(
        languages=["python"],
        configs=["dbg"],
        platforms=["linux"],
        arch="default",
        compiler="python_alpine",
        labels=["portability", "multilang"],
        extra_args=extra_args + ["--report_multi_target"],
        inner_jobs=inner_jobs,
    )

    return test_jobs

def _allowed_labels():
    """Returns a list of existing job labels."""
    all_labels = set()
    for job in _create_test_jobs() + _create_portability_test_jobs():
        for label in job.labels:
            all_labels.add(label)
    return sorted(all_labels)

def _runs_per_test_type(arg_str):
    """Auxiliary function to parse the "runs_per_test" flag."""
    try:
        n = int(arg_str)
        if n <= 0:
            raise ValueError
        return n
    except:
        msg = "'{}' is not a positive integer".format(arg_str)
        raise argparse.ArgumentTypeError(msg)

if __name__ == "__main__":
    argp = argparse.ArgumentParser(
        description="Run a matrix of run_tests.py tests."
    )
    argp.add_argument(
        "-j",
        "--jobs",
        default=multiprocessing.cpu_count() / _DEFAULT_INNER_JOBS,
        type=int,
        help="Number of concurrent run_tests.py instances.",
    )
    argp.add_argument(
        "-f",
        "--filter",
        choices=_allowed_labels(),
        nargs="+",
        default=[],
        help="Filter targets to run by label with AND semantics.",
    )
    argp.add_argument(
        "--exclude",
        choices=_allowed_labels(),
        nargs="+",
        default=[],
        help="Exclude targets with any of given labels.",
    )
    argp.add_argument(
        "--build_only",
        default=False,
        action="store_const",
        const=True,
        help="Pass --build_only flag to run_tests.py instances.",
    )
    argp.add_argument(
        "--force_default_poller",
        default=False,
        action="store_const",
        const=True,
        help="Pass --force_default_poller to run_tests.py instances.",
    )
    argp.add_argument(
        "--dry_run",
        default=False,
        action="store_const",
        const=True,
        help="Only print what would be run.",
    )
    argp.add_argument(
        "--filter_pr_tests",
        default=False,
        action="store_const",
        const=True,
        help="Filters out tests irrelevant to pull request changes.",
    )
    argp.add_argument(
        "--base_branch",
        default="origin/master",
        type=str,
        help="Branch that pull request is requesting to merge into",
    )
    argp.add_argument(
        "--inner_jobs",
        default=_DEFAULT_INNER_JOBS,
        type=int,
        help="Number of jobs in each run_tests.py instance",
    )
    argp.add_argument(
        "-n",
        "--runs_per_test",
        default=1,
        type=_runs_per_test_type,
        help="How many times to run each tests. >1 runs implies "
        + "omitting passing test from the output & reports.",
    )
    argp.add_argument(
        "--max_time",
        default=-1,
        type=int,
        help="Maximum amount of time to run tests for"
        + "(other tests will be skipped)",
    )
    argp.add_argument(
        "--bq_result_table",
        default="",
        type=str,
        nargs="?",
        help="Upload test results to a specified BQ table.",
    )
    argp.add_argument(
        "--extra_args",
        default="",
        type=str,
        nargs=argparse.REMAINDER,
        help="Extra test args passed to each sub-script.",
    )
    args = argp.parse_args()

    extra_args = []
    if args.build_only:
        extra_args.append("--build_only")
    if args.force_default_poller:
        extra_args.append("--force_default_poller")
    if args.runs_per_test > 1:
        extra_args.append("-n")
        extra_args.append("%s" % args.runs_per_test)
        extra_args.append("--quiet_success")
    if args.max_time > 0:
        extra_args.extend(("--max_time", "%d" % args.max_time))
    if args.bq_result_table:
        extra_args.append("--bq_result_table")
        extra_args.append("%s" % args.bq_result_table)
        extra_args.append("--measure_cpu_costs")
    if args.extra_args:
        extra_args.extend(args.extra_args)

    all_jobs = _create_test_jobs(
        extra_args=extra_args, inner_jobs=args.inner_jobs
    ) + _create_portability_test_jobs(
        extra_args=extra_args, inner_jobs=args.inner_jobs
    )

    jobs = []
    for job in all_jobs:
        if not args.filter or all(
            filter in job.labels for filter in args.filter
        ):
            if not any(
                exclude_label in job.labels for exclude_label in args.exclude
            ):
                jobs.append(job)

    if not jobs:
        jobset.message(
            "FAILED", "No test suites match given criteria.", do_newline=True
        )
        sys.exit(1)

    print("IMPORTANT: The changes you are testing need to be locally committed")
    print("because only the committed changes in the current branch will be")
    print("copied to the docker environment or into subworkspaces.")

    skipped_jobs = []

    if args.filter_pr_tests:
        print("Looking for irrelevant tests to skip...")
        relevant_jobs = filter_tests(jobs, args.base_branch)
        if len(relevant_jobs) == len(jobs):
            print("No tests will be skipped.")
        else:
            print("These tests will be skipped:")
            skipped_jobs = list(set(jobs) - set(relevant_jobs))

            skipped_jobs.sort(key=lambda job: job.shortname)
            for job in list(skipped_jobs):
                print("  %s" % job.shortname)
        jobs = relevant_jobs

    print("Will run these tests:")
    for job in jobs:
        print('  %s: "%s"' % (job.shortname, " ".join(job.cmdline)))
    print("")

    if args.dry_run:
        print("--dry_run was used, exiting")
        sys.exit(1)

    jobset.message("START", "Running test matrix.", do_newline=True)
    num_failures, resultset = jobset.run(
        jobs, newline_on_success=True, travis=True, maxjobs=args.jobs
    )

    if skipped_jobs:
        ignored_num_skipped_failures, skipped_results = jobset.run(
            skipped_jobs, skip_jobs=True
        )
        resultset.update(skipped_results)
    report_utils.render_junit_xml_report(
        resultset,
        _report_filename(_MATRIX_REPORT_NAME),
        suite_name=_MATRIX_REPORT_NAME,
        multi_target=True,
    )

    if num_failures == 0:
        jobset.message(
            "SUCCESS",
            "All run_tests.py instances finished successfully.",
            do_newline=True,
        )
    else:
        jobset.message(
            "FAILED",
            "Some run_tests.py instances have failed.",
            do_newline=True,
        )
        sys.exit(1)

Here's the commented version of the code:

```c++
# Copyright 2022 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

QUERY = """
#standardSQL

-- This SQL query analyzes test results from gRPC's RBE (Remote Build Execution) tests
-- Original query can be found at: https://console.cloud.google.com/bigquery?sq=830293263384:5a8549832dfb48d9b2c04312a4ae3181

WITH
  -- First CTE (Common Table Expression) cleans and processes raw test data
  runs AS (
  SELECT
    -- Clean test binary name by removing poller information
    RTRIM(LTRIM(REGEXP_REPLACE(test_target, r'(@poller=.+)', ''))) AS test_binary,
    -- Extract poll strategy if present in test target
    REGEXP_EXTRACT(test_target, r'poller=(\w+)') AS poll_strategy,
    job_name,
    test_target,
    test_class_name,
    -- Normalize test case names for failed tests (timeouts, retries, segfaults)
    CASE
      # Handle sharded test cases that failed with special patterns
      WHEN test_case like 'test_shard_%_run%_attempt%' THEN 'CANNOT_DETERMINE'
      WHEN test_case like '%shard_%/%' THEN 'CANNOT_DETERMINE'
      # Handle cases where test_case looks suspiciously like test_target
      WHEN STRPOS(test_case, REPLACE(SUBSTR(test_target, 3), ":", "/")) != 0 THEN 'CANNOT_DETERMINE'
      ELSE test_case
    END AS test_case,
    result,
    build_id,
    timestamp
  FROM
    `grpc-testing.jenkins_test_results.rbe_test_results`
  WHERE
    -- Only consider tests from the last {lookback_hours} hours
    DATETIME_DIFF(CURRENT_DATETIME(),
      dateTIME(timestamp),
      HOUR) < {lookback_hours}
    ),

  -- Aggregate test results by build, counting failures and total runs
  results_counts_per_build AS (
  SELECT
    test_binary,
    test_class_name,
    test_case,
    -- Count failed runs (excluding SKIPPED results)
    SUM(SAFE_CAST(result != 'PASSED'
        AND result != 'SKIPPED' AS INT64)) AS runs_failed,
    -- Count total runs (excluding SKIPPED results)
    SUM(SAFE_CAST(result != 'SKIPPED' AS INT64)) AS runs_total,
    job_name,
    build_id
  FROM
    runs
  GROUP BY
    test_binary,
    test_class_name,
    test_case,
    job_name,
    build_id),

  -- Identify builds that don't have any 'CANNOT_DETERMINE' test cases
  builds_with_missing_cannot_determine_testcase_entry AS (
    SELECT
      test_binary,
      job_name,
      build_id,
    FROM
      results_counts_per_build
    GROUP BY
      test_binary,
      job_name,
      build_id
    HAVING COUNTIF(test_case = 'CANNOT_DETERMINE') = 0
  ),

  -- Add synthetic 'CANNOT_DETERMINE' entries for builds that don't have them
  -- This ensures consistent statistics across all builds
  results_counts_per_build_with_fake_cannot_determine_test_case_entries AS (
    (SELECT * FROM results_counts_per_build)
    UNION ALL
    (SELECT
      test_binary,
      '' AS test_class_name,  -- Empty class name for synthetic entries
      'CANNOT_DETERMINE' AS test_case,  -- Special case for indeterminate failures
      0 AS runs_failed,      -- Initialize with no failures
      1 AS runs_total,       -- Initialize with one run
      job_name,
      build_id
    FROM
      builds_with_missing_cannot_determine_testcase_entry)
  ),

  -- Final aggregation of results across all builds
  results_counts AS (
  SELECT
    test_binary,
    test_class_name,
    test_case,
    job_name,
    SUM(runs_failed) AS runs_failed,
    SUM(runs_total) AS runs_total,
    -- Count how many builds had at least one failure
    SUM(SAFE_CAST(runs_failed > 0 AS INT64)) AS builds_failed,
    COUNT(build_id) AS builds_total,
    -- Create a visual pattern of build failures (X=failed, _=passed)
    STRING_AGG(CASE
        WHEN runs_failed > 0 THEN 'X'
        ELSE '_' END, ''
    ORDER BY
      build_id ASC) AS build_failure_pattern,
    -- Aggregate all build IDs for reference
    FORMAT("%T", ARRAY_AGG(build_id
      ORDER BY
        build_id ASC)) AS builds
  FROM
    results_counts_per_build_with_fake_cannot_determine_test_case_entries
  GROUP BY
    test_binary,
    test_class_name,
    test_case,
    job_name
  HAVING
    -- Only include tests that had at least one failure
    runs_failed > 0)

-- Final output with calculated percentages and relevant fields
SELECT
  -- Percentage of builds where this test failed
  ROUND(100*builds_failed / builds_total, 2) AS pct_builds_failed,
  -- Percentage of test runs that failed
  ROUND(100*runs_failed / runs_total, 2) AS pct_runs_failed,
  test_binary,
  test_class_name,
  test_case,
  job_name,
  build_failure_pattern

FROM
  results_counts
-- Order by most frequently failing tests first
ORDER BY
  pct_builds_failed DESC
"""
```
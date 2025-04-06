#!/bin/bash

lcov --ignore-errors inconsistent --rc lcov_branch_coverage=1 --capture --directory ./ --output-file coverage.info
genhtml coverage.info --output-directory coverage_report --branch-coverage --title LongIntLib

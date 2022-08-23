#!/bin/zsh

## Run tests
## This script will automate running all the tests and will 
## compare the output against the expected output

# Define all the directories
TEST_DIR="./"
EXEC_DIR="../bin/"

# Define the extensions
INPUT_EXT=".in"
OUTPUT_EXT=".out"

# Defining expecutables
EXEC="verCE"

for test in $TEST_DIR/*.in; do

    # Get the name of the test
    test_name=$(basename $test)

    # Get the name of the expected output
    expected_output="${test_name%.*}.$"

    # Get the name of the actual output
    actual_output="${test_name%.*}.actual.out"

    # Run the test
    $EXEC_DIR$EXEC < $test > $actual_output

    # Compare the output
    diff $TEST_DIR$expected_output $actual_output
done
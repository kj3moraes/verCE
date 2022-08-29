#!/bin/zsh

## PRODUCE OUTPUTS SCRIPT
## This script will automate output generation for all the
## .in files in the testing directory.

## WARNING : This script MUST be run from the tests directory

# Coloured Output
RED='\033[0;31m'
GREEN='\033[0;32m'
BOLD='\033[1;97m'
RESET='\033[0m'

# Define all the directories
TEST_DIR="."
EXEC_DIR="../bin"

# Define the extensions
INPUT_EXT="in"
OUTPUT_EXT="out"

# Defining expecutables
EXEC="verCEProgram"

for test in $(ls $TEST_DIR | egrep ".in"); do

    # Get the name of the test and the temp holding file
    test_name=$(basename $test ".in")
    temp_file=$(mktemp)

    # Get the name of the input file
    input_file="${test_name%.*}.$INPUT_EXT"

    # Get the name of the expected output file
    expected_output="${test_name%.*}.$OUTPUT_EXT"
    touch $expected_output
    echo "Producing output for $test ...in $expected_output"

    # Run the test and store the output in the appropriate file
    $EXEC_DIR/$EXEC < $input_file > $expected_output 2>&1
done
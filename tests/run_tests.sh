#!/bin/zsh

## RUN TESTS SCRIPT
## This script will automate running all the tests and will 
## compare the output against the expected output.

## WARNING : This script MUST be run from the tests directory

# Coloured Output
RED='\033[0;31m'
GREEN='\033[0;32m'
BOLD='\033[1;97m'
RESET='\033[0m'

# Define all the directories
TEST_DIR="./"
EXEC_DIR="../bin/"

# Define the extensions
INPUT_EXT="in"
OUTPUT_EXT="out"

# Defining expecutables
EXEC="verCE"

for test in $(ls $TEST_DIR | egrep ".in$"); do

    # Get the name of the test and the temp holding file
    test_name=$(basename $test ".in")
    temp_file=$(mktemp)

    echo $test

    # Print out the test name fancily
    printf %30s | tr " " "="
    printf  " TEST: $test_name "
    printf %30s  | tr " " "=" 
    printf "\n"

    # Get the name of the input file
    input_file="${test_name%.*}.$INPUT_EXT"

    # Get the name of the expected output file
    expected_output="${test_name%.*}.$OUTPUT_EXT"

    # Run the test
    $EXEC_DIR$EXEC < $input_file > $temp_file 2>&1
    
    # Compare the output
    diff  $temp_file $expected_output > /dev/null

    # If the test fails, print the actual output and the expected output.
    if [ ${?} -ne 0 ]; then
        echo "${RED}Test $test_name failed!${RESET}"
        diff -u $temp_file $expected_output 
        echo ""
    else 
        echo "${GREEN} Test $test_name passed ${RESET}\n"
    fi

    # Remove the temp file
    rm $temp_file
done
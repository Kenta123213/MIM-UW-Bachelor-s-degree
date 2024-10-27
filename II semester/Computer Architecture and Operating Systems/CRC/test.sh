#!/bin/bash

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Function to run test and check result
run_test() {
    local test_number="$1"
    local cmd="$2"
    local expected="$3"
    local expected_exit_code="$4"

    result=$($cmd)
    exit_code=$?

    if [[ "$result" == "$expected" && "$exit_code" == "$expected_exit_code" ]]; then
        echo -e "test nr $test_number: ${GREEN}success${NC}"
    else
        echo -e "test nr $test_number: ${RED}fail${NC}"
    fi
}

# Test cases
run_test 1 "./crc /home/students/inf/PUBLIC/SO/zadanie_3_2024/plik1 1" "1" 0
run_test 2 "./crc /home/students/inf/PUBLIC/SO/zadanie_3_2024/plik1 011" "010" 0
run_test 3 "./crc /home/students/inf/PUBLIC/SO/zadanie_3_2024/plik1 11010101" "01010111" 0
run_test 4 "./crc /home/students/inf/PUBLIC/SO/zadanie_3_2024/plik2 11010101" "10110011" 0
run_test 5 "./crc /home/students/inf/PUBLIC/SO/zadanie_3_2024/plik 1" "" 1
run_test 6 "./crc /home/students/inf/PUBLIC/SO/zadanie_3_2024/plik1 ''" "" 1

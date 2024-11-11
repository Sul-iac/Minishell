#!/bin/bash

TESTS=(
    "ls |"
    "| ls"
    "ls > "
    "ls < "
    "ls >>"
    "<<"
    ">"
    "<"
    "|"
    "ls >>> file"
    "ls <<< file"
    "ls || ls"
    "ls && ls"
    "echo $UNDEFINED_VAR"
    "cd ~/nonexistent"
    "ls ; ls"
    "./nonexistent"
    "ls /root"
    "cat Makefile > /root/test"
    "export TEST+=42"
    "> outfile"
    "< infile"
    "echo Hello > file < inputfile"
)

for test in "${TESTS[@]}"; do
    echo "Testing: $test"
    echo "$test" | ./minishell
    echo "Exit status: $?"
    echo "------------------------"
done
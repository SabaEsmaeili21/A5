#!/bin/bash

for dir in tests/*
do
    num=$(basename "$dir")
    ./UTGame ./data/Players.csv ./data/Admins.csv <"$dir/$num.in"> output.txt

    if diff -w output.txt "$dir/$num.out" > /dev/null;
    then
        echo "Test $num : PASS"
    else
        echo "Test $num: FAIL"
    fi 
done
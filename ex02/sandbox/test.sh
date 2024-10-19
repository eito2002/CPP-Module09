#!/bin/bash

for i in {1..5}
do
  echo "Run $i:"
  ./PmergeMe `jot -r 6000 1 100000 | tr '\n' ' '` | awk '/After:/ { for(i=2;i<=NF;i++) print $i }' | sort -n -c
done
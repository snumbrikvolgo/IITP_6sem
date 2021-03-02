#!/bin/bash

rm -rf result.dat

for lambda in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9
do
for q in 1 2 5 10 25 50
do
  ./execute.py $lambda 1 100000 $q  --runMode static >> resultMM1k.dat
done
done



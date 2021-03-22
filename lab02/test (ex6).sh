#!/bin/bash

N=10

if [ ! -f "strassen_secv" ]
then
    echo "Nu exista binarul multiply_seq"
    exit
fi

if [ ! -f "strassen" ]
then
    echo "Nu exista binarul multiply"
    exit
fi

./strassen_secv $N > seq.txt
./strassen $N  > par.txt

diff seq.txt par.txt

rm -rf seq.txt par.txt

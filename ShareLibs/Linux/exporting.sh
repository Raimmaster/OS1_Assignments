#!/bin/bash

gcc -c -Wall -Werror -fpic suma.c
gcc -shared -o libsuma.so suma.o
gcc -L/home/raim/Documents/Unitec/III\ Year/Q5/Siso\ I/OS1_Assignments/ShareLibs/Linux/ -Wall -o test main.c -lsuma
echo $LD_LIBRARY_PATH
LD_LIBRARY_PATH=/home/raim/Documents/Unitec/III\ Year/Q5/Siso\ I/OS1_Assignments/ShareLibs/Linux:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/home/raim/Documents/Unitec/III\ Year/Q5/Siso\ I/OS1_Assignments/ShareLibs/Linux:$LD_LIBRARY_PATH

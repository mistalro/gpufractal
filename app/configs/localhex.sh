#!/bin/bash

# Set up a local virtual display of 2x2 quads. 
# These have the following layout in terms of port numbers:
#
#     #1    #2
#  #0    #3    #6
#     #5    #4 

DIMENSIONS=-w160x90

# Each display has a separate server
./compute -s -p8080 -b -x160x90 $DIMENSIONS &
./compute -s -p8081 -b -x80x0   $DIMENSIONS &
./compute -s -p8082 -b -x240x0  $DIMENSIONS &
./compute -s -p8083 -b -x320x90 $DIMENSIONS &
./compute -s -p8084 -b -x240x180 $DIMENSIONS &
./compute -s -p8085 -b -x80x180 $DIMENSIONS &
./compute -s -p8086 -b -x0x90 $DIMENSIONS &

# Set up the client window. The file nodehex.txt defines the 
# hostnames and port numbers for each remote display

./compute -c -nnodehex.txt


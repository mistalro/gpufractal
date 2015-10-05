#!/bin/bash

# Set up a local virtual display of 2x2 quads. 
# These have the following layout in terms of port numbers:
#
# 8080 8081
# 8082 8083

./compute -s -p8080 -b -x160x90 -w160x90 &
./compute -s -p8081 -b -x320x90 -w160x90 &
./compute -s -p8082 -b -x160x180 -w160x90 &
./compute -s -p8083 -b -x320x180 -w160x90 &

# Set up the client window. The file nodequads.txt defines the 
# hostnames and port numbers for each remote display

./compute -c -nnodequads.txt


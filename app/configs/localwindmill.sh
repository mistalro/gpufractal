#!/bin/bash

# Create a windmill shape using four servers

./compute -s -p8080 -b -w90x160 -x70x0 &
./compute -s -p8081 -b -w160x90 -x160x70 &
./compute -s -p8082 -b -w90x160 -x160x160 &
./compute -s -p8083 -b -w160x90 -x0x160 &

sleep 5
# Now run the client

./compute -c -nnodewindmill.txt

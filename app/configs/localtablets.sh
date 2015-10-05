#!/bin/bash

# Create a windmill shape using four servers

./compute -s -p8080 -b -w160x90 -x0x0 &
./compute -s -p8081 -b -w160x90 -x160x0 &
./compute -s -p8082 -b -w160x90 -x160x90 &
./compute -s -p8083 -b -w160x90 -x0x90 &

sleep 5
# Now run the client

./compute -c -nnodetablet.txt

#!/bin/bash
./compute -c -s -p8080 &
sleep 1
./compute -c -nnodesimple.txt

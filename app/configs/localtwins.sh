#!/bin/bash

./compute -s -c -nnodesimple2.txt -p8080 $1 -v &
./compute -s -c -nnodesimple.txt -p8081 $2 -v &

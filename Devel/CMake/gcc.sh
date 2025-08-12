#!/bin/bash

LOG_LEVEL=$1

if [ -z $LOG_LEVEL ]; then
    LOG_LEVEL="STATUS"
fi

cmake -S . -B ./build/gcc/debug -DCMAKE_BUILD_TYPE:STRING="Debug" -DCMAKE_CXX_FLAGS_DEBUG:STRING="-g -Wall -Wextra" --log-level="$LOG_LEVEL"
cmake -S . -B ./build/gcc/release -DCMAKE_BUILD_TYPE:STIRNG="Release" 


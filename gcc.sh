#!/bin/bash
cmake -S . -B ./build/gcc/debug -DCMAKE_BUILD_TYPE:STRING="Debug" -DCMAKE_CXX_FLAGS_DEBUG:STRING="-g -Wall -Wextra"
cmake -S . -B ./build/gcc/release -DCMAKE_BUILD_TYPE:STIRNG="Release" 


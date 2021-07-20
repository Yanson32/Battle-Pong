#!/bin/bash


mkdir build;
mkdir build/debug;
mkdir build/release;
cmake -S . -B ./build/debug -DCMAKE_CXX_FLAGS_DEBUG:STRING="-g -Wall -Wextra"


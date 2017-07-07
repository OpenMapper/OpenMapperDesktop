#!/bin/bash

rm -rf build/

# Build OpenMapper Static Lib only
mkdir -p build
cd build
cmake .. 
make -j4

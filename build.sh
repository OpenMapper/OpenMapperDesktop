#!/bin/bash

# rm -rf build/

# Build OpenMapperDesktop
mkdir -p build
cd build
cmake .. 
make -j4

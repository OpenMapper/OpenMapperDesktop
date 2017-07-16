#!/bin/bash

rm -rf build/

# Build Package app
mkdir -p build
cd build
cmake .. 
cpack ..

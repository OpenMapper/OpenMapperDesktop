#!/bin/bash

# rm -rf build/

# Build OpenMapperDesktop
mkdir -p build
cd build
cmake .. -DCMAKE_PREFIX_PATH=/usr/local/Cellar/qt/5.9.1/
make -j4

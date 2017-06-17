#!/bin/bash

cwd0=$(pwd)

# build the SLAM wrapper & engine
cd OpenMapper
sh build.sh
cd $cwd0

sh build_only_gui.sh

#!/bin/bash

source /etc/environment
unset LD_LIBRARY_PATH

mkdir -p build && cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .

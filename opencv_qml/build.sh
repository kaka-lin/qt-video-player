#!/bin/bash

# unset LD_LIBRARY_PATH

mkdir -p obj
qmake
make -j8

#!/bin/bash

mkdir -p obj
qmake
make -j8

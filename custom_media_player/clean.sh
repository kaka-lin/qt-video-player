#!/bin/bash

# cmake
rm -rf build

# qmake
rm -rf obj
rm -rf Makefile
rm -rf .qmake.stash
rm -rf lld

# Qt version >= 5.15
name="$(ls *.pro)"
folder=$(echo $name | cut -d"." -f 1)
rm -rf "$folder.app"


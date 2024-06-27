#!/bin/bash

# cmake
rm -rf build

# qmake
rm -rf obj
rm -rf Makefile
rm -rf .qmake.stash
rm -rf lld

name="$(ls *.pro)"
folder=$(echo $name | cut -d"." -f 1)
# Qt version < 5.15
rm -rf $folder
# Qt version >= 5.15
rm -rf "$folder.app"

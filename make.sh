#!/bin/sh

# Go to the valgrind library folder
cd ./lib/valgrind/

# Getting the current folder's absolute path
ABS_PATH=`pwd` 

# Run a standard UNIX ./configure with a special flag for 64bit only platform support 
./configure --prefix="$ABS_PATH"

# Make and Make install
make && make install

# Go back to the project's root folder
cd ../..
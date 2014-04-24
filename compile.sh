#!/bin/sh

# Compile the program with very strict flags and some debugging flags in additions
gcc -g -O0 -Wall -Wextra -std=c89 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement $1 -o builds/build.out

# Run the program wrapped with Valgrind to detect memoryleaks and overflows
# [NOTE] Valgrind is broken at the moment on Mac OSX Maverick
# valgrind --leak-check=yes ./builds/build.out
./builds/build.out
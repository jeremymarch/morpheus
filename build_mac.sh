#!/bin/sh

# Modern macOS build script

# Use the system's default compiler
export CC="gcc -D_POSIX_C_SOURCE=200809L -std=c89 -fcommon -Wno-return-mismatch -Wno-implicit-int -Wno-implicit-function-declaration"
export LDFLAGS=""


cd src
make clean
# -e flag to allow override of CC and LDFLAGS from the environment
make -e
make install
cd -
strip bin/morpheus
echo "Build complete. The executable is in bin/morpheus"

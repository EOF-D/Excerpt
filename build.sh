#!/bin/bash

# Create build directory
mkdir -p build
cd build

# Check if we need to build tests
if [ "$1" == "--build-tests" ]; then
  cmake -D BUILD_TESTS=ON ..
else
  cmake ..
fi

# Build the project
cmake --build .

# Running tests
if [ "$1" == "--run-tests" ] || [ "$2" == "--run-tests" ]; then
  if [ -x "tests/ExcerptTests" ]; then
    ctest
  else
    echo "Test executable not found. Please build tests first using './build.sh --build-tests'."
  fi
fi

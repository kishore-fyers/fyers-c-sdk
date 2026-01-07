#!/bin/bash

cd /Users/em997/Documents/trade-c-sdk/fyers-api-c/build || exit 1

# Run cmake to ensure build files are up to date
cmake .. || exit 1

echo "Building on_position..."
make on_position || exit 1

echo "Running on_position..."
./examples/on_position "$@"
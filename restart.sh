#!/bin/bash

cd /Users/em997/Documents/trade-c-sdk/fyers-api-c/build || exit 1

echo "Building data_ws_example..."
make data_ws_example || exit 1

echo "Running data_ws_example..."
./examples/data_ws_example "$@"
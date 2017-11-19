#!/bin/bash

echo "Running script.sh..."

echo "    Running C++..."
./cpp/scripts/script.sh
if [ $? -ne 0 ]; then
    exit 1
fi

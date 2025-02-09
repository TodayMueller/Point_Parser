#!/bin/bash

PROJECT_DIR=$(realpath "$(dirname "$(realpath "$0")")"/../..)
VENV_DIR="$PROJECT_DIR/env"

if [ ! -d "$VENV_DIR" ]; then
    echo "Error: Virtual environment not found at $VENV_DIR. Please ensure you have run build.sh first."
    exit 1
fi

source "$VENV_DIR/bin/activate"

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 file1 file2 ..."
    deactivate
    exit 1
fi

SCRIPT_DIR=$(dirname "$(realpath "$0")")
output=$("$SCRIPT_DIR"/cpp_program "$@")
exit_code=$?

if [ $exit_code -ne 0 ]; then
    echo "Error: C++ program failed."
    deactivate
    exit $exit_code
fi

echo "$output" | python3 "$PROJECT_DIR/install/lib/plot.py"
python_exit_code=$?

if [ $python_exit_code -ne 0 ]; then
    echo "Error: Python script failed."
    deactivate
    exit $python_exit_code
fi

echo "Processing completed successfully."
deactivate

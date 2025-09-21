#!/bin/bash

# Default to build/debug if no argument provided
BUILD_DIR="${1:-build/debug}"

if [ ! -d "$BUILD_DIR" ]; then
    echo "Error: Build directory '$BUILD_DIR' not found"
    echo "Usage: $0 [build_directory]"
    echo "Example: $0 build/debug"
    exit 1
fi

echo "=== COVERAGE SUMMARY ==="
echo "Project source files coverage:"
echo ""

# Find gcda files and run gcov on them to get coverage stats
find "$BUILD_DIR" -name "*.gcda" | grep -E "(note|chord|input|settings)" | while read -r gcda_file; do
    # Skip autogen and test files, focus on source files
    if [[ "$gcda_file" == *"autogen"* ]] || [[ "$gcda_file" == *"test_"* ]] || [[ "$gcda_file" == *"qrc_"* ]]; then
        continue
    fi

    dir=$(dirname "$gcda_file")
    filename=$(basename "$gcda_file" .gcda)

    # Run gcov and extract the coverage line for the source file (not system headers)
    coverage_output=$(cd "$dir" && gcov "$(basename "$gcda_file")" 2>&1)
    # Look for the coverage line that corresponds to our source file path
    source_file_line=$(echo "$coverage_output" | grep -A1 "File.*chordless.*${filename}" | grep "Lines executed" | head -1)

    if [ -n "$source_file_line" ]; then
        echo "$filename:"
        echo "  $source_file_line"
        echo ""
    fi
done
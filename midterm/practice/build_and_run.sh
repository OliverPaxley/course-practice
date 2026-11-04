#!/bin/bash

# Build and run script for all midterm practice files
# Usage: ./build_and_run.sh [folder_name]

set -e

PRACTICE_DIR="/Users/macbookair/Desktop/course-practice/midterm/practice"

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

compile_and_run() {
    local file="$1"
    local filename=$(basename "$file" .cpp)
    local dir=$(dirname "$file")
    local output_dir="$dir/build"

    mkdir -p "$output_dir"

    echo -e "${YELLOW}Compiling: $filename${NC}"

    if g++ -std=c++17 -Wall -Wextra -o "$output_dir/$filename" "$file" 2>&1; then
        echo -e "${GREEN}✓ Compiled successfully${NC}"
        echo -e "${YELLOW}Running: $filename${NC}"
        if "$output_dir/$filename"; then
            echo -e "${GREEN}✓ Ran successfully${NC}"
        else
            echo -e "${RED}✗ Runtime error${NC}"
        fi
    else
        echo -e "${RED}✗ Compilation failed${NC}"
        echo -e "${YELLOW}Expected: Fails to Compile${NC}"
    fi
    echo ""
}

# If folder specified, only build that folder
if [ $# -eq 1 ]; then
    FOLDER="$1"
    if [ -d "$PRACTICE_DIR/$FOLDER" ]; then
        echo "Building folder: $FOLDER"
        for file in "$PRACTICE_DIR/$FOLDER"/*.cpp; do
            [ -f "$file" ] && compile_and_run "$file"
        done
    else
        echo "Folder not found: $PRACTICE_DIR/$FOLDER"
        exit 1
    fi
else
    # Build all folders
    echo "Building all practice files..."
    echo "=================================="

    for folder in "$PRACTICE_DIR"/*/; do
        if [ -d "$folder" ]; then
            folder_name=$(basename "$folder")
            echo ""
            echo "=== Folder: $folder_name ==="
            for file in "$folder"/*.cpp; do
                [ -f "$file" ] && compile_and_run "$file"
            done
        fi
    done
fi

echo "Done!"
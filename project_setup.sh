#!/bin/bash

# Define the directory path
OBJ_DIR="./obj"
EXEC_DIR="./exec"

# Check if the obj directory does not exist
if [ ! -d "$OBJ_DIR" ]; then
    # Directory does not exist, so create it
    mkdir "$OBJ_DIR"
    echo "Directory $OBJ_DIR created."
else
    echo "Directory $OBJ_DIR already exists."
fi

# Check if the exec directory does not exist
if [ ! -d "$EXEC_DIR" ]; then
    # Directory does not exist, so create it
    mkdir "$EXEC_DIR"
    echo "Directory $EXEC_DIR created."
else
    echo "Directory $EXEC_DIR already exists."
fi

make slm

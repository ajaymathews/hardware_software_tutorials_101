#!/bin/bash

# Simple script to test a Linux Kernel Module tutorial
# Usage: ./test_module.sh <directory_path>

if [ -z "$1" ]; then
    echo "Usage: $0 <directory_path>"
    exit 1
fi

DIR=$1

if [ ! -d "$DIR" ]; then
    echo "Error: Directory $DIR not found."
    exit 1
fi

cd "$DIR"

echo "--- Building Module in $DIR ---"
make clean
make

# Identify the .ko file
KO_FILE=$(ls *.ko | head -n 1)

if [ -z "$KO_FILE" ]; then
    echo "Error: .ko file not found after build."
    exit 1
fi

MODULE_NAME=$(basename "$KO_FILE" .ko)

echo "--- Cleaning dmesg ---"
sudo dmesg -C

echo "--- Loading Module: $KO_FILE ---"
sudo insmod "$KO_FILE"

echo "--- dmesg Output ---"
dmesg

echo "--- Unloading Module: $MODULE_NAME ---"
sudo rmmod "$MODULE_NAME"

echo "--- Done ---"

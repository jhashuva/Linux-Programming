#!/bin/bash

# Check if the correct number of command-line arguments is provided
if [ $# -ne 3 ]; then
  echo "Usage: $0 <filename> <start_line> <end_line>"
  exit 1
fi

filename="$1"
start_line="$2"
end_line="$3"

# Check if the file exists
if [ ! -f "$filename" ]; then
  echo "Error: File '$filename' not found."
  exit 1
fi

# Check if start_line and end_line are positive integers
if ! [[ "$start_line" =~ ^[0-9]+$ ]] || ! [[ "$end_line" =~ ^[0-9]+$ ]]; then
  echo "Error: Start and end line numbers must be positive integers."
  exit 1
fi

# Check if start_line is less than or equal to end_line
if [ "$start_line" -gt "$end_line" ]; then
  echo "Error: Start line number must be less than or equal to end line number."
  exit 1
fi

# Display lines between start_line and end_line
sed -n "${start_line},${end_line}p" "$filename"

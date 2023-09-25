#!/bin/bash

# Check if the correct number of command-line arguments is provided
if [ $# -lt 2 ]; then
  echo "Usage: $0 <word_to_delete> <file1> [<file2> ...]"
  exit 1
fi

word_to_delete="$1"
shift  # Remove the first argument (word_to_delete)

# Iterate through the remaining arguments (file names)
for file in "$@"; do
  # Check if the file exists
  if [ ! -f "$file" ]; then
    echo "Warning: File '$file' not found. Skipping..."
    continue
  fi

  # Create a temporary file to store the modified content
  temp_file=$(mktemp)
  
  # Use grep to exclude lines containing the word and write the result to the temporary file
  grep -v "$word_to_delete" "$file" > "$temp_file"

  # Replace the original file with the temporary file
  mv "$temp_file" "$file"

  echo "Deleted lines containing '$word_to_delete' from '$file'."
done

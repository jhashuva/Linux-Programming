#!/bin/bash

echo "Files with read, write, and execute permissions in the current directory:"

# Use the find command to locate files with the desired permissions
find . -type f -perm -u=rwx 2>/dev/null | while read -r file; do
  echo "$file"
done

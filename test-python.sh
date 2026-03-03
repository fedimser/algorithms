set -e
for FILE in python/*; do
  if [[ "$FILE" == *".py" ]]; then
    echo "Running $FILE.exe...";
    python3 $FILE
  fi
done
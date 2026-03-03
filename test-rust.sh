set -e  # Fail if any command fails.

for FILE in rust/*; do
  if [[ "$FILE" == *".rs" ]]; then
    echo "Compiling $FILE...";
    rustc $FILE -o $FILE.exe
    echo "Running $FILE.exe...";
    ./$FILE.exe
  fi
done

rm rust/*.exe
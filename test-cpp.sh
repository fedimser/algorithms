# Simple testing script.
# Compiles and runs every .cpp file.
# Every file must compile and compiled binary must complete with exit code 0.

# This makes it fail if any command fails.
set -e

for FILE in *; do
  if [[ "$FILE" == *".cpp" ]]; then
    echo "Compiling $FILE...";
    g++ $FILE -o $FILE.exe
    echo "Running $FILE.exe...";
    ./$FILE.exe
  fi
done

# Clean up.
rm *.exe
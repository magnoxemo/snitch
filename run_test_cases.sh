cd build/test_cases
for file in *; do
    if [[ -x "$file" && ! -d "$file" ]]; then
        echo "Running $file-------"
        ./$file 10 10 0.0 1.0 0.0 1.0
    fi
done
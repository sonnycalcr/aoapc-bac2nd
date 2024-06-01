content=$(< "./CMakeLists.txt")
while IFS= read -r line; do
    if [[ $line == "add_executable"* ]]; then
    pattern="\((.*?)\)"
    if [[ $line =~ $pattern ]]; then
        contentInParentheses="${BASH_REMATCH[1]}"
        result=($contentInParentheses)
        exePath="./build/${result[0]}"
        echo "start running as follows..."
        echo "=================================================="
        "$exePath"
    fi
    fi
done <<< "$content"

#!/usr/bin/env bash

PASS=0
FAIL=0

run_exact() {
    local expr="$1"
    local expected="$2"
    local output

    output=$(./RPN "$expr" 2>&1)
    output=${output//$'\r'/}
    if [ "$output" = "$expected" ]; then
        echo "[PASS] $expr => $output"
        PASS=$((PASS + 1))
    else
        echo "[FAIL] $expr"
        echo "       expected: $expected"
        echo "       got     : $output"
        FAIL=$((FAIL + 1))
    fi
}

run_usage_test() {
    local output
    local status

    output=$(./RPN 2>&1)
    status=$?
    output=${output//$'\r'/}

    case "$output" in
        Usage:*)
            if [ "$status" -eq 1 ]; then
                echo "[PASS] usage message and exit code"
                PASS=$((PASS + 1))
            else
                echo "[FAIL] usage test"
                echo "       expected exit code: 1"
                echo "       got exit code     : $status"
                FAIL=$((FAIL + 1))
            fi
            ;;
        *)
            echo "[FAIL] usage test"
            echo "       expected output to start with: Usage:"
            echo "       got: $output"
            FAIL=$((FAIL + 1))
            ;;
    esac
}

echo "Building project..."
if ! make >/dev/null; then
    echo "Build failed."
    exit 1
fi

echo "Running RPN tests..."
run_exact "4 5 *" "20"
run_exact "8 9 * 9 - 9 - 9 - 4 - 1 +" "42"
run_exact "7 7 * 7 -" "42"
run_exact "1 2 * 2 / 2 * 2 4 - +" "0"
run_exact "9 0 /" "Error: Division by zero."
run_exact "10 2 +" "Error: Invalid number in input."
run_exact "2 a +" "Error: Invalid character in input."
run_exact "1 +" "Error: Not enough operands for operator."
run_exact "1 2" "Error: Too many operands left after processing."
run_exact "" "Error: Too many operands left after processing."
run_usage_test

echo ""
echo "Summary: PASS=$PASS FAIL=$FAIL"

if [ "$FAIL" -ne 0 ]; then
    exit 1
fi

#!/bin/bash

# Function to run dijkstra with input from stdin and capture output
run_dijkstra() {
    input="$1"
    expected_output="$2"
    
    # Run dijkstra and capture its output
    output=$(echo "$input" | ./dijkstra)

    # Print the output for debugging (optional)
    echo "$output"

    # Validate the output
    if [[ "$output" == *"$expected_output"* ]]; then
        echo "Test passed: Output matches expected"
        for ((i=0; i<150; i++)); do
            echo -n "*"
        done
        echo  # Add a newline at the end

    else
        echo "Test failed: Output does not match expected"
        for ((i=0; i<150; i++)); do
            echo -n "*"
        done
        echo  # Add a newline at the end
    fi
}

# Test case 1: Valid input for the program
run_dijkstra "3 3
0 1 0
1 0 1
0 1 0
0" ""
  
# Test case 2: Valid input with different graph structure
run_dijkstra "4 4
0 3 0 0
0 0 5 0
0 0 0 7
2 0 0 0
0" ""


# Test case 3: Graph with negative weights (expected to fail due to invalid input)
run_dijkstra "3 3
0 10 -5
15 0 20
7 9 0
0" "Invalid input for matrix element. Number should be a non-negative integer."

# Test case 4: Invalid start vertex (expected to fail due to invalid vertex)
run_dijkstra "3 3
0 10 20
15 0 20
7 9 0
-1" "Invalid input: Source vertex must be between 0 and 3."

# Test case 5: Zero vertices (expected to fail due to invalid matrix size)
run_dijkstra "-2 -3" "Invalid input: Number of rows and columns must be positive integers."

# Test case 6: Non-integer source (expected to fail due to invalid source vertex)
run_dijkstra "3 3
0 10 20
15 0 20
7 9 0
A" "Invalid input: Source vertex must be an integer between 0 and 3."

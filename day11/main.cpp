#include "NumberProcessor.h"
#include <iostream>
#include <chrono>

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    // Load input
    std::vector<long long> testInput = {125, 17};
    std::vector<long long> input = NumberProcessor::loadInput("input.txt");

    // Test case
    std::cout << "Test 1: " << NumberProcessor::solve(testInput, 25) << std::endl;

    // Part 1 and Part 2
    std::cout << "Part 1: " << NumberProcessor::solve(input, 25) << std::endl;
    std::cout << "Part 2: " << NumberProcessor::solve(input, 75) << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Completed in: " << duration.count() << "ms" << std::endl;

    return 0;
}

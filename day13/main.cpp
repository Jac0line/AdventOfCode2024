#include "NumberProcessor.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    NumberProcessor processor;

    uint64_t sum1 = 0, sum2 = 0;
    std::vector<std::vector<int>> input = processor.parseFile("input.txt");
    for (auto nums : input) {
        sum1 += processor.getPricePart1(nums);
        sum2 += processor.getPricePart2(nums);
    }
    std::cout << "Part 1: " << sum1 << std::endl;
    std::cout << "Part 2: " << sum2 << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Completed in: " << duration.count() << "ms" << std::endl;

    return 0;
}
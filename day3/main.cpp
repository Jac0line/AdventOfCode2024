#include "NumberProcessor.h"

int main() {
    NumberProcessor processor;

    std::string fileName = "input.txt";

    // Part 1: Sum all valid multiplications
    std::cout << "=== Part 1 ===" << std::endl;
    processor.getMultiplicationSum(fileName);

    // Part 2: Handle `do()` and `don't()` instructions
    std::cout << "=== Part 2 ===" << std::endl;
    processor.getEnabledMultiplicationSum(fileName);

    return 0;
}

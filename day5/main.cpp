#include "NumberProcessor.h"

int main() {
    NumberProcessor processor;

    // Read input file
    if (!processor.parseInput("input.txt")) {
        return 1;
    }

    // Compute Part 1 and Part 2
    processor.validateUpdates();

    int sumPart1 = processor.getSumMiddlePages();
    std::cout << "Sum Part 1: " << sumPart1 << std::endl;

    int sumPart2 = processor.getSumMiddlePagesIvalid();
    std::cout << "Sum Part 2: " << sumPart2 << std::endl;

    return 0;
}

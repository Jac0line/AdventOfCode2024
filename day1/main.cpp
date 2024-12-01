#include "NumberProcessor.h"
#include <iostream>

int main() {
    NumberProcessor processor;

    // Read input file
    if (!processor.readInput("inputDay1.txt")) {
        return 1;
    }

    // Sort numbers
    processor.sortNumbers();

    // Compute part 1
    int sumPart1 = processor.computeSumOfDifferences();
    std::cout << "Sum Part 1: " << sumPart1 << std::endl;

    // Compute part 2
    int sumPart2 = processor.computeWeightedSum();
    std::cout << "Sum Part 2: " << sumPart2 << std::endl;

    return 0;
}

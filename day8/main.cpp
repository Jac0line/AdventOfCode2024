#include "NumberProcessor.h"
#include <iostream>

int main() {
    NumberProcessor processor;

    // Load test values
    processor.load_input("sample_input.txt");
    std::cout << "part1 (test): " << processor.part1() << std::endl;
    std::cout << "part2 (test): " << processor.part2() << std::endl;

    // Load actual values
    processor.load_input("input.txt");
    std::cout << "part1 (actual): " << processor.part1() << std::endl;
    std::cout << "part2 (actual): " << processor.part2() << std::endl;

    return 0;
}

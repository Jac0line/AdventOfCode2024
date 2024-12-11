#include "NumberProcessor.h"
#include <iostream>

int main() {
    NumberProcessor processor;
    
    std::string input = processor.readInput("input.txt");
    std::string testInput = "2333133121414131402";

    std::vector<long> testFileStructure = processor.buildFileStructure(testInput);
    std::vector<long> fileStructure = processor.buildFileStructure(input);

    std::cout << "Test 1: " << processor.part1(testFileStructure) << std::endl;
    std::cout << "Part 1: " << processor.part1(fileStructure) << std::endl;
    std::cout << "Test 2: " << processor.part2(testFileStructure) << std::endl;
    std::cout << "Part 2: " << processor.part2(fileStructure) << std::endl;
    return 0;
}

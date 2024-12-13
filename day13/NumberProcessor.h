#ifndef NUMBERPROCESSOR_H
#define NUMBERPROCESSOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <cstdint>
#include <climits>

using namespace std;


class NumberProcessor {
public:
    std::vector<std::vector<int>> parseFile(std::string fileName);
    int getPricePart1(std::vector<int> nums);
    uint64_t getPricePart2(std::vector<int> nums);

private:
    std::vector<int> getNumbersInLine(std::string line);

};

#endif // NUMBERPROCESSOR_H

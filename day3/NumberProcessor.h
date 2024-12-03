#ifndef NUMBERPROCESSOR_H
#define NUMBERPROCESSOR_H

#include <string>
#include <vector>
#include <iostream>


class NumberProcessor {
private:
    std::vector<std::vector<int>> all_numbers;
    std::vector<int> parseLine(const std::string& line, const std::string& delimiter);

public:
    bool readInput(const std::string& fileName);
    int getMultiplicationSum(const std::string& fileName);
    int getEnabledMultiplicationSum(const std::string& fileName);
};

#endif // NUMBERPROCESSOR_H

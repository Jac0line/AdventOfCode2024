#ifndef NUMBER_PROCESSOR_H
#define NUMBER_PROCESSOR_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <tuple>

class NumberProcessor {
private:
    std::vector<std::vector<long long int>> all_numbers;
    std::vector<long long int> all_sums;
    std::vector<long long int> parseLine(const std::string& line, const std::string& delimiter);

public:
    bool readInput(const std::string& fileName);
    long long int CalcTotalCalibrationResult(bool part2);

};

#endif

#include "NumberProcessor.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath> // For std::abs

std::pair<int, int> NumberProcessor::parseLine(const std::string& line, const std::string& delimiter) {
    size_t pos = line.find(delimiter);
    int nr1 = std::stoi(line.substr(0, pos));
    int nr2 = std::stoi(line.substr(pos + delimiter.size()));
    return {nr1, nr2};
}

bool NumberProcessor::readInput(const std::string& fileName, const std::string& delimiter) {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        auto [nr1, nr2] = parseLine(line, delimiter);
        firstNrs.push_back(nr1);
        secondNrs.push_back(nr2);
    }
    inputFile.close();
    return true;
}

void NumberProcessor::sortNumbers() {
    std::sort(firstNrs.begin(), firstNrs.end());
    std::sort(secondNrs.begin(), secondNrs.end());
}

int NumberProcessor::computeSumOfDifferences() const {
    int sum = 0;
    auto it1 = firstNrs.begin();
    auto it2 = secondNrs.begin();
    while (it1 != firstNrs.end() && it2 != secondNrs.end()) {
        sum += std::abs(*it1 - *it2);
        ++it1;
        ++it2;
    }
    return sum;
}

int NumberProcessor::computeWeightedSum() const {
    int sum = 0;
    for (int num1 : firstNrs) {
        int count = std::count(secondNrs.begin(), secondNrs.end(), num1);
        sum += num1 * count;
    }
    return sum;
}

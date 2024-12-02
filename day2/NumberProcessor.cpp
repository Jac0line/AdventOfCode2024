#include "NumberProcessor.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath> // For std::abs
#include <sstream>
#include <vector>

std::vector<int> NumberProcessor::parseLine(const std::string& line, const std::string& delimiter) {
    std::vector<int> numbers;
    std::istringstream stream(line);
    int number;

    while (stream >> number) {
        numbers.push_back(number);
    }
    return numbers;
}

bool NumberProcessor::readInput(const std::string& fileName, const std::string& delimiter) {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(inputFile, line)) {
        std::vector<int> numbers = parseLine(line, delimiter);
        all_numbers.push_back(numbers);
    }
    inputFile.close();
    return true;
}

bool NumberProcessor::isSafeReport(const std::vector<int>& report) const {
    if (report.size() < 2) {
        return true; // Trivially safe if fewer than two levels
    }

    bool increasing = report[0] < report[1];
    for (size_t i = 1; i < report.size(); ++i) {
        if (increasing) {
            if (!(report[i] > report[i - 1] && report[i] <= report[i - 1] + 3)) {
                return false;
            }
        } else {
            if (!(report[i] < report[i - 1] && report[i] >= report[i - 1] - 3)) {
                return false;
            }
        }
    }
    return true;
}

int NumberProcessor::getSaveReports() const {
    int sum = 0;

    for (const auto& report : all_numbers) {
        if (isSafeReport(report)) {
            ++sum;
        }
    }
    return sum;
}

int NumberProcessor::getSaveReportsWithDamper() const {
    int sum = 0;
    for (const auto& report : all_numbers) {
        if (isSafeReport(report)) {
            ++sum; // Already safe
        } else {
            bool dampenedSafe = false;
            // Try removing each level one at a time
            for (size_t i = 0; i < report.size(); ++i) {
                std::vector<int> modifiedReport = report;
                modifiedReport.erase(modifiedReport.begin() + i);
                if (isSafeReport(modifiedReport)) {
                    dampenedSafe = true;
                    break;
                }
            }
            if (dampenedSafe) {
                ++sum;
            }
        }
    }
    return sum;
}

#ifndef NUMBERPROCESSOR_H
#define NUMBERPROCESSOR_H

#include <string>
#include <vector>

class NumberProcessor {
private:
    std::vector<std::vector<int>> all_numbers;

    std::vector<int> parseLine(const std::string& line, const std::string& delimiter);
    bool isSafeReport(const std::vector<int>& report) const;

public:
    bool readInput(const std::string& fileName, const std::string& delimiter = " ");
    int getSaveReports() const;
    int getSaveReportsWithDamper() const;
};

#endif // NUMBERPROCESSOR_H

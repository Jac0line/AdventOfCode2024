#ifndef NUMBERPROCESSOR_H
#define NUMBERPROCESSOR_H

#include <vector>
#include <string>

class NumberProcessor {
private:
    std::vector<int> firstNrs;
    std::vector<int> secondNrs;

    // Helper function to split a line into two integers
    std::pair<int, int> parseLine(const std::string& line, const std::string& delimiter);

public:
    // Method to read input from a file
    bool readInput(const std::string& fileName, const std::string& delimiter = "   ");

    // Method to sort the vectors
    void sortNumbers();

    // Method to compute the sum of absolute differences
    int computeSumOfDifferences() const;

    // Method to compute the weighted sum for matching elements
    int computeWeightedSum() const;
};

#endif // NUMBERPROCESSOR_H

#ifndef NUMBERPROCESSOR_H
#define NUMBERPROCESSOR_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class NumberProcessor {
private:
    std::vector<std::vector<char>> wordMatrix;

public:
    bool readInput(const std::string& fileName, const std::string& delimiter = "   ");
    int computeWordSearch() const;
    int computeXMAS() const;
};

#endif // NUMBERPROCESSOR_H

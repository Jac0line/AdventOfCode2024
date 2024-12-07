#ifndef NUMBER_PROCESSOR_H
#define NUMBER_PROCESSOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <tuple>

class NumberProcessor {
private:
    std::vector<std::vector<char>> wordMatrix;
    std::pair<int, int> guardLocation;
    std::string guardDirection;

    std::pair<int, int> getNextPosition(const std::pair<int, int>& position, const std::string& direction) const;
    std::string turnRight(const std::string& currentDirection) const;

public:
    bool readInput(const std::string& fileName);
    std::set<std::pair<int, int>> simulatePatrol();
    bool isLoopDetected();
    int countObstructionPositions();
};

#endif

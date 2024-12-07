#include "NumberProcessor.h"

bool NumberProcessor::readInput(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return false;
    }

    std::string line;
    int row = 0;
    while (std::getline(inputFile, line)) {
        std::vector<char> lineVector;
        for (int col = 0; col < line.size(); ++col) {
            char character = line[col];
            lineVector.push_back(character);

            if (character == '<' || character == '^' || character == '>' || character == 'v') {
                guardLocation = {row, col};
                switch (character) {
                case '<': guardDirection = "left"; break;
                case '^': guardDirection = "up"; break;
                case '>': guardDirection = "right"; break;
                case 'v': guardDirection = "down"; break;
                }
            }
        }
        wordMatrix.push_back(lineVector);
        ++row;
    }

    inputFile.close();
    return true;
}

std::pair<int, int> NumberProcessor::getNextPosition(const std::pair<int, int>& position, const std::string& direction) const {
    if (direction == "up") return {position.first - 1, position.second};
    if (direction == "down") return {position.first + 1, position.second};
    if (direction == "left") return {position.first, position.second - 1};
    if (direction == "right") return {position.first, position.second + 1};
    return position;
}

std::string NumberProcessor::turnRight(const std::string& currentDirection) const {
    if (currentDirection == "up") return "right";
    if (currentDirection == "right") return "down";
    if (currentDirection == "down") return "left";
    if (currentDirection == "left") return "up";
    return currentDirection;
}

bool NumberProcessor::isLoopDetected() {
    std::set<std::tuple<int, int, std::string>> visitedStates;
    auto currentLocation = guardLocation;
    auto currentDirection = guardDirection;

    int rows = wordMatrix.size();
    int cols = wordMatrix[0].size();

    while (true) {
        auto state = std::make_tuple(currentLocation.first, currentLocation.second, currentDirection);
        if (visitedStates.count(state)) {
            std::cout << "Loop detected!" << std::endl;
            return true; // Loop detected
        }
        std::cout << "state:" << state << std::endl;
        visitedStates.insert(state);

        // Print the guard's current position and direction
        std::cout << "Guard at (" << currentLocation.first << ", " << currentLocation.second
                  << ") facing " << currentDirection << std::endl;

        auto nextPosition = getNextPosition(currentLocation, currentDirection);

        if (nextPosition.first < 0 || nextPosition.first >= rows || nextPosition.second < 0 || nextPosition.second >= cols) {
            return false; // No loop; guard leaves the map
        }

        if (wordMatrix[nextPosition.first][nextPosition.second] == '#') {
            currentDirection = turnRight(currentDirection);
        } else {
            currentLocation = nextPosition;
        }
    }
}


int NumberProcessor::countObstructionPositions() {
    int rows = wordMatrix.size();
    int cols = wordMatrix[0].size();
    int obstructionCount = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == guardLocation.first && j == guardLocation.second) continue;
            if (wordMatrix[i][j] == '#') continue;

            // Temporarily place an obstruction
            wordMatrix[i][j] = '#';
            std::cout << "Testing obstruction at (" << i << ", " << j << ")" << std::endl;

            // Save guard state
            auto originalLocation = guardLocation;
            auto originalDirection = guardDirection;

            // Simulate patrol
            if (isLoopDetected()) {
                ++obstructionCount;
            }

            // Restore guard state
            guardLocation = originalLocation;
            guardDirection = originalDirection;

            // Remove the obstruction
            wordMatrix[i][j] = '.';
        }
    }

    return obstructionCount;
}

std::set<std::pair<int, int>> NumberProcessor::simulatePatrol() {
    std::set<std::pair<int, int>> visited;
    visited.insert(guardLocation);

    int rows = wordMatrix.size();
    int cols = wordMatrix[0].size();

    while (true) {
        auto nextPosition = getNextPosition(guardLocation, guardDirection);

        if (nextPosition.first < 0 || nextPosition.first >= rows || nextPosition.second < 0 || nextPosition.second >= cols) {
            break;
        }

        if (wordMatrix[nextPosition.first][nextPosition.second] == '#') {
            guardDirection = turnRight(guardDirection);
        } else {
            guardLocation = nextPosition;
            visited.insert(guardLocation);
        }
    }

    return visited;
}

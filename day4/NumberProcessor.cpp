#include "NumberProcessor.h"

bool NumberProcessor::readInput(const std::string& fileName, const std::string& delimiter) {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::vector<char> lineVector;
        for(char character : line){
            if(character >= 'A' && character < 'z' && character != ' ')
            {
                lineVector.push_back(character);
            }
        }
        wordMatrix.push_back(lineVector);
    }
    inputFile.close();
    return true;
}


int NumberProcessor::computeWordSearch() const {
    int sum = 0;
    int nrOfRows = wordMatrix.size();
    int nrOfColumns = wordMatrix[0].size();
    std::string target = "XMAS";
    int targetLen = target.length();

    // Directions: (dx, dy) pairs
    std::vector<std::pair<int, int>> directions = {
        {0, 1},   // Horizontal right
        {0, -1},  // Horizontal left
        {1, 0},   // Vertical down
        {-1, 0},  // Vertical up
        {1, 1},   // Diagonal down-right
        {1, -1},  // Diagonal down-left
        {-1, 1},  // Diagonal up-right
        {-1, -1}  // Diagonal up-left
    };

    // Lambda to check for a match in a specific direction
    auto matches = [&](int x, int y, int dx, int dy) {
        for (int i = 0; i < targetLen; ++i) {
            int nx = x + i * dx, ny = y + i * dy;
            if (nx < 0 || nx >= nrOfRows || ny < 0 || ny >= nrOfColumns || wordMatrix[nx][ny] != target[i]) {
                return false;
            }
        }
        return true;
    };

    // Iterate through every cell in the wordMatrix
    for (int i = 0; i < nrOfRows; ++i) {
        for (int j = 0; j < nrOfColumns; ++j) {
            // Check for "XMAS" starting at (i, j) in all directions
            for (const auto& [dx, dy] : directions) {
                if (matches(i, j, dx, dy)) {
                    ++sum;
                }
            }
        }
    }

    // Return the total count
    return sum;
}


int NumberProcessor::computeXMAS() const {
    int count = 0;
    int nrOfRows = wordMatrix.size();
    int nrOfColumns = wordMatrix[0].size();

    // Helper lambda to check for "MAS" (forwards or backwards)
    auto isMAS = [&](char m, char a, char s) {
        return (m == 'M' && a == 'A' && s == 'S') || (m == 'S' && a == 'A' && s == 'M');
    };

    // Iterate through the grid to find the center of the "X-MAS" pattern
    for (int i = 1; i < nrOfRows - 1; ++i) {
        for (int j = 1; j < nrOfColumns - 1; ++j) {
            if (wordMatrix[i][j] != 'A') {
                continue; // The center must be 'A'
            }

            // Check the two diagonals
            // Diagonal 1: top-left to bottom-right
            if (i > 0 && i < nrOfRows - 1 && j > 0 && j < nrOfColumns - 1) {
                if (isMAS(wordMatrix[i - 1][j - 1], wordMatrix[i][j], wordMatrix[i + 1][j + 1])) {
                    // Diagonal 2: bottom-left to top-right
                    if (isMAS(wordMatrix[i + 1][j - 1], wordMatrix[i][j], wordMatrix[i - 1][j + 1])) {
                        ++count; // Found a valid X-MAS
                    }
                }
            }
        }
    }

    return count;
}


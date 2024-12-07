#include "NumberProcessor.h"

int main() {
    NumberProcessor processor;

    if (!processor.readInput("sample_input.txt")) {
        return 1;
    }

    std::set<std::pair<int, int>> visitedPositions = processor.simulatePatrol();
    std::cout << "Distinct positions visited: " << visitedPositions.size() << std::endl;

    int countedObstructionsPositions = processor.countObstructionPositions();
    std::cout << "countObstructionPositions: " << countedObstructionsPositions << std::endl;

    return 0;
}

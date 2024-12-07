#include "NumberProcessor.h"

int main() {
    NumberProcessor processor;

    if (!processor.readInput("input.txt")) {
        return 1;
    }

    long long int calResult = processor.CalcTotalCalibrationResult(false);
    std::cout << "total calibration result part 1: " << calResult << std::endl;

    long long int calResult = processor.CalcTotalCalibrationResult(true);
    std::cout << "total calibration result part 2: " << calResult << std::endl;

    return 0;
}

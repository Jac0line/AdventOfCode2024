#include "NumberProcessor.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>

std::vector<long long> NumberProcessor::loadInput(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    std::string line;
    getline(inputFile, line);
    inputFile.close();

    std::vector<long long> stones;
    std::istringstream stream(line);
    long long number;
    while (stream >> number) {
        stones.push_back(number);
    }

    return stones;
}

int NumberProcessor::countDigits(long long value) {
    int digits = 0;
    while (value > 0) {
        digits++;
        value /= 10;
    }
    return digits;
}

bool NumberProcessor::hasEvenDigits(long long value) {
    return countDigits(value) % 2 == 0;
}

std::vector<long long> NumberProcessor::splitNumber(long long value) {
    int totalDigits = countDigits(value);
    int halfDigits = totalDigits / 2;

    long long rightPart = 0, leftPart = value;
    long long multiplier = 1;

    for (int i = 0; i < halfDigits; ++i) {
        int digit = leftPart % 10;
        leftPart /= 10;
        rightPart += digit * multiplier;
        multiplier *= 10;
    }

    return {leftPart, rightPart};
}

long long NumberProcessor::pebbleCount(const std::vector<long long>& stones, int numBlinks, Memo& memoMap) {
    if (numBlinks == 0) {
        return stones.size();
    }

    long long result = 0;
    for (const auto& value : stones) {
        std::pair<long long, int> key = {value, numBlinks};
        if (memoMap.find(key) != memoMap.end()) {
            result += memoMap[key];
            continue;
        }

        if (value == 0) {
            long long count = pebbleCount({1}, numBlinks - 1, memoMap);
            memoMap[key] = count;
            result += count;
        } else if (hasEvenDigits(value)) {
            auto splitStones = splitNumber(value);
            long long count = pebbleCount(splitStones, numBlinks - 1, memoMap);
            memoMap[key] = count;
            result += count;
        } else {
            long long count = pebbleCount({value * 2024}, numBlinks - 1, memoMap);
            memoMap[key] = count;
            result += count;
        }
    }
    return result;
}

long long NumberProcessor::solve(const std::vector<long long>& stones, int numBlinks) {
    Memo memoMap;
    return pebbleCount(stones, numBlinks, memoMap);
}

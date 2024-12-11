#ifndef NUMBERPROCESSOR_H
#define NUMBERPROCESSOR_H

#include <vector>
#include <unordered_map>
#include <string>

struct LongPairHash {
    size_t operator()(const std::pair<long long, int>& pair) const {
        size_t hash1 = std::hash<long long>{}(pair.first);
        size_t hash2 = std::hash<int>{}(pair.second);
        return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
    }
};

typedef std::unordered_map<std::pair<long long, int>, long long, LongPairHash> Memo;

class NumberProcessor {
public:
    static long long pebbleCount(const std::vector<long long>& stones, int numBlinks, Memo& memoMap);
    static long long solve(const std::vector<long long>& stones, int numBlinks);
    static std::vector<long long> loadInput(const std::string& fileName);
private:
    static bool hasEvenDigits(long long value);
    static std::vector<long long> splitNumber(long long value);
    static int countDigits(long long value);
};

#endif // NUMBERPROCESSOR_H

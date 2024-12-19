#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

struct InputData
{
     std::unordered_set<std::string> towelPatterns;
     std::vector<std::string> designs;
};

InputData parseInputfile(std::string inputfile) {
    InputData data;
        // Open the input file
    std::ifstream inputFile(inputfile);
    if (!inputFile) {
        std::cerr << "Error: Could not open input file." << std::endl;
    }

    // Read the towel patterns
    std::string patternsLine;
    std::getline(inputFile, patternsLine);
    size_t start = 0;
    size_t end;
    while ((end = patternsLine.find(',', start)) != std::string::npos) {
        data.towelPatterns.insert(patternsLine.substr(start, end - start));
        start = end + 2;
    }
    data.towelPatterns.insert(patternsLine.substr(start)); // Add the last pattern

    // Skip the blank line
    std::string blankLine;
    std::getline(inputFile, blankLine);

    // Read the desired designs
    std::string design;
    while (std::getline(inputFile, design)) {
        data.designs.push_back(design);
    }

    inputFile.close();
    return data;
}


// Function to check if a design can be formed using the towel patterns
bool canFormDesign(const std::string& design, const std::unordered_set<std::string>& patterns) {
    // Base case: If the design is empty, it's possible
    if (design.empty()) {
        return true;
    }

    // Try to match the beginning of the design with any towel pattern
    for (const auto& pattern : patterns) {
        if (design.substr(0, pattern.size()) == pattern) {
            if (canFormDesign(design.substr(pattern.size()), patterns)) {
                return true;
            }
        }
    }

    // If no pattern matches, the design cannot be formed
    return false;
}

// Function to count the number of ways to form a design using towel patterns
unsigned long long countWays(const std::string& design, const std::unordered_set<std::string>& patterns, std::unordered_map<std::string, unsigned long long>& memo) {
    // If the design is empty, there's one way (use no towels)
    if (design.empty()) return 1;

    // If already computed, return the memoized result
    if (memo.find(design) != memo.end()) {
        return memo[design];
    }

    unsigned long long ways = 0;

    // Try every towel pattern as a prefix
    for (const auto& pattern : patterns) {
        if (design.substr(0, pattern.size()) == pattern) {
            // If the pattern matches the start of the design, recursively count for the rest
            ways += countWays(design.substr(pattern.size()), patterns, memo);

            // Optional Debug Output:
            // std::cout << "Matching pattern: " << pattern << ", Remaining design: " << design.substr(pattern.size()) << ", Ways so far: " << ways << std::endl;
        }
    }

    // Store result in memo and return
    memo[design] = ways;
    return ways;
}

int main() {

    std::string inputfile = "input.txt";
    InputData data = parseInputfile(inputfile);

    // Count the number of possible designs
    int possibleCount = 0;
    for (const auto& design : data.designs) {
        if (canFormDesign(design, data.towelPatterns)) {
            possibleCount++;
        }
    }

    // Output the result
    std::cout << "Number of possible designs: " << possibleCount << std::endl;

    unsigned long long totalWays = 0;

    // Compute the number of ways for each design
    for (const auto& design : data.designs) {
        std::unordered_map<std::string, unsigned long long> memo; // Memoization map (reset for each design)
        unsigned long long ways = countWays(design, data.towelPatterns, memo);
        totalWays += ways;
    }

    std::cout << "Total number of ways: " << totalWays << std::endl;

    return 0;
}

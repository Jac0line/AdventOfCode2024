#include <iostream>
#include <fstream>
#include <regex>
#include <string>

class NumberProcessor {
public:
    bool readInput(const std::string& fileName);
    int getMultiplicationSum(const std::string& fileName);
    int getEnabledMultiplicationSum(const std::string& fileName);
};

bool NumberProcessor::readInput(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return false;
    }

    std::string content((std::istreambuf_iterator<char>(inputFile)),
                        std::istreambuf_iterator<char>());
    std::cout << "Content:\n" << content << std::endl;

    inputFile.close();
    return true;
}


// Function for Part 1: Sum all valid `mul(X, Y)` products
int NumberProcessor::getMultiplicationSum(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return 0;
    }

    // Read entire file content into a single string.
    std::string content((std::istreambuf_iterator<char>(inputFile)),
                        std::istreambuf_iterator<char>());

    std::regex mulRegex(R"(mul\((\d{1,3}),(\d{1,3})\))");
    int totalSum = 0;

    // Use regex to find all matches for mul(X,Y) in the content.
    auto begin = std::sregex_iterator(content.begin(), content.end(), mulRegex);
    auto end = std::sregex_iterator();

    for (std::sregex_iterator it = begin; it != end; ++it) {
        std::smatch match = *it;
        int x = std::stoi(match[1]);
        int y = std::stoi(match[2]);

        int product = x * y;
        totalSum += product;

        std::cout << "Found: " << match.str() << " -> " << x << " * " << y << " = " << product << std::endl;
    }

    inputFile.close();
    std::cout << "Total Sum of Products: " << totalSum << std::endl;
    return totalSum;
}


// Function for Part 2: Handle `do()` and `don't()` instructions
int NumberProcessor::getEnabledMultiplicationSum(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return 0;
    }

    // Read entire file content into a single string.
    std::string content((std::istreambuf_iterator<char>(inputFile)),
                        std::istreambuf_iterator<char>());

    std::regex mulRegex(R"(mul\((\d{1,3}),(\d{1,3})\))"); // Matches valid mul(X,Y)
    std::regex doRegex(R"(do\(\))");                     // Matches do()
    std::regex dontRegex(R"(don't\(\))");                // Matches don't()

    int totalSum = 0;
    bool isEnabled = true; // Multiplications are enabled by default.

    std::vector<int> stateChangePositions; // Tracks the positions of state changes (do() and don't()).
    std::vector<std::pair<int, int>> mulMatches; // Tracks positions and results of mul().

    // Find all state change (do() and don't()) positions in the content.
    auto doIt = std::sregex_iterator(content.begin(), content.end(), doRegex);
    for (auto it = doIt; it != std::sregex_iterator(); ++it) {
        stateChangePositions.push_back(it->position());
        std::cout << "Found: do() at position " << it->position() << std::endl;
    }

    auto dontIt = std::sregex_iterator(content.begin(), content.end(), dontRegex);
    for (auto it = dontIt; it != std::sregex_iterator(); ++it) {
        stateChangePositions.push_back(it->position());
        std::cout << "Found: don't() at position " << it->position() << std::endl;
    }

    // Sort state change positions to handle sequential state evaluation.
    std::sort(stateChangePositions.begin(), stateChangePositions.end());

    // Find all mul(X,Y) matches along with their positions in the content.
    auto mulIt = std::sregex_iterator(content.begin(), content.end(), mulRegex);
    for (auto it = mulIt; it != std::sregex_iterator(); ++it) {
        int mulPos = it->position();
        int x = std::stoi((*it)[1]);
        int y = std::stoi((*it)[2]);
        mulMatches.emplace_back(mulPos, x * y);
        std::cout << "Found: mul(" << x << "," << y << ") at position " << mulPos
                  << " -> " << x << " * " << y << " = " << x * y << std::endl;
    }

    // Determine state for each mul() based on closest preceding state change.
    for (const auto& [mulPos, product] : mulMatches) {
        isEnabled = true; // Default to enabled.

        for (int statePos : stateChangePositions) {
            if (statePos > mulPos) {
                break; // Stop checking if the state change is after the mul().
            }

            // Update the enabled state based on the state change at this position.
            if (content.substr(statePos, 4) == "do()") {
                isEnabled = true;
            } else if (content.substr(statePos, 7) == "don't()") {
                isEnabled = false;
            }
        }

        if (isEnabled) {
            totalSum += product;
            std::cout << "Enabled: mul() at position " << mulPos
                      << " -> Adding " << product << " to total." << std::endl;
        } else {
            std::cout << "Disabled: mul() at position " << mulPos
                      << " -> Skipping." << std::endl;
        }
    }

    inputFile.close();
    std::cout << "Total Sum of Enabled Products: " << totalSum << std::endl;
    return totalSum;
}

#ifndef NUMBERPROCESSOR_H
#define NUMBERPROCESSOR_H

#include <string>
#include <vector>
#include <tuple>

class NumberProcessor {
private:
    void p1ShiftFiles(std::vector<long> &fileStructure);
    int findEmpty(std::vector<long> &fileStructure, int fileLen);
    std::pair<int, int> findFile(const std::vector<long> &fileStructure, int id);
    void p2ShiftFiles(std::vector<long> &fileStructure);
    long long checkSum(const std::vector<long> &fileStructure);

public:
    std::string readInput(const std::string &fileName); 
    std::vector<long> buildFileStructure(const std::string &input);
    long long part1(std::vector<long> fileStructure);
    long long part2(std::vector<long> fileStructure);
};

#endif // NUMBERPROCESSOR_H

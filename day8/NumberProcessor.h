#ifndef NUMBERPROCESSOR_H
#define NUMBERPROCESSOR_H

#include <vector>
#include <map>
#include <set>
#include <string>

// Position struct and related operators
struct pos_t {
    int x, y;
};

bool operator<(const pos_t& a, const pos_t& b);
pos_t operator+(const pos_t& a, const pos_t& b);
pos_t operator-(const pos_t& a, const pos_t& b);

// NumberProcessor class
class NumberProcessor {
public:
    // Load the input data from a file
    void load_input(const std::string& file);

    // Solve part 1 and part 2
    size_t part1() const;
    size_t part2() const;

private:
    struct map_t {
        std::map<char, std::vector<pos_t>> frequency_to_positions;
        int width = 0;
        int height = 0;

        bool in_grid(const pos_t& p) const;
    };

    map_t map_data;
};

#endif // NUMBERPROCESSOR_H

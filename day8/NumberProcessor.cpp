#include "NumberProcessor.h"
#include <tuple>
#include <fstream>
#include <algorithm>

// pos_t operators
bool operator<(const pos_t& a, const pos_t& b) {
    return std::tuple<int, int>(a.x, a.y) < std::tuple<int, int>(b.x, b.y);
}

pos_t operator+(const pos_t& a, const pos_t& b) {
    return {a.x + b.x, a.y + b.y};
}

pos_t operator-(const pos_t& a, const pos_t& b) {
    return {a.x - b.x, a.y - b.y};
}

// map_t methods
bool NumberProcessor::map_t::in_grid(const pos_t& p) const {
    return p.x >= 0 && p.x < width && p.y >= 0 && p.y < height;
}

// NumberProcessor methods
void NumberProcessor::load_input(const std::string& file) {
    map_data = {};
    std::ifstream fs(file);
    std::string line;
    while (std::getline(fs, line)) {
        for (int x = 0; x < line.size(); ++x) {
            if (line[x] != '.') {
                map_data.frequency_to_positions[line[x]].push_back({x, map_data.height});
            }
        }
        map_data.width = std::max(map_data.width, static_cast<int>(line.size()));
        map_data.height++;
    }
}

size_t NumberProcessor::part1() const {
    std::set<pos_t> antinodes;

    for (auto& [freq, positions] : map_data.frequency_to_positions) {
        for (int i = 0; i < positions.size(); ++i) {
            for (int j = i + 1; j < positions.size(); ++j) {
                pos_t delta = positions[i] - positions[j];

                if (map_data.in_grid(positions[i] + delta)) {
                    antinodes.insert(positions[i] + delta);
                }

                if (map_data.in_grid(positions[j] - delta)) {
                    antinodes.insert(positions[j] - delta);
                }
            }
        }
    }

    return antinodes.size();
}

size_t NumberProcessor::part2() const {
    std::set<pos_t> antinodes;

    for (auto& [freq, positions] : map_data.frequency_to_positions) {
        for (int i = 0; i < positions.size(); ++i) {
            for (int j = i + 1; j < positions.size(); ++j) {
                pos_t delta = positions[i] - positions[j];

                for (pos_t p = positions[i]; map_data.in_grid(p); p = p + delta) {
                    antinodes.insert(p);
                }

                for (pos_t p = positions[j]; map_data.in_grid(p); p = p - delta) {
                    antinodes.insert(p);
                }
            }
        }
    }

    return antinodes.size();
}

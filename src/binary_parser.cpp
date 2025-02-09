#include "binary_parser.h"
#include <fstream>
#include <stdexcept>
#include <cstdint>

std::vector<Point> BinaryParser::parseFile(const std::string& filename) {
    std::vector<Point> points;
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Failed to open file");

    uint32_t data;
    while (file.read(reinterpret_cast<char*>(&data), sizeof(data))) {
        Point point;

        point.group = std::to_string((data >> 24) & 0xFF);
        point.x = (data >> 12) & 0xFFF;                  
        point.y = data & 0xFFF;                          

        points.push_back(point);
    }
    return points;
}

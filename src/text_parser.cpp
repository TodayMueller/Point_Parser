#include "text_parser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

std::vector<Point> TextParser::parseFile(const std::string& filename) {
    std::vector<Point> points;
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Failed to open file");

    std::string line;
    while (std::getline(file, line)) {
        size_t colon = line.find(':');
        size_t comma = line.find(',', colon);
        if (colon == std::string::npos || comma == std::string::npos) continue;

        Point point;
        point.group = line.substr(0, colon);
        point.x = std::stoi(line.substr(colon + 1, comma - colon - 1));
        point.y = std::stoi(line.substr(comma + 1));

        points.push_back(point);
    }
    return points;
}

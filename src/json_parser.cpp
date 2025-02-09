#include "json_parser.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <stdexcept>

std::vector<Point> JsonParser::parseFile(const std::string& filename) {
    std::vector<Point> points;
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Failed to open file");

    nlohmann::json json_data;
    file >> json_data;

    for (const auto& point_data : json_data["points"]) {
        Point point;
        point.group = point_data["group"];
        point.x = point_data["x"];
        point.y = point_data["y"];

        points.push_back(point);
    }
    return points;
}

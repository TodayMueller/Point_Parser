#ifndef PARSER_BASE_H
#define PARSER_BASE_H

#include <vector>
#include <string>

struct Point {
    std::string group;
    int x;
    int y;
};

class ParserBase {
public:
    virtual ~ParserBase() = default;
    virtual std::vector<Point> parseFile(const std::string& filename) = 0;
};

#endif

#ifndef BINARY_PARSER_H
#define BINARY_PARSER_H

#include "parser_base.h"
#include <vector>
#include <string>

class BinaryParser : public ParserBase {
public:
    std::vector<Point> parseFile(const std::string& filename) override;
};

#endif

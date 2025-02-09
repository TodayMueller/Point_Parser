#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "parser_base.h"
#include <vector>
#include <string>

class JsonParser : public ParserBase {
public:
    std::vector<Point> parseFile(const std::string& filename) override;
};

#endif

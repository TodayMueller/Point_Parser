#ifndef TEXT_PARSER_H
#define TEXT_PARSER_H

#include "parser_base.h"
#include <vector>
#include <string>

class TextParser : public ParserBase {
public:
    std::vector<Point> parseFile(const std::string& filename) override;
};

#endif

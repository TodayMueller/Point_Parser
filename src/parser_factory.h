#ifndef PARSER_FACTORY_H
#define PARSER_FACTORY_H

#include <memory>
#include <string>
#include "parser_base.h"

class ParserFactory {
public:
    std::unique_ptr<ParserBase> createParser(const std::string& filename) const;
};

#endif

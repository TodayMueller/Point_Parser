#include "parser_factory.h"
#include "text_parser.h"    
#include "binary_parser.h"  
#include "json_parser.h"    

std::unique_ptr<ParserBase> ParserFactory::createParser(const std::string& filename) const {
    if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".txt") {
        return std::unique_ptr<ParserBase>(new TextParser());
    } else if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".bin") {
        return std::unique_ptr<ParserBase>(new BinaryParser());
    } else if (filename.size() > 5 && filename.substr(filename.size() - 5) == ".json") {
        return std::unique_ptr<ParserBase>(new JsonParser());
    }
    return nullptr;
}

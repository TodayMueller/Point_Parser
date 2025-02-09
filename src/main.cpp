#include "parser_factory.h"
#include "text_parser.h"   
#include "binary_parser.h"  
#include "json_parser.h"  

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

std::vector<std::thread> threads;
std::vector<Point> global_points;
std::mutex mutex;
bool error_occurred = false;

void parseFileInThread(const std::string& filename, const std::unique_ptr<ParserBase>& parser) {
    try {
        auto points = parser->parseFile(filename);
        std::lock_guard<std::mutex> lock(mutex);
        global_points.insert(global_points.end(), points.begin(), points.end());
    } catch (const std::runtime_error& e) {
        std::cerr << "Error parsing file " << filename << ": " << e.what() << std::endl;
        std::lock_guard<std::mutex> lock(mutex);
        error_occurred = true;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " file1 file2 ..." << std::endl;
        return 1;
    }

    ParserFactory factory;

    for (int i = 1; i < argc; ++i) {
        std::string filename = argv[i];
        std::unique_ptr<ParserBase> parser;

        if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".txt") {
            parser.reset(new TextParser());
        } else if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".bin") {
            parser.reset(new BinaryParser());
        } else if (filename.size() > 5 && filename.substr(filename.size() - 5) == ".json") {
            parser.reset(new JsonParser());
        } else {
            std::cerr << "Error: Unsupported file format or invalid file: " << filename << std::endl;
            return 1;
        }

        threads.emplace_back(parseFileInThread, filename, std::move(parser));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    if (error_occurred) {
        return 1;
    }

    std::cout << "{\"points\":[" << std::endl;
    bool first = true;
    for (const auto& point : global_points) {
        if (!first) std::cout << "," << std::endl;
        std::cout << "{\"group\":\"" << point.group << "\",\"x\":" << point.x << ",\"y\":" << point.y << "}";
        first = false;
    }
    std::cout << "]}" << std::endl;

    return 0;
}

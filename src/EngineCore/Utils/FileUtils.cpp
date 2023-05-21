
#include "FileUtils.h"

#include <fstream>
#include <iostream>

namespace EngineCore::Utils::FileUtils {
    std::string LoadTextFile(const char *filePath) {
        std::ifstream textFile;
        std::string text;

        textFile.open(filePath, std::ios::in | std::ios::binary);
        if (!textFile.is_open()) {
            std::cerr << "Missing text file" << std::endl;
            return "";
        }

        textFile.seekg(0, std::ios::end);
        text.resize(static_cast<std::string::size_type>(textFile.tellg()));
        textFile.seekg(0, std::ios::beg);
        textFile.read(&text[ 0 ], text.size());

        textFile.close();

        return std::move(text);
    }
} // EngineCore::Utils::FileUtils

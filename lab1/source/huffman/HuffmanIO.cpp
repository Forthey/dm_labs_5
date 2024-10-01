#include "HuffmanIO.h"
#include "utility/BinaryString.h"

#include <format>
#include <fstream>
#include <sstream>
#include <algorithm>


std::string HuffmanIO::prettyCode(CharCodeWithMeta const &code) {
    std::string result;
    for (uint8_t i = code.length; i > 0; --i) {
        result += (static_cast<char>(code.code >> (i - 1)) & 1) + '0';
    }
    return result;
}

void HuffmanIO::printCodes(std::unordered_map<char, CharCodeWithMeta> const& codes,
                           std::ostream &out) {
    for (auto const &[ch, code]: codes) {
        out << std::format("{}: {}\n", ch, prettyCode(code));
    }
}

std::string HuffmanIO::prettySize(uint64_t size) {
    static std::unordered_map<uint8_t, std::string> levelToMeasureUnit = {
            {0, "B"},
            {1, "KB"},
            {2, "MB"},
            {3, "GB"}
    };
    std::size_t loweredSize;
    uint8_t level = 0;
    while ((loweredSize = size / 1024) > 100) {
        size = loweredSize;
        level++;
    }

    return std::format("{}{}", size, levelToMeasureUnit[level]);
}

void HuffmanIO::printStats(uint64_t const sizeBefore, uint64_t const sizeAfter) {
    double compressionRatio = 1.0 - double(sizeAfter) / double(sizeBefore);
    std::cout << std::format(
            "size: {} -> {} ({}%)\n",
            HuffmanIO::prettySize(sizeBefore), HuffmanIO::prettySize(sizeAfter),
            static_cast<int>(compressionRatio * 100)
    );
}

void HuffmanIO::saveStats(uint64_t const size, uint64_t const compressedSize) {
    std::ofstream file("stats.csv", std::ofstream::app);

    file << size << ";" << compressedSize << std::endl;
}

void HuffmanIO::writeToFile(std::string const &filename, std::string const &str) {
    std::ofstream file(filename, std::ofstream::binary);

    if (!file.is_open()) {
        throw std::runtime_error(
                std::format("Cannot write into {}. Please, check program read/write permissions", filename)
        );
    }

    file << str;
}

std::shared_ptr<std::string const> HuffmanIO::readFromFile(std::string const &filename) {
    std::ifstream file(filename, std::ifstream::binary);

    if (!file.is_open()) {
        throw std::runtime_error(std::format("Cannot open file {}", filename));
    }

    std::stringstream ss;
    ss << file.rdbuf();

    return std::make_shared<std::string>(ss.str());
}

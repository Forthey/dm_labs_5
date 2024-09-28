#include "HuffmanIO.h"
#include "utility/BinaryString.h"

#include <format>
#include <fstream>
#include <sstream>


std::shared_ptr<std::string> HuffmanIO::prettyCode(CharCodeWithMeta const &code) {
    auto result = std::make_shared<std::string>();
    for (uint8 i = code.length; i > 0; --i) {
        *result += char(code.code >> (i - 1) & 1) + '0';
    }
    return result;
}

void HuffmanIO::printCodes(std::shared_ptr<std::unordered_map<char, CharCodeWithMeta> const> const &codes,
                           std::ostream &out) {
    for (auto const &[ch, code]: *codes) {
        out << std::format("{}: {}\n", ch, *prettyCode(code));
    }
}

void HuffmanIO::writeToFile(std::string const &filename, std::string const &str) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error(
                std::format("Cannot write into {}. Please, check your read/write permissions", filename)
        );
    }

    file << str;
}

std::shared_ptr<std::string const> HuffmanIO::readFromFile(std::string const &filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error(std::format("Cannot open file {}", filename));
    }

    std::stringstream ss;
    ss << file.rdbuf();

    return std::make_shared<std::string>(ss.str());
}

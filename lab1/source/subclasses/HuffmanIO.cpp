#include "HuffmanIO.h"

#include <format>
#include <fstream>


std::shared_ptr<std::string> HuffmanIO::prettyCode(CharCodeWithMeta const& code) {
    auto result = std::make_shared<std::string>();
    uint8 discharge = code.length;
    while (discharge > 0) {
        *result += char(code.code >> (discharge - uint8(1)) & 1ull) + '0';
        discharge--;
    }
    return result;
}

void HuffmanIO::printCodes(std::shared_ptr<std::unordered_map<char, CharCodeWithMeta> const> const& codes, std::ostream& out) {
    for (auto const& [ch, code] : *codes) {
        out << std::format("{}: {}\n", ch, *prettyCode(code));
    }
}

void HuffmanIO::writeToFile(std::string const& filename, std::string const& str) {
    std::ofstream file(filename);

    if (!file.is_open())
        throw std::runtime_error("Cannot open file");
}
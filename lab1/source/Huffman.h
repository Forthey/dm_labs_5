#pragma once

#include <string>
#include <unordered_map>

namespace Huffman {

    class Huffman {
    public:
        enum class KwargsKeys {
            print_codes = 0,
            print_stats,
            save_stats
        };
    private:
        static std::unordered_map<KwargsKeys, bool> const defaultKwargs;
    public:

        static void compress(std::string const &inFilename, std::string const &outFilename,
                             std::unordered_map<KwargsKeys, bool> kwargs = {});

        static void decompress(std::string const &inFilename, std::string const &outFilename);
    };

}


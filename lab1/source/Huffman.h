#pragma once
#include <set>
#include <string>
#include <unordered_map>

#include "subclasses/HuffmanTree.h"
#include "subclasses/utility/CharCodeWithMeta.h"



namespace Huffman {

	class Huffman {
	public:
		void compress(std::string const& text, std::string const& outFilename);
        std::shared_ptr<std::string> decompress(std::string const& inFilename);
	};

}


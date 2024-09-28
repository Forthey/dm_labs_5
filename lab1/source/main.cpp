#include <iostream>
#include "Huffman.h"

int main() {
    Huffman::Huffman huf;

    huf.compress("aabbbccdddabc", "out.huff");
    std::cout << *huf.decompress("out.huff");
	return 0;

}
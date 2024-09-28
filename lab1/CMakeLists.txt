cmake_minimum_required(VERSION 3.27)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
project(
        huffman
        VERSION 0.1.0
        DESCRIPTION "Compress files using huffman encoding"
        LANGUAGES CXX
)

SET(SOURCE_FILES
        source/main.cpp
        source/Huffman.cpp
        source/subclasses/HuffmanTree.cpp
        source/subclasses/HuffmanStringCoder.cpp
        source/subclasses/HuffmanIO.cpp
        source/subclasses/utility/BinaryString.cpp
        source/subclasses/utility/BinaryStringReader.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
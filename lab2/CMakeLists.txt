cmake_minimum_required(VERSION 3.27)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
project(
        match
        VERSION 0.1.0
        DESCRIPTION "Find largest match in the given bipartite graph"
        LANGUAGES CXX
)

SET(SOURCE_FILES
        source/main.cpp
        source/BipartiteGraph.cpp
        source/GraphIO.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.21)
project(SimpleRendering)

set(CMAKE_CXX_STANDARD 14)


add_executable(SimpleRendering
        src/main.cpp
        src/tgaimage.cpp
        src/model.cpp
        )

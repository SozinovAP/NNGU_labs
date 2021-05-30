cmake_minimum_required(VERSION 3.6.0)

SET(PROJECT_HEADERS
        src/main/cpp/Counter.h
        src/main/cpp/Dictionary.h
        src/main/cpp/Tools.h
        )

SET(PROJECT_SOURCES
        src/main/cpp/Counter.cpp
        src/main/cpp/Dictionary.cpp
        src/main/cpp/Tools.cpp
        )

add_library(library-c
        SHARED
        ${PROJECT_HEADERS} ${PROJECT_SOURCES}
        )

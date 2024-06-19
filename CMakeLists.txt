cmake_minimum_required(VERSION 3.26.1)

project(Rakab
    HOMEPAGE_URL "https://github.com/Reza-namvaran/Rakab"
    LANGUAGES CXX
    VERSION 0.1
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # for clangd to know include directories

# Set the default generator to "MinGW Makefiles"
if(NOT CMAKE_GENERATOR)
    set(CMAKE_GENERATOR "MinGW Makefiles" CACHE INTERNAL "" FORCE)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(src/)
cmake_minimum_required(VERSION 3.10)

# Project name
project(SimpleCppProject)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directory for header files
include_directories(include)

# Define source files
set(SOURCES
    src/main.cpp
    src/GameManager.cpp
    src/Hero.cpp
    src/Team.cpp
    src/Drwhite.cpp
    src/SmallTaha.cpp
    src/BigTaha.cpp
    src/AminSafety.cpp
    src/DannyGolang.cpp
)

# Build the executable
add_executable(app ${SOURCES})
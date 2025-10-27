cmake_minimum_required(VERSION 3.16)
project(tinydb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)

# Include directory for your headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect sources
file(GLOB SOURCES "src/*.cpp")

file(GLOB TEST_CPP "tests/*.cpp")
file(GLOB TEST_HPP "tests/*.hpp")

# --- SFML CONFIG ---
find_package(SFML COMPONENTS Graphics Window System Audio REQUIRED)

# --- Main Executable ---
add_executable(main ${SOURCES} src/main.cpp)
target_link_libraries(main SFML::Graphics SFML::Window SFML::System SFML::Audio)

# --- Tests ---
add_executable(t ${SOURCES} ${TEST_CPP} ${TEST_HPP})
target_link_libraries(t SFML::Graphics SFML::Window SFML::System SFML::Audio)

# --- Assets ---
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

enable_testing()
add_test(NAME tinydb_test COMMAND t)

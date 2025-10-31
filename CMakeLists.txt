cmake_minimum_required(VERSION 3.16)
project(tinydb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)

# Include directory for your headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect sources
file(GLOB_RECURSE SOURCES_COMMON "src/common/*.cpp")
file(GLOB_RECURSE SOURCES_GAME "src/game/*.cpp")
# file(GLOB_RECURSE SOURCES_WORLDBUILDER "src/worldBuilder/*.cpp")

# file(GLOB_RECURSE TEST_CPP "tests/*.cpp")
# file(GLOB_RECURSE TEST_HPP "tests/*.hpp")

# --- SFML CONFIG ---
find_package(SFML COMPONENTS Graphics Window System Audio REQUIRED)

# --- Main Executable ---
add_executable(main ${SOURCES_COMMON} ${SOURCES_GAME})
target_link_libraries(main SFML::Graphics SFML::Window SFML::System SFML::Audio)

# # --- World Builder ---
# add_executable(world_builder ${SOURCES_COMMON} ${SOURCES_WORLDBUILDER})
# target_link_libraries(world_builder SFML::Graphics SFML::Window SFML::System SFML::Audio)

# # --- Tests ---
# add_executable(t ${SOURCES_COMMON} ${TEST_CPP} ${TEST_HPP})
# target_link_libraries(t SFML::Graphics SFML::Window SFML::System SFML::Audio)

# --- Assets ---
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

enable_testing()
add_test(NAME tinydb_test COMMAND t)

cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_COVERAGE "Build coverage" OFF)

set(
  HUNTER_CACHE_SERVERS
  "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
  CACHE STRING "Default cache server"
)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
  URL "https://github.com/cpp-pm/hunter/archive/v0.23.218.tar.gz"
  SHA1 "9a3594a61227967fb92159339ba326701b287b19"
)

project(lab04)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)
hunter_add_package(Boost COMPONENTS filesystem regex)
hunter_add_package(Boost COMPONENTS system regex)
find_package(Boost CONFIG REQUIRED filesystem regex)
find_package(Boost CONFIG REQUIRED system regex)

add_executable(
        lab04                              # Название цели
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/broker.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/source.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/broker.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/header.hpp
)

target_link_libraries(
        lab04                         # Цель, к которой просходит линковка
        Boost::filesystem                        # Библиотеки, которые линкуются к цели
        Boost::system
)

add_executable(tests
  # TODO: enum your files and delete this comment
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
)

# TODO: change template word to project name and delete this comment
target_include_directories(tests
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
# TODO: change template word to project name and delete this comment
target_link_libraries(tests GTest::main template)

enable_testing()
add_test(NAME unit_tests COMMAND tests) 

if(BUILD_COVERAGE)
  set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
  find_package(codecov)
  # TODO: change template word to project name and delete this comment
  add_coverage(lab04)
  add_coverage(tests)
  list(APPEND LCOV_REMOVE_PATTERNS "'${PROJECT_SOURCE_DIR}/tests/*'")
  coverage_evaluate()
endif()

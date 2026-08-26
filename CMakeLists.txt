cmake_minimum_required(VERSION 3.16)

project(avShell VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDAED 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(avShell
	src/main.cpp
	src/builtins.cpp
	src/lexer.cpp
	src/parser.cpp
)

target_include_directories(avShell PRIVATE
${CMAKE_SOURCE_DIR}/include
)

cmake_minimum_required(VERSION 2.8)

project(MLStone)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g")

add_executable(MLStone main.cpp game.cpp card.cpp player.cpp deck.cpp board.cpp utils.cpp card_generator.cpp)

FIND_PACKAGE(CxxTest REQUIRED)
IF(CXXTEST_FOUND)
	INCLUDE_DIRECTORIES(${CXXTEST_INCLUDE_DIR})
	ENABLE_TESTING()

	IF(NOT IS_DIRECTORY "tests")
		FILE(MAKE_DIRECTORY "tests")
	ENDIF()
	ADD_SUBDIRECTORY("tests")
ENDIF()
cmake_minimum_required(VERSION 2.8)

project(MLStone)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

# Angry error checks, for fun
#set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g -Wno-c++98-compat -Weverything -Werror -pedantic -pedantic-errors -Wno-unused-private-field")

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g -pedantic -pedantic-errors")

include_directories(".")

add_executable(MLStone
main.cpp 
target.cpp
effect.cpp 
effects/give_windfury_effect.cpp 
effects/heal_effect.cpp 
effects/damage_effect.cpp 
effects/destroy_effect.cpp 
factories/factories.cpp
game.cpp 
card.cpp 
player.cpp 
deck.cpp 
board.cpp 
utils.cpp 
card_generator.cpp)

FIND_PACKAGE(CxxTest REQUIRED)
IF(CXXTEST_FOUND)
	INCLUDE_DIRECTORIES(${CXXTEST_INCLUDE_DIR})
	ENABLE_TESTING()

	IF(NOT IS_DIRECTORY "tests")
		FILE(MAKE_DIRECTORY "tests")
	ENDIF()
	ADD_SUBDIRECTORY("tests")
ENDIF()

cmake_minimum_required (VERSION 3.7)

project (sdl_engine)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_library (sdl_engine SHARED)

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

find_package (SDL2 REQUIRED)
find_package (SDL2_ttf REQUIRED)

target_compile_options (sdl_engine PUBLIC
	-Wall -Wextra -Werror -pedantic
	)

set (CMAKE_VERBOSE_MAKEFILE OFF)
set (CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/src
	)

target_include_directories (sdl_engine PUBLIC
	${SDL2_INCLUDE_DIRS}
	${SDL2_TTF_INCLUDE_DIRS}
	)

target_link_libraries (sdl_engine
	${SDL2_LIBRARIES}
	${SDL2_TTF_LIBRARIES}
	core_utils
	)

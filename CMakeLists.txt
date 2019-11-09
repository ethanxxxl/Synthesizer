cmake_minimum_required(VERSION 2.6)
project(Synthesizer)

set(SRC
	src/main.cpp
	)

include_directories(./include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

add_executable(run ${SRC})

target_link_libraries(run rt m asound jack pthread portaudio)

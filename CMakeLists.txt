cmake_minimum_required(VERSION 3.1)

project(Physical)

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

# set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

## In most cases better set in the CMake cache
set(SFML_DIR "/mingw32/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio window REQUIRED)
add_executable(Physical
	src/main.cpp
	src/body.cpp
	src/world.cpp
	inc/point.h
	inc/body.h
	inc/world.h
)
target_include_directories(Physical PRIVATE "inc")
target_link_libraries(Physical sfml-graphics sfml-audio)

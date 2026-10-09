cmake_minimum_required(VERSION 3.20)
project(IndependenceDayAlienSignal LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(alien_signal
    src/main.cpp
    src/signal/SynthesizedAlienPulse.cpp
    src/signal/WavWriter.cpp)
target_include_directories(alien_signal PRIVATE src)
if(MSVC)
    target_compile_options(alien_signal PRIVATE /W4)
else()
    target_compile_options(alien_signal PRIVATE -Wall -Wextra -Wpedantic)
endif()

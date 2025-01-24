cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

project(zen-engine CXX)


add_library(zen-engine 
    zen/src/scene/Entity.cpp
    zen/src/scene/Node.cpp
    zen/src/scene/Entity.h
    zen/src/scene/Node.h
)


target_include_directories(zen-engine PUBLIC zen/src)
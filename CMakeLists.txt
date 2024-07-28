cmake_minimum_required(VERSION 3.28)
project(DBZ_BT3_PNACH_Generator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/sources)

add_definitions(-DLOGGER_ENABLED)

set(SRC_FILES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/character.cpp
    ${SRC_DIR}/character.h
    ${SRC_DIR}/characters.cpp
    ${SRC_DIR}/characters.h
    ${SRC_DIR}/core.cpp
    ${SRC_DIR}/core.h)

if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})
else()
    add_executable(${PROJECT_NAME} ${SRC_FILES})
endif()

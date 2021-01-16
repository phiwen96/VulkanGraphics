
cmake_minimum_required(VERSION 3.0.0)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

set(CXX_STANDARD_REQUIRED on)
set(CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)
# SET(CMAKE_SYSTEM_NAME Generic)

set(PROJECT_NAME
    ${PROJECT_NAME}Library
)

set(LIBRARY_NAME
${ProjectId}
)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/ph/${LIBRARY_NAME}/*.hpp src/pch.pch)

set(LIBRARY_SOURCE_DIR
    src
)


project(${PROJECT_NAME})

add_library(${LIBRARY_NAME} STATIC
    ${HEADERS}
    ${SOURCES}
)

target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_17)

target_precompile_headers(${LIBRARY_NAME} PUBLIC src/pch.pch)

target_include_directories(${LIBRARY_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/ph/${LIBRARY_NAME}>
    $<INSTALL_INTERFACE:include/ph/${LIBRARY_NAME}>
)

target_include_directories(${LIBRARY_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

#add_subdirectory(test)

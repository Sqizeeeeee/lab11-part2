cmake_minimum_required(VERSION 3.10)
project(LabProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -pedantic -O2)
endif()

# Исходники
set(SOURCES
    main.cpp
    avl/avl.cpp
    tree23/tree23.cpp
    sorting/sorts.cpp
    io/csv_reader.cpp
    io/csv_writer.cpp
    benchmark/benchmark.cpp
    tests/test_runner.cpp
)

# Создаём исполняемый файл
add_executable(lab ${SOURCES})

# Include директории
target_include_directories(lab PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/avl
    ${PROJECT_SOURCE_DIR}/tree23
    ${PROJECT_SOURCE_DIR}/sorting
    ${PROJECT_SOURCE_DIR}/io
    ${PROJECT_SOURCE_DIR}/benchmark
    ${PROJECT_SOURCE_DIR}/tests
)

# Для старых GCC
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(lab stdc++fs)
endif()
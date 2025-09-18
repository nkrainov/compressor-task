cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)

project(task_1)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

find_program(CLANG_FORMAT "clang-format")
find_program(CLANG_TIDY "clang-tidy")

if (CLANG_FORMAT)
    file(GLOB_RECURSE ALL_SOURCE_FILES
        "*.cpp" "*.hpp" "*.c" "*.h"
    )

    add_custom_target(
        format
        COMMAND ${CLANG_FORMAT}
        -i
        -style=file
        ${ALL_SOURCE_FILES}
    )
else()
    message(WARNING "clang-format not found. The 'format' target will not be available.")
endif()

if (CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY
        ${CLANG_TIDY}
        -config-file=${CMAKE_SOURCE_DIR}/.clang-tidy
        -extra-arg=-Wno-unknown-warning-option
    )
else()
    message(WARNING "clang-tidy not found. Static analysis will not be performed.")
endif()

find_package(Doxygen REQUIRED)
set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/docs)
set(DOXYGEN_EXTRACT_ALL YES)
doxygen_add_docs(docs
    ${CMAKE_SOURCE_DIR}/libcompressor/include
    ${CMAKE_SOURCE_DIR}/libcompressor/src
    ${CMAKE_SOURCE_DIR}/compressor/src
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
enable_testing()
add_subdirectory(libcompressor)
add_subdirectory(compressor)
find_package(BZip2 REQUIRED)
find_package(ZLIB REQUIRED)
add_library(libcompressor STATIC src/libcompressor.cpp)
target_include_directories(libcompressor PUBLIC include/)
target_link_libraries(libcompressor PUBLIC BZip2::BZip2 ZLIB::ZLIB)

add_subdirectory(./tests)
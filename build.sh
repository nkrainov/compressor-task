rm -rf build
mkdir build
conan install . --build=missing
cmake -S . --preset conan-release
cmake --build build/Release --target=format
cmake --build build/Release
cmake --build build/Release --target=docs
cmake --install build/Release --prefix ./install
cd build/Release
ctest -V -j4
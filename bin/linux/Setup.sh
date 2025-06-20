# Shell script to build Oceanic for Linux

rm -rf build
cmake -S . -B build -DOCEANIC_LINUX=ON
cmake --build build
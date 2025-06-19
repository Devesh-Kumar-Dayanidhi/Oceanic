# Shell script to build and run Oceanic for Linux

rm -rf build
cmake -S . -B build -DOCEANIC_LINUX=ON
cmake --build build

:: Shell script to build Oceanic for Windows 64-bit.

rmdir /s /q build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DOCEANIC_WIN64=ON
cmake --build build --config Release

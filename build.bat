set CXX=g++
cmake -S . -G "MinGW Makefiles" -B build -DCMAKE_BUILD_TYPE=Debug  -DCMAKE_CXX_COMPILER=g++
cmake --build build --config Debug -j6 --parallel 6
.\build\svim.exe %1
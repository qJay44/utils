@echo off
cls

echo int main() {return 0;}> main.cpp
cmake -S . -B Build\\Release -G "MinGW Makefiles" -D CMAKE_EXPORT_COMPILE_COMMANDS=ON -D CMAKE_BUILD_TYPE=Release
cmake --build Build\\Release --config Release
move /y Build\\Release\\compile_commands.json Build
del main.cpp

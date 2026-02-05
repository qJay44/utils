echo "int main() {return 0;}" > main.cpp
cmake -S . -B Build/Release -D CMAKE_EXPORT_COMPILE_COMMANDS=ON -D CMAKE_BUILD_TYPE=Release
cmake --build Build/Release --config Release
mv Build/Release/compile_commands.json .
rm main.cpp

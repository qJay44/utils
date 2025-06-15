include(./.env.cmake OPTIONAL RESULT_VARIABLE LOCAL_ENV)
message(STATUS "Local .env.cmake: ${LOCAL_ENV}")

cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MyProject VERSION 1.0)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror)
target_compile_options(${PROJECT_NAME} PRIVATE -isystem ${GENERAL_INCLUDES}/stb)

target_include_directories(${PROJECT_NAME} PUBLIC ${LIBTIFF_PATH}/include)
target_link_directories(${PROJECT_NAME} PUBLIC ${LIBTIFF_PATH}/lib)


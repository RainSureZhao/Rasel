cmake_minimum_required(VERSION 3.25)
project(Rasel)

set(CMAKE_CXX_STANDARD 20)
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/ThirdParty)

# 第三方库文件
add_subdirectory(ThirdParty)
include_directories(${THIRD_PARTY_DIR}/spdlog/include)

# 项目头文件
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/engine)

file(GLOB ENGINE "src/engine/*.cpp" "include/engine/*.h")
file(GLOB RASEL ${PROJECT_SOURCE_DIR}/include/Rasel.h)
file(GLOB SANDBOX ${PROJECT_SOURCE_DIR}/src/SandBox/*.cpp)

add_executable(Rasel ${ENGINE} ${RASEL} ${SANDBOX})
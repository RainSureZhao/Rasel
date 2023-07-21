cmake_minimum_required(VERSION 3.25)
project(Rasel)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/ThirdParty)

# 第三方库文件
add_subdirectory(ThirdParty)

file(GLOB ENGINE "src/engine/*.cpp" "include/engine/*.h")
file(GLOB RASEL "${PROJECT_SOURCE_DIR}/include/Rasel.h")
file(GLOB SANDBOX "${PROJECT_SOURCE_DIR}/src/SandBox/*.cpp")
file(GLOB EVENT "${PROJECT_SOURCE_DIR}/include/engine/Events/*.h")

add_executable(${PROJECT_NAME} ${ENGINE} ${RASEL} ${SANDBOX} ${EVENT})
# 添加头文件路径
target_include_directories(${PROJECT_NAME} PRIVATE
        "${PROJECT_SOURCE_DIR}/include" 
        "${PROJECT_SOURCE_DIR}/include/engine"
        "${PROJECT_SOURCE_DIR}/include/engine/Events")

target_link_libraries(${PROJECT_NAME} PRIVATE imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE stb)
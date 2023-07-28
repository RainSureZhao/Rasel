cmake_minimum_required(VERSION 3.25)
project(Rasel)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/ThirdParty)

set(PRECOMPILED_HEADER ${PROJECT_SOURCE_DIR}/include/stdafx.h)
find_package(OpenGL REQUIRED)

# 第三方库文件
add_subdirectory(ThirdParty)

file(GLOB ENGINE "${PROJECT_SOURCE_DIR}/src/engine/*.cpp" "${PROJECT_SOURCE_DIR}/include/engine/*.h")
file(GLOB RASEL "${PROJECT_SOURCE_DIR}/include/Rasel.h")
file(GLOB SANDBOX "${PROJECT_SOURCE_DIR}/src/SandBox/*.cpp")
file(GLOB EVENT "${PROJECT_SOURCE_DIR}/include/engine/Events/*.h")
file(GLOB PLATFORM_WINDOW "${PROJECT_SOURCE_DIR}/include/engine/Platforms/Windows/*.h" "${PROJECT_SOURCE_DIR}/src/engine/Platforms/Windows/*.cpp")
file(GLOB LAYER "${PROJECT_SOURCE_DIR}/include/engine/Layer/*.h" "${PROJECT_SOURCE_DIR}/src/engine/Layer/*.cpp")
file(GLOB IMGUI "${PROJECT_SOURCE_DIR}/include/engine/ImGui/*.h" "${PROJECT_SOURCE_DIR}/src/engine/ImGui/*.cpp")

add_executable(${PROJECT_NAME} ${ENGINE} ${RASEL} ${SANDBOX} ${EVENT} ${PLATFORM_WINDOW} ${LAYER} ${IMGUI})

# 添加头文件路径
target_include_directories(${PROJECT_NAME} PRIVATE
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/include/engine"
        "${PROJECT_SOURCE_DIR}/include/engine/Events"
        "${PROJECT_SOURCE_DIR}/include/engine/Platforms/Windows"
        "${PROJECT_SOURCE_DIR}/include/engine/Layer"
        "${PROJECT_SOURCE_DIR}/include/engine/ImGui")

# 配置预编译头文件
target_precompile_headers(${PROJECT_NAME} PRIVATE ${PRECOMPILED_HEADER})

target_link_libraries(${PROJECT_NAME} PRIVATE imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE stb)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)

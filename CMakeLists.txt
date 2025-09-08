cmake_minimum_required(VERSION 4.1)
project(svim VERSION 0.1.0 LANGUAGES CXX)

# ---- C++ standard ----
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Sources ----
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/graphics/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/graphics/api/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/util/*.cpp"
)

# ---- Executable ----
add_executable(${PROJECT_NAME}
    main.cpp
    ${PROJECT_SOURCES}
)

# ---- Include paths ----
target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
        "${CMAKE_SOURCE_DIR}/src/graphics"
        "${CMAKE_SOURCE_DIR}/src/graphics/api"
        "${CMAKE_SOURCE_DIR}/src/util"
)

# ---- Warnings ----
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -g -Wall -Wextra -Wpedantic)
endif()

# ---- Nice IDE structure ----
source_group(TREE "${CMAKE_SOURCE_DIR}" FILES ${PROJECT_SOURCES} main.cpp)

# ---- Example install (optional) ----
# install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

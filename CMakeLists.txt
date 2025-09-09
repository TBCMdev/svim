cmake_minimum_required(VERSION 3.10)
project(svim VERSION 0.1.0 LANGUAGES CXX)

# ---- C++ standard ----
set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER_ID 1)

if (MSVC)
    add_compile_options(/W4)  # Use /W4 instead of -Wextra
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if (MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

add_compile_options(-g3 -pipe)
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
# ---- DEBUG ----
if (MSVC)
    message("Using MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /Zi)
    target_link_options(${PROJECT_NAME} PRIVATE /DEBUG)
endif()

# ---- Include paths ----
target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
        "${CMAKE_SOURCE_DIR}/src/graphics"
        "${CMAKE_SOURCE_DIR}/src/graphics/api"
        "${CMAKE_SOURCE_DIR}/src/util"
)

# ---- Nice IDE structure ----
source_group(TREE "${CMAKE_SOURCE_DIR}" FILES ${PROJECT_SOURCES} main.cpp)

# ---- Example install (optional) ----
# install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

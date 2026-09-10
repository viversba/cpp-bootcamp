cmake_minimum_required(VERSION 3.21)
project(Workshop1 LANGUAGES CXX)

# Force C++17 standard for compatibility with SFML and ImGui bindings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# -----------------------------------------------------------------------------
# 1. Fetch SFML (pinned to 2.6.1 to match the ImGui-SFML binding below)
# -----------------------------------------------------------------------------
FetchContent_Declare(
    SFML
    GIT_REPOSITORY [REPLACE URL HERE]
    GIT_TAG        2.6.1
)

set(SFML_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(SFML_BUILD_DOCS OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(SFML)

# -----------------------------------------------------------------------------
# 2. Fetch Core ImGui Source
# -----------------------------------------------------------------------------
FetchContent_Declare(
    imgui
    GIT_REPOSITORY [REPLACE URL HERE]
    GIT_TAG        v1.90.9
)

# Modern, non-deprecated population method for CMake 4.4+
FetchContent_MakeAvailable(imgui)

# Resolve the directory path variable using the standard generated properties
FetchContent_GetProperties(imgui SOURCE_DIR IMGUI_DIR_LOC)
set(IMGUI_DIR "${IMGUI_DIR_LOC}" CACHE PATH "Path to ImGui source" FORCE)

# -----------------------------------------------------------------------------
# 3. Fetch ImGui-SFML Binding
# -----------------------------------------------------------------------------
FetchContent_Declare(
    ImGui-SFML
    GIT_REPOSITORY [REPLACE URL HERE]
    GIT_TAG        v2.6.1
)

set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(ImGui-SFML)

# Use BUILD_INTERFACE so these paths aren't propagated to install(EXPORT ...),
# which would otherwise fail since they point inside the build tree.
target_include_directories(ImGui-SFML SYSTEM PUBLIC
    $<BUILD_INTERFACE:${sfml_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${IMGUI_DIR}>
)

# -----------------------------------------------------------------------------
# 4. Configure Executable
# -----------------------------------------------------------------------------
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML)
target_include_directories(${PROJECT_NAME} PRIVATE src)

# On Windows, SFML/ImGui-SFML are built as DLLs; copy them next to the exe so it can run.
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND_EXPAND_LISTS
    )
endif()

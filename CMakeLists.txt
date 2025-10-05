cmake_minimum_required(VERSION 3.16)

project(RPGCharacterSystem
  VERSION 1.0
  DESCRIPTION "An object-oriented C++ RPG character system featuring classes, abilities, leveling, factions, and combat logic."
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/data
)

file(GLOB_RECURSE SRC_FILES
  ${PROJECT_SOURCE_DIR}/Main.cpp
  ${PROJECT_SOURCE_DIR}/src/*.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

include(FetchContent)
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${PROJECT_SOURCE_DIR}/data $<TARGET_FILE_DIR:${PROJECT_NAME}>/data
)
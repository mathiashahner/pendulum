cmake_minimum_required(VERSION 3.20.6)
project(pendulum VERSION 0.1.0 LANGUAGES CXX)

### Configs
set(SDL2_DIR C:/dev/utils/SDL2)
set(SDL2_TTF_DIR C:/dev/utils/SDL2_ttf)

configure_file(${SDL2_DIR}/bin/SDL2.dll ${CMAKE_CURRENT_BINARY_DIR}/SDL2.dll COPYONLY)
configure_file(${SDL2_TTF_DIR}/bin/SDL2_ttf.dll ${CMAKE_CURRENT_BINARY_DIR}/SDL2_ttf.dll COPYONLY)

### Sources
file(GLOB SOURCES
  src/*.cpp
  src/text/*.cpp
  src/objects/*.cpp
)

add_executable(
  ${PROJECT_NAME}
  ${SOURCES}
)

### Includes
set(SDL2_INCLUDE_DIRS
  ${SDL2_DIR}/include
  ${SDL2_DIR}/include/SDL2
  ${SDL2_TTF_DIR}/include
  ${SDL2_TTF_DIR}/include/SDL2
)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
  include/
  include/text/
  include/objects/
  ${SDL2_INCLUDE_DIRS}
)

### Libraries
find_library(SDL2_LIBRARY
  NAMES libSDL2
  PATHS ${SDL2_DIR}/lib
)

find_library(SDL2_MAIN_LIBRARY
  NAMES libSDL2main
  PATHS ${SDL2_DIR}/lib
)

find_library(SDL2_TTF_LIBRARY
  NAMES libSDL2_ttf
  PATHS ${SDL2_TTF_DIR}/lib
)

if(NOT SDL2_LIBRARY)
  message(FATAL_ERROR "SDL2 not found")
elseif(NOT SDL2_MAIN_LIBRARY)
  message(FATAL_ERROR "SDL2main not found")
elseif(NOT SDL2_TTF_LIBRARY)
  message(FATAL_ERROR "SDL2_ttf not found")
else()
  message(STATUS "SDL2 found at ${SDL2_LIBRARY}")
  message(STATUS "SDL2main found at ${SDL2_MAIN_LIBRARY}")
  message(STATUS "SDL2_ttf found at ${SDL2_TTF_LIBRARY}")

  target_link_libraries(
    ${PROJECT_NAME}
    ${SDL2_LIBRARY}
    ${SDL2_MAIN_LIBRARY}
    ${SDL2_TTF_LIBRARY}
  )
endif()

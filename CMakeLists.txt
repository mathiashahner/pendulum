cmake_minimum_required(VERSION 3.20.6)
project(pendulum VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

### Sources
file(GLOB SOURCES
  src/*.cpp
  src/text/*.cpp
  src/objects/*.cpp
  src/pendulums/*.cpp
)

add_executable(
  ${PROJECT_NAME}
  ${SOURCES}
)

### Includes
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
  include/
  include/text/
  include/objects/
  include/pendulums/
  ${SDL2_INCLUDE_DIRS}
  ${SDL2_TTF_INCLUDE_DIRS}
)

### Libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(
  ${PROJECT_NAME}
  ${SDL2_LIBRARIES}
  ${SDL2_TTF_LIBRARIES}
)

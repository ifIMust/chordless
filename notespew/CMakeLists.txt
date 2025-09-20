cmake_minimum_required(VERSION 3.19)
project(notespew VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find ALSA
find_package(PkgConfig REQUIRED)
pkg_check_modules(ALSA REQUIRED alsa)

add_executable(notespew notespew.cc)
target_link_libraries(notespew PRIVATE ${ALSA_LIBRARIES})
target_include_directories(notespew PRIVATE ${ALSA_INCLUDE_DIRS})
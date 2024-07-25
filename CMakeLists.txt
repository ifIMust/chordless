cmake_minimum_required(VERSION 3.12)

project(chordless VERSION 0.5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)
add_compile_definitions(CHORDLESS_VERSION=${PROJECT_VERSION})

# Download google test every time we build... might not be the best way!
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/e39786088138f2749d64e9e90e0f9902daa77c40.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(CTest)
enable_testing()

find_package(Qt6 REQUIRED COMPONENTS Core Gui Test Widgets)
qt_standard_project_setup()
add_subdirectory(input)
add_subdirectory(chord)
add_subdirectory(note)

qt_add_executable(chordless main.cc)
target_link_libraries(chordless PRIVATE Qt6::Core Qt6::Widgets note_event note_reader note_state alsa_input full_voicing_observer scientific_note_namer chord_observer chord_matcher_reader chord_matcher_config_factory)

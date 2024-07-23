cmake_minimum_required(VERSION 3.12)

project(chordless LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

add_library(note_reader note_reader.cc note_reader.h)

include(CTest)

add_subdirectory(note)
add_subdirectory(alsa)

# Qt components follow
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()

add_subdirectory(ui)

qt_add_executable(chordless main.cc)
target_link_libraries(chordless PRIVATE Qt6::Core Qt6::Widgets note_event note_name note_reader note_state alsa_input chord_label full_voicing_observer)



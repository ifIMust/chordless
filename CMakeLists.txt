cmake_minimum_required(VERSION 3.12)

project(chordless)

set(CMAKE_CXX_STANDARD 14)
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


add_library(note_state note_state.cc note_state.h)

include(CTest)
add_executable(test_note_state test_note_state.cc)
target_link_libraries(test_note_state gtest_main note_state)
add_test(NAME note_state_test COMMAND test_note_state)



add_executable(chordless main.cpp)
target_link_libraries(chordless note_state)



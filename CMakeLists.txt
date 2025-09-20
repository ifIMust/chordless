cmake_minimum_required(VERSION 3.19)

project(chordless VERSION 0.8 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)
add_compile_definitions(CHORDLESS_VERSION=${PROJECT_VERSION})

# Configure static linking for standalone deployment
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBS OFF)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif()

# Set position independent code for all targets (needed for QML modules)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Download google test as needed
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the specific commit. Update this to use a newer version.
  URL https://github.com/google/googletest/archive/e39786088138f2749d64e9e90e0f9902daa77c40.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(CTest)
enable_testing()

find_package(Qt6 REQUIRED COMPONENTS Core Gui Test Quick Widgets)
qt_standard_project_setup()

# Find Boost with specific components
find_package(Boost REQUIRED COMPONENTS json program_options)
add_subdirectory(input)
add_subdirectory(note)
add_subdirectory(chord)
add_subdirectory(settings)

qt_add_executable(chordless main.cc)

# Add QML files as resources
qt_add_resources(chordless "qml"
    PREFIX "/qt/qml"
    FILES ui.qml
)

# Add resources for configuration files
qt_add_resources(chordless "config"
    PREFIX "/"
    FILES chords.json
)

target_link_libraries(chordless PRIVATE Qt6::Core Qt6::Widgets Qt6::Quick note_reader note_state alsa_input full_voicing_observer scientific_note_namer chord_observer chord_matcher_reader settings)

# Configure static linking and plugins for standalone deployment
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Import static plugins needed for QML and platform support
    qt_import_plugins(chordless
        INCLUDE Qt6::QXcbIntegrationPlugin Qt6::QSvgPlugin
    )
    # Strip symbols from release build:
    target_link_options(chordless PRIVATE -s)
    # Link statically against system libraries
    target_link_options(chordless PRIVATE -static-libgcc -static-libstdc++)
else()
    # Strip symbols from release build:
    target_link_options(chordless PRIVATE $<$<CONFIG:Release>: -s>)
endif()

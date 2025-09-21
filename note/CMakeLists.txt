add_library(basic_note_namer basic_note_namer.cc basic_note_namer.h note_namer.h)

add_executable(test_basic_note_namer test_basic_note_namer.cc)
target_link_libraries(test_basic_note_namer gtest_main basic_note_namer)
add_test(NAME basic_note_namer_test COMMAND test_basic_note_namer)

qt_add_qml_module(full_voicing_observer
    URI com.chordless.note_observer
    VERSION 1.0
    OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/com/chordless/note_observer
    RESOURCE_PREFIX /qt/qml
    SOURCES full_voicing_observer.cc full_voicing_observer.h note_observer.cc note_observer.h
)
target_link_libraries(full_voicing_observer PRIVATE Qt6::Core basic_note_namer scientific_note_namer note_observer)

add_executable(test_full_voicing_observer test_full_voicing_observer.cc)
target_link_libraries(test_full_voicing_observer PRIVATE Qt6::Core Qt6::Test gtest_main full_voicing_observer note_state note_observer scientific_note_namer)
add_test(NAME full_voicing_observer_test COMMAND test_full_voicing_observer)

add_library(note_event note_event.cc note_event.h)

add_executable(test_note_event test_note_event.cc)
target_link_libraries(test_note_event gtest_main note_event)
add_test(NAME note_event_test COMMAND test_note_event)

add_library(note_observer note_observer.cc note_observer.h)
target_link_libraries(note_observer PRIVATE Qt6::Core)

add_library(scientific_note_namer scientific_note_namer.cc scientific_note_namer.h note_namer.h)
target_link_libraries(scientific_note_namer basic_note_namer)

add_executable(test_scientific_note_namer test_scientific_note_namer.cc)
target_link_libraries(test_scientific_note_namer gtest_main scientific_note_namer)
add_test(NAME scientific_note_namer_test COMMAND test_scientific_note_namer)

add_library(note_reader note_reader.cc note_reader.h)
target_link_libraries(note_reader PRIVATE Qt6::Core)

add_library(note_state note_state.cc note_state.h)

add_executable(test_note_state test_note_state.cc)
target_link_libraries(test_note_state gtest_main note_state)
add_test(NAME note_state_test COMMAND test_note_state)

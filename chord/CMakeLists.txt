add_library(chord_matcher chord_matcher.cc chord_matcher.h chord_matcher_config.h)

add_executable(test_chord_matcher test_chord_matcher.cc)
target_link_libraries(test_chord_matcher gtest_main chord_matcher chord_matcher_config_factory note_state)
add_test(NAME chord_matcher_test COMMAND test_chord_matcher)

add_library(chord_matcher_config_factory chord_matcher_config_factory.cc chord_matcher_config_factory.h chord_matcher_config.h)

add_executable(test_chord_matcher_config_factory test_chord_matcher_config_factory.cc)
target_link_libraries(test_chord_matcher_config_factory gtest_main chord_matcher_config_factory)
add_test(NAME chord_matcher_config_factory_test COMMAND test_chord_matcher_config_factory)

add_library(chord_matcher_reader chord_matcher_reader.cc chord_matcher_reader.h)
target_link_libraries(chord_matcher_reader PRIVATE Qt6::Core Boost::json chord_matcher)

qt_add_qml_module(chord_observer
    URI com.chordless.chord_observer
    VERSION 1.0
    OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/com/chordless/chord_observer
    RESOURCE_PREFIX /qt/qml
    SOURCES chord_observer.cc chord_observer.h
)
target_link_libraries(chord_observer PRIVATE Qt6::Core chord_matcher note_observer basic_note_namer)

add_executable(test_chord_observer test_chord_observer.cc)
target_link_libraries(test_chord_observer PRIVATE Qt6::Core Qt6::Test gtest_main chord_observer note_state chord_matcher chord_matcher_config_factory)
add_test(NAME chord_observer_test COMMAND test_chord_observer)

add_library(full_voicing_observer full_voicing_observer.cc full_voicing_observer.h)
target_link_libraries(full_voicing_observer note_name)

add_executable(test_full_voicing_observer test_full_voicing_observer.cc)
target_link_libraries(test_full_voicing_observer gtest_main full_voicing_observer note_state)
add_test(NAME full_voicing_observer_test COMMAND test_full_voicing_observer)

add_library(note_event note_event.cc note_event.h)

add_executable(test_note_event test_note_event.cc)
target_link_libraries(test_note_event gtest_main note_event)
add_test(NAME note_event_test COMMAND test_note_event)

add_library(note_name note_name.cc note_name.h)

add_executable(test_note_name test_note_name.cc)
target_link_libraries(test_note_name gtest_main note_name)
add_test(NAME note_name_test COMMAND test_note_name)

add_library(note_reader note_reader.cc note_reader.h)

add_library(note_state note_state.cc note_state.h)

add_executable(test_note_state test_note_state.cc)
target_link_libraries(test_note_state gtest_main note_state)
add_test(NAME note_state_test COMMAND test_note_state)

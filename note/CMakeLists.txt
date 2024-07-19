add_library(note_event note_event.cc note_event.h)

add_executable(test_note_event test_note_event.cc)
target_link_libraries(test_note_event gtest_main note_event)
add_test(NAME note_event_test COMMAND test_note_event)

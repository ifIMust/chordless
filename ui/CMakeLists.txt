add_library(chord_label chord_label.cc chord_label.h)

target_link_libraries(chord_label PRIVATE note_state note_event note_name Qt6::Widgets)



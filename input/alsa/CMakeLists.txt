add_library(alsa_input alsa_input.cc alsa_input.h ../note_input.h)
target_link_libraries(alsa_input asound note_event)

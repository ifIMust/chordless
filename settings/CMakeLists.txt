qt_add_qml_module(settings URI com.chordless.settings VERSION 1.0 SOURCES settings.cc settings.h)
target_link_libraries(settings PRIVATE Qt6::Core Qt6::Quick Qt6::Widgets)

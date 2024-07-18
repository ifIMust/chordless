#include "note_event.h"
#include "note_name.h"
#include "note_state.h"
#include "alsa/alsa_input.h"
#include "ui/chord_label.h"

#include <QApplication>
#include <future>
#include <iostream>
#include <vector>

constexpr int window_w = 498;
constexpr int window_h = 64;
constexpr int label_x = 10;
constexpr int label_y = 10;
constexpr int label_w = window_w - label_x*2;
constexpr int label_h = window_h - label_y*2;

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  QWidget window;
  window.setFixedSize(window_w, window_h);

  chordless::alsa::AlsaInput alsa_input;
  if (!alsa_input.IsValid()) {
    std::cout << "Failed to open ALSA sequencer/port" << std::endl;
    exit(EXIT_FAILURE);
  }

  auto label = new chordless::ui::ChordLabel(&window, alsa_input);
  label->setGeometry(label_x, label_y, label_w, label_h);

  QFont font("Courier", 24);
  label->setFont(font);
  
  window.show();

  QObject::connect(&app, SIGNAL(aboutToQuit()), label, SLOT(Teardown()));
  
  return app.exec();
}

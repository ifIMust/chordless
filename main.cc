#include "alsa/alsa_input.h"
#include "note/full_voicing_observer.h"
#include "note/note_state.h"
#include "ui/chord_label.h"
#include "note_reader.h"

#include <QApplication>

#include <iostream>

constexpr int window_w = 498;
constexpr int window_h = 64;
constexpr int label_x = 10;
constexpr int label_y = 10;
constexpr int label_w = window_w - label_x*2;
constexpr int label_h = window_h - label_y*2;

int main(int argc, char **argv) {
  chordless::alsa::AlsaInput alsa_input;
  if (!alsa_input.IsValid()) {
    std::cerr << "Failed to open ALSA sequencer/port" << std::endl;
    exit(EXIT_FAILURE);
  }

  QApplication app(argc, argv);
  QWidget window;
  window.setFixedSize(window_w, window_h);

  auto label = new chordless::ui::ChordLabel(&window);
  label->setGeometry(label_x, label_y, label_w, label_h);

  QFont font("Courier", 24);
  label->setFont(font);

  chordless::note::NoteState note_state;
  chordless::note::FullVoicingObserver full_voicing(note_state, *label);
  chordless::NoteReader note_reader(alsa_input, note_state);
  note_reader.AddObserver(full_voicing);
  note_reader.Run();
  
  QObject::connect(&app, &QApplication::aboutToQuit, [&note_reader]() {
    note_reader.Stop();
  });
  
  window.show();
  return app.exec();
}

#include "chord/chord_matcher_reader.h"
#include "chord/chord_observer.h"
#include "input/alsa/alsa_input.h"
#include "note/full_voicing_observer.h"
#include "note/note_state.h"
#include "note/note_reader.h"
#include "note/scientific_note_namer.h"

#include <QApplication>
#include <QFont>
#include <QLabel>

#include <iostream>
#include <memory>
#include <utility>

constexpr int window_w = 498;
constexpr int window_h = 128;

constexpr int full_voice_label_x = 10;
constexpr int full_voice_label_y = 10;
constexpr int full_voice_label_w = window_w - full_voice_label_x*2;
constexpr int full_voice_label_h = static_cast<int>(window_h/2) - full_voice_label_y*2;

constexpr int chord_label_x = 10;
constexpr int chord_label_y = full_voice_label_y + full_voice_label_h + 10;
constexpr int chord_label_w = full_voice_label_w;
constexpr int chord_label_h = full_voice_label_h;

int main(int argc, char **argv) {
  std::cout << "chordless v" << CHORDLESS_VERSION << std::endl;
  
  chordless::alsa::AlsaInput alsa_input;
  if (!alsa_input.IsValid()) {
    std::cerr << "Failed to open ALSA sequencer/port" << std::endl;
    exit(EXIT_FAILURE);
  }

  QApplication app(argc, argv);
  QWidget window;
  window.setFixedSize(window_w, window_h);
  QFont mini_font("Helvetica", 10);

  auto all_notes_label = new QLabel(&window);
  all_notes_label->setGeometry(0, 0, full_voice_label_w, 10);
  all_notes_label->setFont(mini_font);
  all_notes_label->setText("All Notes");

  auto chords_label = new QLabel(&window);
  chords_label->setGeometry(0, chord_label_y - 10, chord_label_w, 10);
  chords_label->setFont(mini_font);
  chords_label->setText("Chords");
  
  QFont font("Helvetica", 24);
  auto full_voice_label = new QLabel(&window);
  full_voice_label->setGeometry(full_voice_label_x, full_voice_label_y, full_voice_label_w, full_voice_label_h);
  full_voice_label->setFont(font);
  full_voice_label->setText("Play to begin");

  auto chord_label = new QLabel(&window);
  chord_label->setGeometry(chord_label_x, chord_label_y, chord_label_w, chord_label_h);
  chord_label->setFont(font);

  chordless::note::NoteState note_state;
  chordless::note::NoteReader note_reader(alsa_input, note_state);

  chordless::note::FullVoicingObserver full_voicing(note_state);
  full_voicing.SetNoteNamer(std::make_unique<chordless::note::ScientificNoteNamer>());
  note_reader.AddObserver(full_voicing);
  QObject::connect(&full_voicing, SIGNAL(textChanged(const QString&)), full_voice_label, SLOT(setText(const QString&)));

  chordless::chord::ChordObserver chord_observer(note_state);
  chordless::chord::configureChordObserver(chord_observer, "../chord/config.json");
  note_reader.AddObserver(chord_observer);
  QObject::connect(&chord_observer, SIGNAL(textChanged(const QString&)), chord_label, SLOT(setText(const QString&)));

  note_reader.start();
  
  window.show();
  return app.exec();
}

#include "chord/chord_matcher_config_factory.h"
#include "chord/chord_matcher.h"
#include "chord/chord_observer.h"
#include "input/alsa/alsa_input.h"
#include "note/full_voicing_observer.h"
#include "note/note_state.h"
#include "note/note_reader.h"
#include "note/scientific_note_namer.h"
#include "ui/chord_label.h"

#include <QApplication>

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

void configureChordObserver(chordless::chord::ChordObserver &c) {
  chordless::chord::ChordMatcherConfigFactory config_factory;
  auto matcher(std::make_unique<chordless::chord::ChordMatcher>());
  matcher->SetConfig(config_factory.MakeConfig(chordless::chord::ChordType::MAJOR_TRIAD));
  c.AddMatcher(std::move(matcher));
}

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

  auto all_notes_label = new chordless::ui::ChordLabel(&window);
  all_notes_label->setGeometry(0, 0, full_voice_label_w, 10);
  all_notes_label->setFont(mini_font);
  all_notes_label->setText("All Notes");

  auto chords_label = new chordless::ui::ChordLabel(&window);
  chords_label->setGeometry(0, chord_label_y - 10, chord_label_w, 10);
  chords_label->setFont(mini_font);
  chords_label->setText("Chords");
  
  QFont font("Helvetica", 24);
  auto full_voice_label = new chordless::ui::ChordLabel(&window);
  full_voice_label->setGeometry(full_voice_label_x, full_voice_label_y, full_voice_label_w, full_voice_label_h);
  full_voice_label->setFont(font);

  auto chord_label = new chordless::ui::ChordLabel(&window);
  chord_label->setGeometry(chord_label_x, chord_label_y, chord_label_w, chord_label_h);
  chord_label->setFont(font);

  chordless::note::NoteState note_state;
  chordless::note::NoteReader note_reader(alsa_input, note_state);

  chordless::note::FullVoicingObserver full_voicing(note_state, *full_voice_label);
  full_voicing.SetNoteNamer(std::make_unique<chordless::note::ScientificNoteNamer>());
  note_reader.AddObserver(full_voicing);

  chordless::chord::ChordObserver chord_observer(note_state, *chord_label);
  configureChordObserver(chord_observer);
  note_reader.AddObserver(chord_observer);

  note_reader.Run();
  
  QObject::connect(&app, &QApplication::aboutToQuit, [&note_reader]() {
    note_reader.Stop();
  });
  
  window.show();
  return app.exec();
}

#include "chord/chord_matcher_reader.h"
#include "chord/chord_observer.h"
#include "input/alsa/alsa_input.h"
#include "note/full_voicing_observer.h"
#include "note/note_state.h"
#include "note/note_reader.h"
#include "note/scientific_note_namer.h"
#include "settings/settings.h"

#include <QApplication>
#include <QCoreApplication>
#include <QFont>
#include <QLabel>
#include <QQuickItem>
#include <QQuickView>
#include <QQmlEngine>

#include <iostream>
#include <memory>
#include <string>
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
  chordless::note::NoteState note_state;
  chordless::note::NoteReader note_reader(alsa_input, note_state);
  chordless::settings::Settings settings;
  
  chordless::note::FullVoicingObserver full_voicing(note_state);
  full_voicing.SetNoteNamer(std::make_unique<chordless::note::ScientificNoteNamer>());
  note_reader.AddObserver(full_voicing);
  
  chordless::chord::ChordObserver chord_observer(note_state);
  note_reader.AddObserver(chord_observer);
  
  int config_result = settings.ReadConfiguration(argc, argv);
  if (config_result != 0) {
    return config_result;
  }

  chordless::chord::configureChordObserver(chord_observer, settings.ChordsFile());

  note_reader.start();
    
  QQuickView view;

  // Add QML import paths for our modules relative to executable
  QQmlEngine *engine = view.engine();
  QString execDir = QCoreApplication::applicationDirPath();
  engine->addImportPath(execDir + "/note");
  engine->addImportPath(execDir + "/chord");
  engine->addImportPath(execDir + "/settings");
  view.setInitialProperties({
      {"note_obs", QVariant::fromValue(&full_voicing)},
      {"chord_obs", QVariant::fromValue(&chord_observer)},
      {"settings", QVariant::fromValue(&settings)}});
  view.setSource(QUrl("qrc:/qt/qml/ui.qml"));
  view.show();
  
  return app.exec();
}

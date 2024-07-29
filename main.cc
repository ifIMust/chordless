#include "chord/chord_matcher_reader.h"
#include "chord/chord_observer.h"
#include "input/alsa/alsa_input.h"
#include "note/full_voicing_observer.h"
#include "note/note_state.h"
#include "note/note_reader.h"
#include "note/scientific_note_namer.h"
#include "settings/settings.h"

#include <QApplication>
#include <QFont>
#include <QLabel>
#include <QQuickItem>
#include <QQuickView>

#include <boost/program_options.hpp>

#include <filesystem>
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

namespace po = boost::program_options;

int main(int argc, char **argv) {
  std::cout << "chordless v" << CHORDLESS_VERSION << std::endl;

  chordless::settings::Settings settings;
  
  po::options_description desc("Usage");
  desc.add_options()
    ("config,c", po::value<std::string>()->default_value("chords.json"),
     "specify location of chords file");
  
  po::variables_map vm;
  try {
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
  } catch (...) {
    std::cerr << desc << std::endl;
    return 1;
  }
  
  const auto chords_file = std::filesystem::absolute(vm["config"].as<std::string>());
  std::cout << "Using chord config file: " << chords_file << std::endl;
  
  chordless::alsa::AlsaInput alsa_input;
  if (!alsa_input.IsValid()) {
    std::cerr << "Failed to open ALSA sequencer/port" << std::endl;
    exit(EXIT_FAILURE);
  }

  QApplication app(argc, argv);
  chordless::note::NoteState note_state;
  chordless::note::NoteReader note_reader(alsa_input, note_state);

  chordless::note::FullVoicingObserver full_voicing(note_state);
  full_voicing.SetNoteNamer(std::make_unique<chordless::note::ScientificNoteNamer>());
  note_reader.AddObserver(full_voicing);
  QObject::connect(&settings, SIGNAL(SharpSettingChanged(bool)), &full_voicing, SLOT(SetSharp(bool)));
  
  chordless::chord::ChordObserver chord_observer(note_state);
  chordless::chord::configureChordObserver(chord_observer, chords_file);
  note_reader.AddObserver(chord_observer);
  
  note_reader.start();
  
  QQuickView view;
  qmlRegisterType<chordless::note::FullVoicingObserver>("com.chordless.note_observer", 1, 0, "NoteObserver");
  qmlRegisterType<chordless::chord::ChordObserver>("com.chordless.chord_observer", 1, 0, "ChordObserver");
  qmlRegisterType<chordless::settings::Settings>("com.chordless.settings", 1, 0, "Settings");
  view.setInitialProperties({
      {"note_obs", QVariant::fromValue(&full_voicing)},
      {"chord_obs", QVariant::fromValue(&chord_observer)},
      {"settings", QVariant::fromValue(&settings)}});
  view.setSource(QUrl::fromLocalFile("new_ui.qml"));
  view.show();
  auto root_object = view.rootObject();
  settings.ConnectToGui(*root_object);
  
  return app.exec();
}

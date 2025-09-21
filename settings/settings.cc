#include "settings.h"
#include "../logging.h"

#include <boost/program_options.hpp>

#include <filesystem>

namespace chordless::settings {
  int Settings::ReadConfiguration(int argc, char **argv) {
    namespace po = boost::program_options;
    po::options_description desc("Usage");
    desc.add_options()
      ("config,c", po::value<std::string>(),
       "specify location of chords file")
      ("sharp,s", po::value<bool>()->default_value(true),
       "prefer sharps or flats (boolean)")
      ("best-chord,b", po::value<bool>()->default_value(false),
       "show only the best chord match (boolean)");
  
    po::variables_map vm;
    try {
      po::store(po::parse_command_line(argc, argv, desc), vm);
      po::notify(vm);
    } catch (...) {
      LOG_ERROR(configCategory, "Invalid command line options. Usage information available with --help");
      return 1;
    }
    if (vm.count("config")) {
      // User provided a config file - make it absolute for local files
      chords_file_ = std::filesystem::absolute(vm["config"].as<std::string>());
      LOG_INFO(configCategory, "Using chord config file: ", chords_file_);
    } else {
      // Use embedded resource as default
      chords_file_ = ":/chords.json";
      LOG_INFO(configCategory, "Using default chord config");
    }

    sharp_ = vm["sharp"].as<bool>();
    best_chord_only_ = vm["best-chord"].as<bool>();

    // Set initial state for observers
    emit SharpChanged(sharp_);
    emit BestChordOnlyChanged(best_chord_only_);

    return 0;
  }

  const std::string& Settings::ChordsFile() const noexcept {
    return chords_file_;
  }

  bool Settings::Sharp() const noexcept {
    return sharp_;
  }

  void Settings::SetSharp(bool sharp) noexcept {
    sharp_ = sharp;
    emit SharpChanged(sharp_);
  }

  bool Settings::BestChordOnly() const noexcept {
    return best_chord_only_;
  }

  void Settings::SetBestChordOnly(bool best_chord_only) noexcept {
    best_chord_only_ = best_chord_only;
    emit BestChordOnlyChanged(best_chord_only_);
  }
}

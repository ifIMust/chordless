#include "settings.h"

#include <boost/program_options.hpp>

#include <iostream>
#include <filesystem>

namespace chordless::settings {
  int Settings::ReadConfiguration(int argc, char **argv) {
    namespace po = boost::program_options;
    po::options_description desc("Usage");
    desc.add_options()
      ("config,c", po::value<std::string>(),
       "specify location of chords file")
      ("sharp,s", po::value<bool>()->default_value(true),
       "prefer sharps or flats (boolean)");
  
    po::variables_map vm;
    try {
      po::store(po::parse_command_line(argc, argv, desc), vm);
      po::notify(vm);
    } catch (...) {
      std::cerr << desc << std::endl;
      return 1;
    }
    if (vm.count("config")) {
      // User provided a config file - make it absolute for local files
      chords_file_ = std::filesystem::absolute(vm["config"].as<std::string>());
      std::cout << "Using chord config file: " << chords_file_ << std::endl;
    } else {
      // Use embedded resource as default
      chords_file_ = ":/chords.json";
      std::cout << "Using default chord config" << std::endl;
    }

    sharp_ = vm["sharp"].as<bool>();

    // Set initial state for sharp observers
    emit sharpChanged(sharp_);
    
    return 0;
  }

  const std::string& Settings::ChordsFile() const noexcept {
    return chords_file_;
  }
  
  bool Settings::sharp() const noexcept {
    return sharp_;
  }

  void Settings::setSharp(bool sharp) noexcept {
    sharp_ = sharp;
    emit sharpChanged(sharp_);
  }
}

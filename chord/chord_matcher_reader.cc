#include "chord_matcher_reader.h"

#include "chord_matcher.h"
#include "chord_matcher_config.h"
#include "chord_observer.h"
#include "chord_pattern.h"

#include <boost/json.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>

namespace chordless::chord {
  void configureChordObserver(ChordObserver &observer, const std::string &file_name) {
    // Slurp the file into a string/buffer
    std::ifstream file(file_name);
    if (!file.is_open()) {
      std::cerr << "Failed to read config file\n";
      return;
    }

    const auto size = std::filesystem::file_size(file_name);
    std::string json_data(size, '\0');
    if (file.read(json_data.data(), size)) {
      try {
	using namespace boost::json;
	auto value = parse(json_data);
	auto obj = value.as_object();
	auto chord_arr = obj.at("chords").as_array();
	for (auto chord : chord_arr) {
	  auto cfg = std::make_unique<ChordMatcherConfig>();
	  auto chord_obj = chord.as_object();
	  cfg->name = chord_obj.at("name").as_string();
	  cfg->suffix = chord_obj.at("suffix").as_string();
	  cfg->tonic = static_cast<unsigned char>(chord_obj.at("tonic").as_int64());
	  auto patterns = chord_obj.at("patterns").as_array();
	  for (auto pattern : patterns) {
	    auto pat_obj = pattern.as_object();
	    ChordPattern chord_pattern;
	    chord_pattern.num_notes = pat_obj.at("num_notes").as_int64();
	    auto notes = pat_obj.at("notes").as_array();
	    for (auto n : notes) {
	      chord_pattern.pattern.set(n.as_int64());
	    }
	    cfg->patterns.push_back(std::move(chord_pattern));
	  }
	  auto matcher = std::make_unique<ChordMatcher>();
	  matcher->SetConfig(std::move(cfg));
	  observer.AddMatcher(std::move(matcher));
	}
      } catch (const std::exception &e) {
	std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
      }
    } else {
      std::cerr << "Failed to read file data as a string\n";
    }
  }
}

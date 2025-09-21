#include "chord_matcher_reader.h"
#include "../logging.h"

#include "chord_matcher.h"
#include "chord_matcher_config.h"
#include "chord_observer.h"
#include "chord_pattern.h"

#include <boost/json.hpp>

#include <QFile>
#include <QFileInfo>
#include <memory>

namespace chordless::chord {
  void ConfigureChordObserver(ChordObserver &observer, const std::string &file_name) {
    // Load chord configuration from file (supports qrc:// resources)
    QFile file(QString::fromStdString(file_name));
    if (!file.open(QIODevice::ReadOnly)) {
      LOG_ERROR(configCategory, "Failed to read chord config file:" << file_name);
      return;
    }

    QByteArray file_data = file.readAll();
    std::string json_data = file_data.toStdString();
    if (!json_data.empty()) {
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
        LOG_ERROR(configCategory, "Failed to parse chord configuration JSON:" << e.what());
      }
    } else {
      LOG_ERROR(configCategory, "Chord configuration file is empty");
    }
  }
}

#pragma once

#include "chord.h"

#include "chord_matcher_config.h"
#include "../note/note_constant.h"
#include "../note/note_namer.h"

#include <memory>
#include <vector>

namespace chordless {
  namespace note {
    class NoteState;
  }
  
  namespace chord {
    class ChordMatcher {
    public:
      ChordMatcher();
      
      std::vector<Chord> MatchRooted(const std::bitset<::chordless::note::kNumNotes> &rooted_notes,
				     unsigned char root_note, unsigned char num_notes) noexcept;

      void SetConfig(std::unique_ptr<ChordMatcherConfig> &&config);
      
    private:
      std::unique_ptr<ChordMatcherConfig> config_;
      std::unique_ptr<note::NoteNamer> note_namer_;
    };
  }
}

#pragma once

#include "chord.h"

#include "../note/note_namer.h"

#include <memory>
#include <vector>

namespace chordless {
  namespace note {
    class NoteState;
  }
  
  namespace chord {
    struct ChordMatcherConfig;
    
    class ChordMatcher {
    public:
      ChordMatcher();
      
      std::vector<Chord> Match(const note::NoteState&) noexcept;

      void SetConfig(std::unique_ptr<ChordMatcherConfig> &&config);
      
    private:
      std::unique_ptr<ChordMatcherConfig> config_;
      std::unique_ptr<note::NoteNamer> note_namer_;
    };
  }
}

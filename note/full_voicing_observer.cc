#include "full_voicing_observer.h"

#include "basic_note_namer.h"
#include "note_state.h"

#include <sstream>
#include <string>
#include <vector>

namespace chordless::note {
  FullVoicingObserver::FullVoicingObserver(const NoteState &ns) :
    note_state_(ns), note_namer_(std::make_unique<BasicNoteNamer>())
  {}

  void FullVoicingObserver::Observe() noexcept {
    std::vector<unsigned char> notes;
    note_state_.GetNotes(notes);

    std::ostringstream ss;
    for (auto n : notes) {
      ss << note_namer_->Name(n, true) << " ";
    }
    emit textChanged(QString(ss.str().c_str()));
  }

  void FullVoicingObserver::SetNoteNamer(std::unique_ptr<NoteNamer> &&n) noexcept {
    note_namer_ = std::move(n);
  }
}

#include "full_voicing_observer.h"

#include "basic_note_namer.h"
#include "scientific_note_namer.h"
#include "note_state.h"

#include <sstream>
#include <string>
#include <vector>

namespace chordless::note {
  FullVoicingObserver::FullVoicingObserver(const NoteState &ns) :
    note_state_(ns), note_namer_(std::make_unique<BasicNoteNamer>())
  {}

  void FullVoicingObserver::OnNoteChange() noexcept {
    std::vector<unsigned char> notes;
    note_state_.GetNotes(notes);

    std::ostringstream ss;
    for (auto n : notes) {
      ss << note_namer_->Name(n, true) << " ";
    }
    text_ = QString(ss.str().c_str());
    emit textChanged();
  }

  void FullVoicingObserver::SetNoteNamer(std::unique_ptr<NoteNamer> &&n) noexcept {
    note_namer_ = std::move(n);
  }

  void FullVoicingObserver::SetSharp(bool sharp) noexcept {
    note_namer_->SetSharp(sharp);
  }
}

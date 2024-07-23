#include "full_voicing_observer.h"

#include "basic_note_namer.h"
#include "note_state.h"
#include "../ui/text_setter.h"


#include <sstream>
#include <string>
#include <vector>

namespace chordless::note {
  FullVoicingObserver::FullVoicingObserver(NoteState &ns, chordless::ui::TextSetter &ts) :
    note_state_(ns), text_setter_(ts), note_namer_(new BasicNoteNamer())
  {}

  void FullVoicingObserver::Observe() noexcept {
    std::vector<unsigned char> notes;
    note_state_.GetNotes(notes);

    std::ostringstream ss;
    for (auto n : notes) {
      ss << note_namer_->Name(n, true) << " ";
    }
    text_setter_.SetText(ss.str());
  }

  void FullVoicingObserver::SetNoteNamer(std::unique_ptr<NoteNamer> &&n) noexcept {
    note_namer_ = std::move(n);
  }
}

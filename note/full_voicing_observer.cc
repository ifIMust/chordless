#include "full_voicing_observer.h"
#include "../ui/text_setter.h"
#include "../note_name.h"
#include "../note_state.h"

#include <sstream>
#include <string>
#include <vector>

namespace chordless {
  namespace note {
    FullVoicingObserver::FullVoicingObserver(chordless::NoteState &ns, chordless::ui::TextSetter &ts) :
      note_state_(ns), text_setter_(ts)
    {}

    void FullVoicingObserver::Observe() noexcept {
      std::vector<unsigned char> notes;
      note_state_.GetNotes(notes);

      std::ostringstream ss;
      for (auto n : notes) {
	ss << chordless::NoteName::Name(n, false) << " ";
      }
      text_setter_.SetText(ss.str());
    }
  }
}

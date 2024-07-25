#pragma once

#include <QThread>

#include <functional>
#include <vector>

namespace chordless {
  namespace input {
    class NoteInput;
  }

  namespace note {
    class NoteObserver;
    class NoteState;
  
    class NoteReader : public QThread {
      Q_OBJECT
      
    public:
      NoteReader(input::NoteInput &, NoteState &);
      ~NoteReader();

      void run() override;

      void AddObserver(NoteObserver&);

    signals:
      void noteChange();

    private:
      input::NoteInput &note_input_;
      NoteState &note_state_;

      std::atomic<bool> read_input_;

      std::vector<std::reference_wrapper<NoteObserver>> observers_;
    };
  }
}

#pragma once

#include "../note/note_observer.h"

#include "chord_matcher.h"
#include "../note/note_namer.h"

#include <QtQml/qqmlregistration.h>
#include <QString>

#include <memory>
#include <vector>

namespace chordless {
  namespace note {
    class NoteState;
  }

  namespace chord {
    class ChordObserver : public ::chordless::note::NoteObserver
    {
      Q_OBJECT
      QML_ELEMENT
      Q_PROPERTY(QString text READ text NOTIFY textChanged)

    public:
      explicit ChordObserver(::chordless::note::NoteState &note_state);
    
      void OnNoteChange() noexcept override;
      void SetSharp(bool) noexcept override;
      
      void AddMatcher(std::unique_ptr<ChordMatcher> &&matcher);

      static std::bitset<::chordless::note::kNumNotes> UniqueNotes(const std::bitset<::chordless::note::kNumNotes> &n);

      QString text() const { return text_; }
      
      ChordObserver(const ChordObserver&) = delete;
      ChordObserver& operator=(const ChordObserver&) = delete;

    // signals:
    //   void TextChanged();
    
    private:
      std::vector<std::unique_ptr<ChordMatcher>> matchers_;
      const ::chordless::note::NoteState &note_state_;
      std::unique_ptr<note::NoteNamer> note_namer_;
      QString text_;
    };
  }
}

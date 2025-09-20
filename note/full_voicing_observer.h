#pragma once

#include "note_observer.h"

#include "note_namer.h"

#include <QtQml/qqmlregistration.h>
#include <QString>

#include <memory>

namespace chordless {
  namespace note {
    class NoteState;    
    
    class FullVoicingObserver : public NoteObserver {
      Q_OBJECT
      QML_ELEMENT
      QML_UNCREATABLE("FullVoicingObserver must be created in C++")
      Q_PROPERTY(QString text READ text NOTIFY textChanged)

    public:
      explicit FullVoicingObserver(const NoteState&);

      void OnNoteChange() noexcept override;
      Q_INVOKABLE void SetSharp(bool) noexcept;

      void SetNoteNamer(std::unique_ptr<NoteNamer>&&) noexcept;

      QString text() const { return text_; }

      FullVoicingObserver(const FullVoicingObserver&) = delete;
      FullVoicingObserver& operator=(const FullVoicingObserver&) = delete;
      
    private:
      const NoteState& note_state_;
      std::unique_ptr<NoteNamer> note_namer_;

      QString text_;
    };
  }
}

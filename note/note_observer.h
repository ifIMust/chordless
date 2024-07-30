#pragma once

#include <QObject>

namespace chordless::note {
  class NoteObserver : public QObject {
    Q_OBJECT
    
  public:
    virtual ~NoteObserver();

  public slots:
    virtual void OnNoteChange() noexcept = 0;
    
  signals:
      void textChanged();
  };
}

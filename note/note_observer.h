#pragma once

#include <QObject>

namespace chordless::note {
  class NoteObserver : public QObject {
    Q_OBJECT
    
  public:
    virtual void Observe() noexcept = 0;

    virtual ~NoteObserver();

  signals:
      virtual void textChanged(const QString &);
  };
}

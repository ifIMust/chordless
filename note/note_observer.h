#pragma once

#include <QObject>
#include <QtQml/qqmlregistration.h>

namespace chordless::note {
  class NoteObserver : public QObject {
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("NoteObserver is abstract")
    
  public:
    virtual ~NoteObserver();

  public slots:
    virtual void OnNoteChange() noexcept = 0;
    
  signals:
      void textChanged();
  };
}

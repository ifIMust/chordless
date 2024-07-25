#include "full_voicing_observer.h"

#include "note_state.h"
#include "../ui/mock/mock_text_setter.h"

#include <QSignalSpy>

#include <gtest/gtest.h>
#include <string>

class FullVoicingObserverTest : public testing::Test {
public:
  FullVoicingObserverTest() :
    observer(note_state),
    spy(&observer, SIGNAL(textChanged(const QString&)))
  {}
  
protected:
  chordless::note::NoteState note_state;
  chordless::note::FullVoicingObserver observer;
  QSignalSpy spy;
};

TEST_F(FullVoicingObserverTest, Empty) {
  observer.Observe();
  ASSERT_EQ(1, spy.count());
  QList<QVariant> arguments = spy.takeFirst();
  EXPECT_EQ(0, arguments.at(0).toString().size());
}

TEST_F(FullVoicingObserverTest, OneNote) {
  QString expected("C ");
  note_state.NoteOn(0);
  observer.Observe();
  ASSERT_EQ(1, spy.count());
  QList<QVariant> arguments = spy.takeFirst();
  EXPECT_EQ(expected, arguments.at(0).toString());
}

TEST_F(FullVoicingObserverTest, ThreeNote) {
  QString expected("C E G ");
  note_state.NoteOn(0);
  note_state.NoteOn(16);
  note_state.NoteOn(31);
  observer.Observe();
  ASSERT_EQ(1, spy.count());
  QList<QVariant> arguments = spy.takeFirst();
  EXPECT_EQ(expected, arguments.at(0).toString());
}

TEST_F(FullVoicingObserverTest, Reobserve) {
  QString expected("C G ");
  note_state.NoteOn(0);
  note_state.NoteOn(16);
  note_state.NoteOn(31);
  observer.Observe();

  note_state.NoteOff(16);
  observer.Observe();

  ASSERT_EQ(2, spy.count());
  QList<QVariant> arguments = spy.takeLast();
  EXPECT_EQ(expected, arguments.at(0).toString());
}

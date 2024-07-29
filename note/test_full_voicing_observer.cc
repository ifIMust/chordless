#include "full_voicing_observer.h"

#include "note_state.h"

#include <QSignalSpy>

#include <gtest/gtest.h>
#include <string>

class FullVoicingObserverTest : public testing::Test {
public:
  FullVoicingObserverTest() :
    observer(note_state),
    spy(&observer, SIGNAL(textChanged()))
  {}
  
protected:
  chordless::note::NoteState note_state;
  chordless::note::FullVoicingObserver observer;
  QSignalSpy spy;
};

TEST_F(FullVoicingObserverTest, Empty) {
  observer.OnNoteChange();
  ASSERT_EQ(1, spy.count());
  EXPECT_EQ(0, observer.text().size());
}

TEST_F(FullVoicingObserverTest, OneNote) {
  QString expected("C ");
  note_state.NoteOn(0);
  observer.OnNoteChange();
  ASSERT_EQ(1, spy.count());
  QList<QVariant> arguments = spy.takeFirst();
  EXPECT_EQ(expected, observer.text());
}

TEST_F(FullVoicingObserverTest, ThreeNote) {
  QString expected("C E G ");
  note_state.NoteOn(0);
  note_state.NoteOn(16);
  note_state.NoteOn(31);
  observer.OnNoteChange();
  ASSERT_EQ(1, spy.count());
  EXPECT_EQ(expected, observer.text());
}

TEST_F(FullVoicingObserverTest, Reobserve) {
  QString expected("C G ");
  note_state.NoteOn(0);
  note_state.NoteOn(16);
  note_state.NoteOn(31);
  observer.OnNoteChange();

  note_state.NoteOff(16);
  observer.OnNoteChange();

  ASSERT_EQ(2, spy.count());
  EXPECT_EQ(expected, observer.text());
}

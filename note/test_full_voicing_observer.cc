#include "full_voicing_observer.h"

#include "note_state.h"
#include "scientific_note_namer.h"

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

TEST_F(FullVoicingObserverTest, SetNoteNamer) {
  // Start with BasicNoteNamer (default), test with C4 (MIDI note 60)
  note_state.NoteOn(60);
  observer.OnNoteChange();
  QString basic_result = observer.text();
  EXPECT_EQ(QString("C "), basic_result);  // BasicNoteNamer: just "C"

  // Switch to ScientificNoteNamer
  observer.SetNoteNamer(std::make_unique<chordless::note::ScientificNoteNamer>());
  observer.OnNoteChange();
  QString scientific_result = observer.text();
  EXPECT_EQ(QString("C₄ "), scientific_result);  // ScientificNoteNamer: "C₄"
}

TEST_F(FullVoicingObserverTest, SetSharp) {
  // Test with F# (MIDI note 66: 66 % 12 = 6)
  note_state.NoteOn(66);

  // Default should use sharps
  observer.OnNoteChange();
  EXPECT_EQ(QString("F♯ "), observer.text());

  // Switch to flats
  observer.SetSharp(false);
  observer.OnNoteChange();
  EXPECT_EQ(QString("G♭ "), observer.text());

  // Switch back to sharps
  observer.SetSharp(true);
  observer.OnNoteChange();
  EXPECT_EQ(QString("F♯ "), observer.text());
}

TEST_F(FullVoicingObserverTest, CMajorTriad) {
  // C Major triad: C-E-G (MIDI notes 60, 64, 67)
  note_state.NoteOn(60);  // C4
  note_state.NoteOn(64);  // E4
  note_state.NoteOn(67);  // G4
  observer.OnNoteChange();

  // Notes should be displayed in the order they were activated
  EXPECT_EQ(QString("C E G "), observer.text());
}

TEST_F(FullVoicingObserverTest, FMajor7thChord) {
  // F Major 7th chord: F-A-C-E (MIDI notes 65, 69, 72, 76)
  note_state.NoteOn(65);  // F4
  note_state.NoteOn(69);  // A4
  note_state.NoteOn(72);  // C5
  note_state.NoteOn(76);  // E5
  observer.OnNoteChange();

  EXPECT_EQ(QString("F A C E "), observer.text());
}

TEST_F(FullVoicingObserverTest, DMinorChordWithScientificNotation) {
  // D minor chord with scientific notation: D-F-A (MIDI notes 62, 65, 69)
  observer.SetNoteNamer(std::make_unique<chordless::note::ScientificNoteNamer>());

  note_state.NoteOn(62);  // D4
  note_state.NoteOn(65);  // F4
  note_state.NoteOn(69);  // A4
  observer.OnNoteChange();

  EXPECT_EQ(QString("D₄ F₄ A₄ "), observer.text());
}

TEST_F(FullVoicingObserverTest, ComplexChordWithSharpsAndFlats) {
  // Test a chord with both sharps and flats preferences
  // C# diminished chord: C#-E-G (MIDI notes 61, 64, 67)
  note_state.NoteOn(61);  // C#4/Db4
  note_state.NoteOn(64);  // E4
  note_state.NoteOn(67);  // G4

  // Test with sharps
  observer.SetSharp(true);
  observer.OnNoteChange();
  EXPECT_EQ(QString("C♯ E G "), observer.text());

  // Test with flats
  observer.SetSharp(false);
  observer.OnNoteChange();
  EXPECT_EQ(QString("D♭ E G "), observer.text());
}

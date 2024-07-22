#include "note_state.h"

#include <gtest/gtest.h>
#include <vector>

TEST(NoteStateTest, NumNotesOnInitial) {
  chordless::note::NoteState noteState;
  ASSERT_EQ(0, noteState.NumNotesOn());
}

TEST(NoteStateTest, NumNotesOnWithValidNote) {
  chordless::note::NoteState noteState;
  noteState.NoteOn(0);
  ASSERT_EQ(1, noteState.NumNotesOn());
}

TEST(NoteStateTest, NoteOnWithInvalidNote) {
  chordless::note::NoteState noteState;
  ASSERT_THROW(noteState.NoteOn(128), std::out_of_range);
  ASSERT_EQ(0, noteState.NumNotesOn());
}

TEST(NoteStateTest, NumNotesOnCmajCadence) {
  chordless::note::NoteState noteState;
  noteState.NoteOn(0x3C);
  noteState.NoteOn(0x40);
  noteState.NoteOn(0x43);
  noteState.NoteOn(0x4E);
  ASSERT_EQ(4, noteState.NumNotesOn());
}

TEST(NoteStateTest, NumNotesOnRepeats) {
  chordless::note::NoteState noteState;
  noteState.NoteOn(0x3C);
  noteState.NoteOn(0x40);
  noteState.NoteOn(0x3C);
  noteState.NoteOn(0x40);
  ASSERT_EQ(2, noteState.NumNotesOn());
}

TEST(NoteStateTest, NumNotesOnNoteOffInit) {
  chordless::note::NoteState noteState;
  noteState.NoteOff(0);
  ASSERT_EQ(0, noteState.NumNotesOn());
}

TEST(NoteStateTest, NumNotesOnNoteOnOff) {
  chordless::note::NoteState noteState;
  noteState.NoteOn(0);
  noteState.NoteOff(0);
  ASSERT_EQ(0, noteState.NumNotesOn());
}

TEST(NoteStateTest, NoteOffWithInvalidNote) {
  chordless::note::NoteState noteState;
  ASSERT_THROW(noteState.NoteOff(128), std::out_of_range);
}

TEST(NoteStateTest, GetNotesNone) {
  chordless::note::NoteState noteState;
  std::vector<unsigned char> notes;
  noteState.GetNotes(notes);
  EXPECT_EQ(0, notes.size());
}

TEST(NoteStateTest, GetNotesSizeOne) {
  chordless::note::NoteState noteState;
  std::vector<unsigned char> notes;
  noteState.NoteOn(42);
  noteState.GetNotes(notes);
  ASSERT_EQ(1, notes.size());
  EXPECT_EQ(42, notes[0]);
}

TEST(NoteStateTest, GetNotesCMajCadence) {
  chordless::note::NoteState noteState;
  const std::vector<unsigned char> expected{0x3C, 0x40, 0x43, 0x4E};
  std::vector<unsigned char> notes;
  noteState.NoteOn(0x3C);
  noteState.NoteOn(0x40);
  noteState.NoteOn(0x43);
  noteState.NoteOn(0x4E);
  noteState.GetNotes(notes);
  EXPECT_EQ(expected, notes);
}

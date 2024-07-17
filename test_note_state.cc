#include "note_state.h"

#include <gtest/gtest.h>

TEST(NoteStateTest, NumNotesOnInitial) {
  chordless::NoteState noteState;
  ASSERT_EQ(0, noteState.NumNotesOn());
}

TEST(NoteStateTest, NumNotesOnWithValidNote) {
  chordless::NoteState noteState;
  noteState.NoteOn(0);
  ASSERT_EQ(1, noteState.NumNotesOn());
}

TEST(NoteStateTest, NoteOnWithInvalidNote) {
  chordless::NoteState noteState;
  ASSERT_THROW(noteState.NoteOn(128), std::out_of_range);
  ASSERT_EQ(0, noteState.NumNotesOn());
}

TEST(NoteStateTest, NumNotesOnCmajCadence) {
  chordless::NoteState noteState;
  noteState.NoteOn(0x3C);
  noteState.NoteOn(0x40);
  noteState.NoteOn(0x43);
  noteState.NoteOn(0x4E);
  ASSERT_EQ(4, noteState.NumNotesOn());
}

TEST(NoteStateTest, NumNotesOnRepeats) {
  chordless::NoteState noteState;
  noteState.NoteOn(0x3C);
  noteState.NoteOn(0x40);
  noteState.NoteOn(0x3C);
  noteState.NoteOn(0x40);
  ASSERT_EQ(2, noteState.NumNotesOn());
}

TEST(NoteStateTest, NumNotesOnNoteOffInit) {
  chordless::NoteState noteState;
  noteState.NoteOff(0);
  ASSERT_EQ(0, noteState.NumNotesOn());
}

TEST(NoteStateTest, NumNotesOnNoteOnOff) {
  chordless::NoteState noteState;
  noteState.NoteOn(0);
  noteState.NoteOff(0);
  ASSERT_EQ(0, noteState.NumNotesOn());
}

TEST(NoteStateTest, NoteOffWithInvalidNote) {
  chordless::NoteState noteState;
  ASSERT_THROW(noteState.NoteOff(128), std::out_of_range);
}

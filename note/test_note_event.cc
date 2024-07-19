#include "note_event.h"

#include <gtest/gtest.h>

TEST(NoteEventTest, DefaultConstructor) {
  chordless::note::NoteEvent e;
  EXPECT_EQ(chordless::note::NoteEventType::NONE, e.type_);
}

TEST(NoteEventTest, NoteOnVelOne) {
  chordless::note::NoteEvent e(true, 0x77, 0x01);
  EXPECT_EQ(chordless::note::NoteEventType::NOTE_ON, e.type_);
}

TEST(NoteEventTest, NoteOnVelZero) {
  chordless::note::NoteEvent e(true, 0x77, 0x00);
  EXPECT_EQ(chordless::note::NoteEventType::NOTE_OFF, e.type_);
}

TEST(NoteEventTest, NoteOffVelNonZero) {
  chordless::note::NoteEvent e(false, 0x77, 0x0F);
  EXPECT_EQ(chordless::note::NoteEventType::NOTE_OFF, e.type_);
}

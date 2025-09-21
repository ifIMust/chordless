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

TEST(NoteEventTest, MoveConstructor) {
  chordless::note::NoteEvent source(true, 0x60, 0x7F);
  chordless::note::NoteEvent moved(std::move(source));
  EXPECT_EQ(chordless::note::NoteEventType::NOTE_ON, moved.type_);
  EXPECT_EQ(0x60, moved.note_);
}

TEST(NoteEventTest, MoveAssignment) {
  chordless::note::NoteEvent source(false, 0x64, 0x40);
  chordless::note::NoteEvent target;
  target = std::move(source);
  EXPECT_EQ(chordless::note::NoteEventType::NOTE_OFF, target.type_);
  EXPECT_EQ(0x64, target.note_);
}

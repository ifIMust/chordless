#include "note_event.h"

#include <gtest/gtest.h>

TEST(NoteEventTest, NoteOnVelOne) {
  chordless::NoteEvent e(true, 0x77, 0x01);
  EXPECT_TRUE(e.on_);
}

TEST(NoteEventTest, NoteOnVelZero) {
  chordless::NoteEvent e(true, 0x77, 0x00);
  EXPECT_FALSE(e.on_);
}

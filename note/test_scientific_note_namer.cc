#include "scientific_note_namer.h"

#include <gtest/gtest.h>
#include <string>

TEST(ScientificNoteNamerTest, NameMiddleC) {
  chordless::note::ScientificNoteNamer namer;
  ASSERT_EQ(std::string("C\u2084"), namer.Name(0x3c, true));
}

// The highest note on a standard 88-key piano
TEST(ScientificNoteNamerTest, NameHighestC) {
  chordless::note::ScientificNoteNamer namer;
  ASSERT_EQ(std::string("C\u2088"), namer.Name(0x6c, true));
}

// The lowest note on a standard 88-key piano
TEST(ScientificNoteNamerTest, NameLowestA) {
  chordless::note::ScientificNoteNamer namer;
  ASSERT_EQ(std::string("A\u2080"), namer.Name(0x15, true));
}

// C0 note
TEST(ScientificNoteNamerTest, NameCZero) {
  chordless::note::ScientificNoteNamer namer;
  ASSERT_EQ(std::string("C\u2080"), namer.Name(0x0c, true));
}

// C9 note
TEST(ScientificNoteNamerTest, NameCNine) {
  chordless::note::ScientificNoteNamer namer;
  ASSERT_EQ(std::string("C\u2089"), namer.Name(0x78, true));
}

// Lowest MIDI note
TEST(ScientificNoteNamerTest, NameLowestNote) {
  chordless::note::ScientificNoteNamer namer;
  ASSERT_EQ(std::string("C\u208B\u2081"), namer.Name(0x00, true));
}

// Highest MIDI note
TEST(ScientificNoteNamerTest, NameHighestNote) {
  chordless::note::ScientificNoteNamer namer;
  ASSERT_EQ(std::string("G\u2089"), namer.Name(0x7F, true));
}

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

// Test octave 2 (common musical range)
TEST(ScientificNoteNamerTest, NameOctave2) {
  chordless::note::ScientificNoteNamer namer;
  ASSERT_EQ(std::string("C\u2082"), namer.Name(0x24, true));  // MIDI note 36 (C2)
}

// Test SetSharp functionality with flats
TEST(ScientificNoteNamerTest, SetSharpFunctionality) {
  chordless::note::ScientificNoteNamer namer;
  namer.SetSharp(false);
  ASSERT_EQ(std::string("B\u266D\u2084"), namer.Name(0x46, false));  // MIDI note 70 (A#4/Bb4)
}

// Test extreme octave values (beyond normal MIDI range)
TEST(ScientificNoteNamerTest, ExtremeOctaveValue) {
  chordless::note::ScientificNoteNamer namer;
  // MIDI note 255 would give octave = (255/12) - 1 = 20
  // 255 % 12 = 3, which is D♯/E♭, so result should be "D♯₂₀"
  ASSERT_EQ(std::string("D♯\u2082\u2080"), namer.Name(0xFF, true));
}

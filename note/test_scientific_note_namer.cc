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

// Test octave containing digit 3 (octave 13)
TEST(ScientificNoteNamerTest, OctaveWithDigit3) {
  chordless::note::ScientificNoteNamer namer;
  // MIDI note 168 gives octave = (168/12) - 1 = 13
  // 168 % 12 = 0, which is C, so result should be "C₁₃"
  ASSERT_EQ(std::string("C\u2081\u2083"), namer.Name(168, true));
}

// Test octave containing digit 5 (octave 15)
TEST(ScientificNoteNamerTest, OctaveWithDigit5) {
  chordless::note::ScientificNoteNamer namer;
  // For octave 15: MIDI note = (15 + 1) * 12 = 192
  // 192 % 12 = 0, which is C
  ASSERT_EQ(std::string("C\u2081\u2085"), namer.Name(192, true));
}

// Test octave containing digits 6 and 7 (octave 16 and 17)
TEST(ScientificNoteNamerTest, OctaveWithDigits67) {
  chordless::note::ScientificNoteNamer namer;
  // For octave 16: MIDI note = (16 + 1) * 12 = 204
  // 204 % 12 = 0, which is C, so result should be "C₁₆"
  ASSERT_EQ(std::string("C\u2081\u2086"), namer.Name(204, true));

  // For octave 17: MIDI note = (17 + 1) * 12 = 216
  // 216 % 12 = 0, which is C, so result should be "C₁₇"
  ASSERT_EQ(std::string("C\u2081\u2087"), namer.Name(216, true));
}

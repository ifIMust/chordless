#pragma once

class NoteState {
public:
  // Note On
  // Status:   0x9Z where Z is channel
  // Data:     0x00 to 0x7F for the note number. 0x3C is middle C.
  // Velocity: 0x00 to 0x7f. If 0, treat as a Note Off.
  void noteOn(unsigned char note);

  // Same as Note On, but Status is 0x8Z
  void noteOff(unsigned char note);
};

# chordless
## Description
chordless is a MIDI note analyzer that runs on Linux.
Any modern Linux version (i.e. with ALSA) should work.

The initial project goals are partially completed.

### Project Goals
- Display currently "on" notes from a MIDI instrument (DONE)
- Display chord names matching the note structure (DONE)
- Flesh out supported chords with all typical chord types and inversions (IN PROGRESS)
- Customize displayed info using GUI controls (NOT done)
- Conform to the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

## Compiling
Requirements (with example Debian/Ubuntu package names):
- CMake 3.25+ (cmake)
- Qt 6.3 dev files (qt6-base-dev)
- OpenGL dev files required by Qt6 (libgl1-mesa-dev)
- ALSA dev files (libasound2-dev)
- Boost JSON dev files (libboost-json1.81-dev)
- An internet connection, since gtest 1.15.0 is downloaded from github during the build

Build instructions
```
mkdir build
cd build
cmake ..
cmake --build .
ctest # optional, run the unit tests
```
The output binary in the build directory is called `chordless`.

## Usage
Run `chordless` with no arguments. An ALSA port is opened.
Use an ALSA utility such as `aconnectgui` to connect your MIDI instrument to chordless.
chordless listens to all MIDI channels.

![chordless and aconnectgui](/screenshot.png?raw=true "Screenshot")

## Desired features
- Select sharps or flats preference with a UI widget.
- Toggle numeric subscript visibility with a UI widget.
- Specify config file as a command line argument

## Further work
- Select key/mode, for improved chord naming/analysis
- JACK MIDI input
- Sustain pedal
  - Keep notes on to correspond to sustain pedal "dampers lifted"
  - Control this setting with a UI widget
- Bass chords only
  - Apply chord detection only to lowest matching pattern.
  - Would match chords to the prevailing harmony (left hand) without being muddled by the melody (right hand).
  - Control this setting with a UI widget
- Resizable window with font scaling
- Make unit testing a separate target
- Consider storing gtest files in the repository, instead of downloading

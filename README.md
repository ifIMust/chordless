# chordless
## Description
chordless is a MIDI note analyzer that runs on Linux.
Any modern Linux (i.e. with ALSA) version should work.

This project uses:
- Qt for GUI
- CMake for build
- gtest for unit testing
- ALSA for receiving MIDI events

## Compiling
Requirements (with example Debian/Ubuntu package names):
- CMake (cmake)
- Qt dev files (qt6-base-dev)
- ALSA dev files (libasound2-dev)
- An internet connection, since gtest is downloaded from github during the build
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
Use an ALSA utility such as `aconnectgui` to connect your MIDI instrument to chordless


## Desired features
- Add L/GPL license to comply with Qt licensing.
- Select sharps or flats preference with a UI widget.
- Display note octave as numeric subscript.
- Detect chord patterns and display the chord names.


## Further work
- Make unit testing a separate target
- Resizable window with font scaling
- Support JACK MIDI input
- Select key/mode, for improved chord naming/analysis
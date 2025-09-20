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
Requirements:
- CMake 3.25+
  - Debian/Ubuntu: `cmake`
  - Fedora: `cmake`
- Ninja build system
  - Debian/Ubuntu: `ninja-build`
  - Fedora: `ninja-build`
- Qt 6.3 dev files
  - Debian/Ubuntu: `qt6-base-dev`, `qt6-declarative-dev`
  - Fedora: `qt6-qtbase-devel`, `qt6-qtdeclarative-devel`
- OpenGL dev files required by Qt6
  - Debian/Ubuntu: `libgl1-mesa-dev`
  - Fedora: `mesa-libGL-devel`
- ALSA dev files
  - Debian/Ubuntu: `libasound2-dev`
  - Fedora: `alsa-lib-devel`
- Boost program_options and json dev files
  - Debian/Ubuntu: `libboost-json1.81-dev`, `libboost-program-options1.81-dev`
  - Fedora: `boost-devel`
- An internet connection, since gtest 1.15.0 is downloaded from github during the build

Build instructions
```
cmake --workflow --preset release
```
The output binary is created at `build/release/chordless`.

## Usage
In addition to compile dependencies, `qml6-module-qtquick-templates` is used at runtime.

Running `build/release/chordless` from the project root will use the provided `chords.json` config file.
Use `chordless -c FILE_NAME` to specify a different chord configuration or path.

An ALSA MIDI input port is opened when the application launches.
Use an ALSA utility such as `aconnectgui` to connect your MIDI instrument to chordless.
Notes are read from all MIDI channels, and all other MIDI traffic is ignored.

![chordless and aconnectgui](/screenshot.png?raw=true "Screenshot")

## Planned steps
- Deploy a package that includes most/all dependencies.
  - Create a .deb package.
- Toggle numeric subscript visibility with a UI widget.
- Use a config file for general progam settings.

## Further work
- Select key/mode, for improved chord naming/analysis.
- JACK MIDI input
- Sustain checkbox: Keep notes on, respecting sustain pedal.
- Bass chords only
  - Apply chord detection only to lowest matching pattern.
  - Would match chords to the prevailing harmony (left hand) without being muddled by the melody (right hand).
  - Control this setting with a UI widget.


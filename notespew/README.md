# notespew

MIDI note generator for testing chordless.

## Description

notespew creates an ALSA MIDI output port and generates 3 random notes every second. It's designed to provide test input for the chordless chord analyzer without requiring a physical MIDI device.

## Build

```bash
cmake -B build -S .
cmake --build build
```

## Usage

```bash
./build/notespew
```

The program will run until interrupted with Ctrl+C. Use `aconnect` to connect the MIDI output to chordless:

```bash
# Find client IDs
aconnect -l

# Connect notespew output to chordless input
aconnect <notespew_client>:0 <chordless_client>:0
```

## Automated Testing

Use the included `spew-notes.sh` script to automatically launch both notespew and chordless with MIDI connection:

```bash
./spew-notes.sh
```

This requires chordless to be built in `../build/release/`.
#!/bin/bash

# spew-notes.sh - Launch chordless with notespew for testing

set -e

CHORDLESS_BIN="../build/release/chordless"
NOTESPEW_BIN="./build/notespew"

# Check if binaries exist
if [ ! -f "$CHORDLESS_BIN" ]; then
    echo "Error: chordless binary not found at $CHORDLESS_BIN"
    echo "Please build chordless first:"
    echo "  cd .. && cmake --workflow --preset release"
    exit 1
fi

if [ ! -f "$NOTESPEW_BIN" ]; then
    echo "Error: notespew binary not found at $NOTESPEW_BIN"
    echo "Please build notespew first:"
    echo "  cmake -B build -S . && cmake --build build"
    exit 1
fi

# Check if aconnect is available
if ! command -v aconnect &> /dev/null; then
    echo "Error: aconnect utility not found"
    echo "Please install alsa-utils package:"
    echo "  Debian/Ubuntu: sudo apt install alsa-utils"
    echo "  Fedora: sudo dnf install alsa-utils"
    exit 1
fi

echo "Starting chordless and notespew test session..."

# Function to cleanup processes
cleanup() {
    echo ""
    echo "Stopping processes..."
    if [ ! -z "$CHORDLESS_PID" ]; then
        kill $CHORDLESS_PID 2>/dev/null || true
    fi
    if [ ! -z "$NOTESPEW_PID" ]; then
        kill $NOTESPEW_PID 2>/dev/null || true
    fi
    exit 0
}

# Set up signal handler
trap cleanup SIGINT SIGTERM

# Start chordless in background
echo "Starting chordless..."
$CHORDLESS_BIN &
CHORDLESS_PID=$!

# Give chordless time to start up
sleep 2

# Start notespew in background
echo "Starting notespew..."
$NOTESPEW_BIN &
NOTESPEW_PID=$!

# Give notespew time to create its ALSA port
sleep 2

# Find the ALSA client IDs
echo "Discovering ALSA clients..."
CHORDLESS_CLIENT=$(aconnect -l | grep "chordless" | head -n1 | cut -d' ' -f2 | cut -d':' -f1)
NOTESPEW_CLIENT=$(aconnect -l | grep "notespew" | head -n1 | cut -d' ' -f2 | cut -d':' -f1)

if [ -z "$CHORDLESS_CLIENT" ]; then
    echo "Error: Could not find chordless ALSA client"
    cleanup
fi

if [ -z "$NOTESPEW_CLIENT" ]; then
    echo "Error: Could not find notespew ALSA client"
    cleanup
fi

echo "Found chordless client: $CHORDLESS_CLIENT"
echo "Found notespew client: $NOTESPEW_CLIENT"

# Connect notespew output to chordless input
echo "Connecting MIDI: notespew -> chordless"
aconnect $NOTESPEW_CLIENT:0 $CHORDLESS_CLIENT:0

echo ""
echo "Test session running!"
echo "- notespew is generating random notes every second"
echo "- chordless should display the chord analysis"
echo "- Press Ctrl+C to stop both programs"
echo ""

# Wait for processes to finish or be interrupted
wait $CHORDLESS_PID $NOTESPEW_PID
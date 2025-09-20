#include <alsa/asoundlib.h>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

class NotesSpewer {
public:
    NotesSpewer() {
        // Initialize ALSA sequencer
        int error = snd_seq_open(&seq_handle_, "default", SND_SEQ_OPEN_OUTPUT, 0);
        if (error < 0) {
            std::cerr << "Failed to open ALSA sequencer: " << snd_strerror(error) << std::endl;
            return;
        }

        snd_seq_set_client_name(seq_handle_, "notespew");

        // Create output port
        port_ = snd_seq_create_simple_port(seq_handle_, "MIDI Output",
                                          SND_SEQ_PORT_CAP_READ | SND_SEQ_PORT_CAP_SUBS_READ,
                                          SND_SEQ_PORT_TYPE_MIDI_GENERIC);

        if (port_ < 0) {
            std::cerr << "Failed to create ALSA port: " << snd_strerror(port_) << std::endl;
            snd_seq_close(seq_handle_);
            seq_handle_ = nullptr;
            return;
        }

        valid_ = true;

        // Initialize random number generator
        std::random_device rd;
        gen_.seed(rd());
        note_dist_ = std::uniform_int_distribution<int>(36, 84); // C2 to C6

        std::cout << "notespew initialized successfully" << std::endl;
        std::cout << "ALSA client: " << snd_seq_client_id(seq_handle_) << std::endl;
        std::cout << "ALSA port: " << port_ << std::endl;
    }

    ~NotesSpewer() {
        if (seq_handle_) {
            snd_seq_close(seq_handle_);
        }
    }

    bool IsValid() const {
        return valid_;
    }

    void SendNoteOn(int note, int velocity = 64) {
        if (!valid_) return;

        snd_seq_event_t ev;
        snd_seq_ev_clear(&ev);
        snd_seq_ev_set_source(&ev, port_);
        snd_seq_ev_set_subs(&ev);
        snd_seq_ev_set_direct(&ev);

        snd_seq_ev_set_noteon(&ev, 0, note, velocity);
        snd_seq_event_output_direct(seq_handle_, &ev);
    }

    void SendNoteOff(int note) {
        if (!valid_) return;

        snd_seq_event_t ev;
        snd_seq_ev_clear(&ev);
        snd_seq_ev_set_source(&ev, port_);
        snd_seq_ev_set_subs(&ev);
        snd_seq_ev_set_direct(&ev);

        snd_seq_ev_set_noteoff(&ev, 0, note, 64);
        snd_seq_event_output_direct(seq_handle_, &ev);
    }

    void Run() {
        if (!valid_) {
            std::cerr << "NotesSpewer is not valid, cannot run" << std::endl;
            return;
        }

        std::cout << "Starting note spewing... Press Ctrl+C to stop" << std::endl;

        std::vector<int> current_notes;

        while (true) {
            // Turn off all current notes
            for (int note : current_notes) {
                SendNoteOff(note);
            }
            current_notes.clear();

            // Generate 3 random notes
            for (int i = 0; i < 3; ++i) {
                int note = note_dist_(gen_);
                current_notes.push_back(note);
                SendNoteOn(note);
            }

            // Wait 1 second
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

private:
    snd_seq_t* seq_handle_ = nullptr;
    int port_ = -1;
    bool valid_ = false;

    std::mt19937 gen_;
    std::uniform_int_distribution<int> note_dist_;
};

int main() {
    std::cout << "notespew - Random MIDI note generator" << std::endl;

    NotesSpewer spewer;
    if (!spewer.IsValid()) {
        std::cerr << "Failed to initialize notespew" << std::endl;
        return 1;
    }

    spewer.Run();
    return 0;
}
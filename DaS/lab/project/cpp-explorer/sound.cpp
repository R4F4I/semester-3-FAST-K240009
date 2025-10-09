#include <iostream>
#include <map>
#include <string>
#include <vector> // Added required header for std::vector
// *** WARNING: The Beep function is Windows-specific and non-standard. ***
#include <windows.h> 

// High-precision value for Pi is no longer needed for Beep()

// --- Configuration Constants for Timing ---
// Since Beep requires milliseconds, we use this conversion constant.
const double DURATION_MULTIPLIER_MS = 1000.0;

/**
 * @brief Defines the standard musical frequencies in Hertz (Hz).
 * * Based on A4 = 440 Hz temperament.
 */
std::map<std::string, double> initialize_frequencies() {
    std::map<std::string, double> freqs = {
        {"C4", 261.63},
        {"D4", 293.66},
        {"E4", 329.63},
        {"F4", 349.23},
        {"G4", 392.00},
        {"A4", 440.00},
        {"B4", 493.88},
        {"C5", 523.25},
        {"REST", 0.0} // Silence/Rest
    };
    return freqs;
}

// NOTE: The generate_note_samples function is removed as Beep handles playback directly.

int main() {
    std::cout << "--- Starting Direct Audio Playback (Windows Only) ---" << std::endl;
    std::cout << "Using the Windows API Beep function." << std::endl;

    // 1. Initialize Frequencies
    const auto note_frequencies = initialize_frequencies();

    // 2. Define the Song Structure: London Bridge is Falling Down
    // The sequence is pairs of (Note Name, Duration in Seconds)
    // Quarter note = 0.5s, Half note = 1.0s, Dotted Half = 1.5s
    const double Q = 0.5; // Quarter Note
    const double H = 1.0; // Half Note
    const double P = 0.05; // Short Pause/Rest for separation (ignored by Beep, but kept for clarity)

    // Duration of Beep should be slightly shorter than the total duration 
    // to separate notes, as Beep blocks execution.
    const double NOTE_DUTY_CYCLE = 0.95; 

    std::vector<std::pair<std::string, double>> song_sequence = {
        // London Bridge is falling down,
        {"G4", Q}, {"A4", Q}, {"G4", Q}, {"F4", Q},
        {"E4", Q}, {"F4", Q}, {"G4", H},
        {"REST", P},

        // Falling down, falling down.
        {"D4", Q}, {"E4", Q}, {"F4", H}, 
        {"REST", P},
        
        // London Bridge is falling down,
        {"G4", Q}, {"A4", Q}, {"G4", Q}, {"F4", Q},
        {"E4", Q}, {"F4", Q}, {"G4", H * 2} // Last note held longer
    };

    // 3. Play the Song
    for (const auto& note_data : song_sequence) {
        const std::string& note_name = note_data.first;
        double total_duration_s = note_data.second;
        
        // Lookup the frequency
        double freq_s = 0.0;
        if (note_frequencies.count(note_name)) {
            freq_s = note_frequencies.at(note_name);
        } else {
            std::cerr << "Error: Unknown note name '" << note_name << "'. Skipping." << std::endl;
            continue;
        }

        DWORD total_duration_ms = static_cast<DWORD>(total_duration_s * DURATION_MULTIPLIER_MS);
        DWORD beep_duration_ms = static_cast<DWORD>(total_duration_s * NOTE_DUTY_CYCLE * DURATION_MULTIPLIER_MS);
        DWORD rest_duration_ms = total_duration_ms - beep_duration_ms;

        if (freq_s > 0) {
            // Play the tone
            DWORD freq_hz = static_cast<DWORD>(freq_s);
            
            // Beep function plays a tone and blocks for beep_duration_ms
            Beep(freq_hz, beep_duration_ms);

            // Rest for the remaining time to separate notes
            Sleep(rest_duration_ms); 

            std::cout << "Playing note: " << note_name << " (" << freq_hz << " Hz) for " << total_duration_s << "s" << std::endl;
        } else {
            // Handle REST: simply sleep for the entire duration
            Sleep(total_duration_ms);
            std::cout << "Resting for " << total_duration_s << "s" << std::endl;
        }
    }
    
    std::cout << "--- Playback Complete ---" << std::endl;

    return 0;
}

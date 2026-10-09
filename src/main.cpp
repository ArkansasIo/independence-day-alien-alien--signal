#include "signal/SynthesizedAlienPulse.hpp"
#include "signal/WavWriter.hpp"
#include <iostream>
int main() {
    alien_signal::SynthesizedAlienPulse synth;
    const auto samples = synth.render();
    if (!alien_signal::write_wav_pcm16_stereo("alien_pulse_generated.wav", samples,
                                               static_cast<std::uint32_t>(synth.parameters().sample_rate_hz))) {
        std::cerr << "Failed to write WAV output.\n";
        return 1;
    }
    std::cout << "Generated " << samples.size() << " samples.\n";
    return 0;
}

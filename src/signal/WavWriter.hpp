#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace alien_signal {
bool write_wav_pcm16_stereo(const std::string& path,
                            const std::vector<float>& mono,
                            std::uint32_t sample_rate);
}

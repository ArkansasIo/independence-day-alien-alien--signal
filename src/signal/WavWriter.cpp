#include "WavWriter.hpp"
#include <algorithm>
#include <fstream>
#include <limits>

namespace alien_signal {
namespace {
void put_u16(std::ofstream& f, std::uint16_t v) {
    f.put(static_cast<char>(v & 0xff)); f.put(static_cast<char>((v >> 8) & 0xff));
}
void put_u32(std::ofstream& f, std::uint32_t v) {
    for (int i=0;i<4;++i) f.put(static_cast<char>((v >> (8*i)) & 0xff));
}
}
bool write_wav_pcm16_stereo(const std::string& path,
                            const std::vector<float>& mono,
                            std::uint32_t sample_rate) {
    std::ofstream f(path, std::ios::binary);
    if (!f) return false;
    const std::uint32_t frames = static_cast<std::uint32_t>(
        std::min<std::size_t>(mono.size(), std::numeric_limits<std::uint32_t>::max() / 4));
    const std::uint32_t data_size = frames * 4;
    f.write("RIFF",4); put_u32(f,36+data_size); f.write("WAVE",4);
    f.write("fmt ",4); put_u32(f,16); put_u16(f,1); put_u16(f,2);
    put_u32(f,sample_rate); put_u32(f,sample_rate*4); put_u16(f,4); put_u16(f,16);
    f.write("data",4); put_u32(f,data_size);
    for (std::uint32_t i=0;i<frames;++i) {
        const float x = std::clamp(mono[i],-1.0f,1.0f);
        const auto s = static_cast<std::int16_t>(x * 32767.0f);
        put_u16(f,static_cast<std::uint16_t>(s));
        put_u16(f,static_cast<std::uint16_t>(s));
    }
    return static_cast<bool>(f);
}

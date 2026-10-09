#include "SynthesizedAlienPulse.hpp"
#include <cmath>
#include <algorithm>

namespace alien_signal {
namespace {
constexpr double kPi = 3.14159265358979323846;
}
SynthesizedAlienPulse::SynthesizedAlienPulse(SignalParameters parameters)
    : parameters_(parameters) {}

std::vector<float> SynthesizedAlienPulse::render() const {
    const std::size_t count = static_cast<std::size_t>(
        std::max(0.0, parameters_.duration_seconds) * parameters_.sample_rate_hz);
    std::vector<float> out(count, 0.0f);
    if (count == 0 || parameters_.sample_rate_hz <= 0.0 || parameters_.pulse_rate_hz <= 0.0)
        return out;

    const double pulse_period = 1.0 / parameters_.pulse_rate_hz;
    for (std::size_t i = 0; i < count; ++i) {
        const double t = static_cast<double>(i) / parameters_.sample_rate_hz;
        const double phase = std::fmod(t, pulse_period) / pulse_period;
        const double envelope = phase < 0.08
            ? phase / 0.08
            : std::exp(-(phase - 0.08) * 10.0);
        const double carrier = std::sin(2.0 * kPi * parameters_.carrier_hz * t);
        const double sub = 0.30 * std::sin(2.0 * kPi * parameters_.sub_component_hz * t);
        out[i] = static_cast<float>(0.72 * envelope * (carrier + sub));
    }
    return out;
}

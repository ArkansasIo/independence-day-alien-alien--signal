#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

namespace alien_signal {
struct SignalParameters {
    double duration_seconds = 7.0;
    double sample_rate_hz = 44100.0;
    double pulse_rate_hz = 4.15;
    double carrier_hz = 438.0;
    double sub_component_hz = 74.0;
};

class SynthesizedAlienPulse {
public:
    explicit SynthesizedAlienPulse(SignalParameters parameters = {});
    std::vector<float> render() const;
    const SignalParameters& parameters() const noexcept { return parameters_; }

private:
    SignalParameters parameters_;
};
}

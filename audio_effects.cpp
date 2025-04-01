#include "audio_effects.h"
#include <iostream>
#include <vector>
#include <sndfile.h>
#include <cstring>

#pragma comment(lib, "sndfile.lib")

AudioData loadAudioFile(const char* filename) {
    AudioData audio;
    memset(&audio.info, 0, sizeof(audio.info));

    SNDFILE* file = sf_open(filename, SFM_READ, &audio.info);
    if (!file) {
        std::cerr << "Error opening file: " << sf_strerror(NULL) << std::endl;
        exit(1);
    }

    audio.samples.resize(audio.info.frames * audio.info.channels);
    sf_readf_double(file, audio.samples.data(), audio.info.frames);
    sf_close(file);

    return audio;
}

void saveAudioFile(const char* filename, const AudioData& audio) {
    SF_INFO info = audio.info; // Copy the info to non-const version
    SNDFILE* file = sf_open(filename, SFM_WRITE, &info);
    if (!file) {
        std::cerr << "Error creating file: " << sf_strerror(NULL) << std::endl;
        exit(1);
    }

    sf_writef_double(file, audio.samples.data(), audio.info.frames);
    sf_close(file);
}

void applyEcho(AudioData& audio, double delaySeconds, double decay) {
    int delaySamples = static_cast<int>(delaySeconds * audio.info.samplerate);
    std::vector<double> output(audio.samples.size());

    for (size_t i = 0; i < audio.samples.size(); ++i) {
        output[i] = audio.samples[i];
        if (i >= static_cast<size_t>(delaySamples * audio.info.channels)) {
            output[i] += decay * audio.samples[i - delaySamples * audio.info.channels];
        }
    }

    audio.samples = output;
}

void pitchShift(AudioData& audio, double shiftRatio) {
    std::vector<double> output;
    output.reserve(static_cast<size_t>(audio.samples.size() / shiftRatio));

    double index = 0.0;
    while (static_cast<size_t>(index) < audio.samples.size()) {
        output.push_back(audio.samples[static_cast<size_t>(index)]);
        index += shiftRatio;
    }

    audio.samples = output;
    audio.info.frames = static_cast<sf_count_t>(output.size() / audio.info.channels);
}

void changeSpeed(AudioData& audio, double speedRatio) {
    std::vector<double> output;
    output.reserve(static_cast<size_t>(audio.samples.size() / speedRatio));

    for (size_t i = 0; i < audio.samples.size(); i += static_cast<size_t>(speedRatio)) {
        if (i < audio.samples.size()) {
            output.push_back(audio.samples[i]);
        }
    }

    audio.samples = output;
    audio.info.frames = static_cast<sf_count_t>(output.size() / audio.info.channels);
}
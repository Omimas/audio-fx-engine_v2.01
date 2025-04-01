#ifndef AUDIO_EFFECTS_H
#define AUDIO_EFFECTS_H

#include <vector>
#include <sndfile.h>

struct AudioData {
    std::vector<double> samples;
    SF_INFO info;  // SF_INFO artýk const olmayacak
};

// Fonksiyon prototipleri
AudioData loadAudioFile(const char* filename);
void saveAudioFile(const char* filename, const AudioData& audio);
void applyEcho(AudioData& audio, double delaySeconds, double decay);
void pitchShift(AudioData& audio, double shiftRatio);
void changeSpeed(AudioData& audio, double speedRatio);

#endif
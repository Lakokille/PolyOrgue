#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H

#include <QAudioSink>
#include <QAudioFormat>
#include <QBuffer>
#include <cmath>
#include <vector>
#include "audiogenerator.h"

class SoundEngine
{
private:
    QAudioFormat* m_Format;
    QAudioSink* m_AudioOutput;
    std::vector<double> m_FrequencyNotes = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88};
    AudioGenerator* m_generator;

public:
    //Penser à rajouter le format pour initialiser le moteur de son
    SoundEngine();
    void PlayNote(int N_FreqIndex = 0);
    void StopNote();
};

#endif // SOUNDENGINE_H

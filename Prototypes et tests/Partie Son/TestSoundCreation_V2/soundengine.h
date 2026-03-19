#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H

#include <QAudioFormat>
#include <QAudioSink>
#include "audiogenerator.h"

class SoundEngine
{
public:
    SoundEngine();

    void PlayNote(int index);
    void StopNote();

private:
    QAudioFormat *m_Format;
    QAudioSink *m_AudioOutput;
    AudioGenerator *m_generator;

    double m_FrequencyNotes[6] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00};
};

#endif

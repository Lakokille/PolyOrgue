#ifndef PIANOSYNTH_H
#define PIANOSYNTH_H

#include <QByteArray>
#include <QtMath>
#include <QDebug>

#define PI 3.14159265358979323846

class PianoSynth
{
public:
    PianoSynth(int sampleRate = 44100);

    QByteArray generateNote(double frequency, int durationMs);

private:
    int m_sampleRate;
};

#endif

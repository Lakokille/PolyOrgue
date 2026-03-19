#include "pianosynth.h"

PianoSynth::PianoSynth(int sampleRate) : m_sampleRate(sampleRate)
{
}

QByteArray PianoSynth::generateNote(double frequency, int durationMs)
{
    int totalSamples = m_sampleRate * durationMs / 1000;
    QByteArray data;
    data.resize(totalSamples * 2);
    qint16 *samples = reinterpret_cast<qint16*>(data.data());

    for(int i = 0; i < totalSamples; i++) {
        double t = double(i) / m_sampleRate;
        double sample = 0.0;

        // Harmoniques piano
        sample += 0.8 * qSin(2 * PI * frequency * t);
        sample += 0.3 * qSin(2 * PI * frequency * 2 * t);
        sample += 0.15 * qSin(2 * PI * frequency * 3 * t);
        sample += 0.05 * qSin(2 * PI * frequency * 4 * t);

        // Enveloppe (attaque rapide + decay piano)
        double envelope = (t < 0.005) ? t/0.005 : qExp(-4.0 * t);
        sample *= envelope * 0.5 * 32767.0;

        samples[i] = static_cast<qint16>(qBound(-32767, int(sample), 32767));
    }

    return data;
}

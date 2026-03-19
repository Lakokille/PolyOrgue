#include "audiogenerator.h"

AudioGenerator::AudioGenerator(QObject *parent)
    : QIODevice(parent),
    m_freq(0),
    m_phase(0),
    m_sampleRate(44100)
{
}

void AudioGenerator::start()
{
    open(QIODevice::ReadOnly);
}

void AudioGenerator::stop()
{
    close();
}

void AudioGenerator::setFrequency(double freq)
{
    m_freq = freq;
}

qint64 AudioGenerator::readData(char *data, qint64 maxlen)
{
    qint16 *out = reinterpret_cast<qint16*>(data);
    int samples = maxlen / 2;

    for (int i = 0; i < samples; ++i)
    {
        double amplitude = (m_freq > 0) ? 1.0 : 0.0;

        qint16 value = qint16(32767 * amplitude * sin(2 * M_PI * m_freq * m_phase));
        m_phase += 1.0 / m_sampleRate;

        out[i] = value;
    }

    return samples * 2;
}

qint64 AudioGenerator::writeData(const char *data, qint64 len)
{
    Q_UNUSED(data);
    Q_UNUSED(len);
    return 0;
}

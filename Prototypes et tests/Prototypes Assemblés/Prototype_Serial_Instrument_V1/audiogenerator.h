#ifndef AUDIOGENERATOR_H
#define AUDIOGENERATOR_H

#include <QIODevice>

class AudioGenerator : public QIODevice
{
private:
    double m_freq = 440;
    double m_phase = 0;
    int m_sampleRate = 44100;

public:
    AudioGenerator(QObject *parent = nullptr) : QIODevice(parent) {}
    void start() { open(QIODevice::ReadOnly); }
    void stop() { close(); }
    void setFrequency(double freq) { m_freq = freq; }

protected:

    qint64 readData(char *data, qint64 maxlen) override
    {
        qint16 *out = reinterpret_cast<qint16*>(data);
        int samples = maxlen / 2;

        for (int i = 0; i < samples; ++i)
        {
            qint16 value = 0;

            if (m_freq > 0)
            {
                value = qint16(32767 * sin(2 * M_PI * m_freq * m_phase));
                m_phase += 1.0 / m_sampleRate;
            }

            out[i] = value;
        }

        return samples * 2;
    }

    qint64 writeData(const char *data, qint64 len) override
    {
        Q_UNUSED(data);
        Q_UNUSED(len);
        return 0;
    }
};

#endif // AUDIOGENERATOR_H

#ifndef AUDIOGENERATOR_H
#define AUDIOGENERATOR_H

#include <QIODevice>
#include <cmath>

class AudioGenerator : public QIODevice
{
public:
    AudioGenerator(QObject *parent = nullptr);

    void start();
    void stop();

    void setFrequency(double freq);

protected:
    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;

private:
    double m_freq;
    double m_phase;
    int m_sampleRate;
};

#endif

#include <QCoreApplication>
#include <QAudioSink>
#include <QAudioFormat>
#include <QIODevice>
#include <cmath>

class SineGenerator : public QIODevice {
public:
    SineGenerator(double frequency, int sampleRate, QObject* parent = nullptr)
        : QIODevice(parent), m_freq(frequency), m_sampleRate(sampleRate), m_phase(0.0) {}

    void start() { open(QIODevice::ReadOnly); }
    void stop() { close(); }

protected:
    qint64 readData(char *data, qint64 maxlen) override {
        qint64 samples = maxlen / 2; // 2 octets par échantillon
        qint16* ptr = reinterpret_cast<qint16*>(data);

        for (qint64 i = 0; i < samples; ++i) {
            ptr[i] = qint16(32767 * std::sin(2.0 * M_PI * m_freq * m_phase / m_sampleRate));
            m_phase += 1.0;
            if (m_phase >= m_sampleRate) m_phase -= m_sampleRate;
        }
        return samples * 2; // nombre d’octets écrits
    }

    qint64 writeData(const char*, qint64) override { return 0; }
    qint64 bytesAvailable() const override { return 4096 + QIODevice::bytesAvailable(); }

private:
    double m_freq;
    int m_sampleRate;
    double m_phase;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);

    QAudioSink audioSink(format);

    SineGenerator generator(440.0, format.sampleRate());
    generator.start();

    audioSink.start(&generator);

    return a.exec();
}

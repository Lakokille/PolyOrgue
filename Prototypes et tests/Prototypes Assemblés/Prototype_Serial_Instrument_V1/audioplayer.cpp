#include "audioplayer.h"
#include <QAudioFormat>

AudioPlayer::AudioPlayer(QObject *parent)
    : QObject(parent)
{
    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);

    QAudioDevice device = QMediaDevices::defaultAudioOutput();
    m_audioSink = new QAudioSink(device, format, this);
    m_audioSink->setVolume(0.8);
}

AudioPlayer::~AudioPlayer()
{
    m_audioSink->stop();
}

void AudioPlayer::playBuffer(const QByteArray &pcmData)
{
    QBuffer *buffer = new QBuffer(this);
    buffer->setData(pcmData);
    buffer->open(QIODevice::ReadOnly);

    m_audioSink->stop();
    m_audioSink->start(buffer);

    // nettoyage auto
    connect(m_audioSink, &QAudioSink::stateChanged, buffer, [buffer](QAudio::State state){
        if(state == QAudio::IdleState) {
            buffer->close();
            buffer->deleteLater();
        }
    });
}

void AudioPlayer::stop()
{
    m_audioSink->stop();
}

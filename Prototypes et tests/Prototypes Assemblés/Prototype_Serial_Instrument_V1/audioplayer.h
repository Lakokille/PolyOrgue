#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QAudioSink>
#include <QBuffer>
#include <QMediaDevices>
#include <QObject>

class AudioPlayer : public QObject
{
    Q_OBJECT
public:
    AudioPlayer(QObject *parent = nullptr);
    ~AudioPlayer();

    void playBuffer(const QByteArray &pcmData);
    void stop();

private:
    QAudioSink *m_audioSink;
};

#endif

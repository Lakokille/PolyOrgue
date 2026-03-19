#include "soundengine.h"

SoundEngine::SoundEngine()
{
    m_Format = new QAudioFormat;
    m_Format->setSampleRate(44100);
    m_Format->setChannelCount(1);
    m_Format->setSampleFormat(QAudioFormat::Int16);

    m_AudioOutput = new QAudioSink(*m_Format);

    m_generator = new AudioGenerator();
    m_generator->start();

    m_AudioOutput->start(m_generator);
}

void SoundEngine::PlayNote(int index)
{
    m_generator->setFrequency(m_FrequencyNotes[index]);
}

void SoundEngine::StopNote()
{
    m_generator->setFrequency(0);
}

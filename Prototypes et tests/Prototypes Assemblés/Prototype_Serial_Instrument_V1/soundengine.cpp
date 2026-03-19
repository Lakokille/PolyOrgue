#include "soundengine.h"

SoundEngine::SoundEngine()
{
    //Par défaut le format est le suivant

    //--FORMAT--//
    m_Format = new QAudioFormat;
    //Nombre d'échantillons
    m_Format->setSampleRate(44100);
    //Ici channel mono parce que on a pas besoin de stéréo
    m_Format->setChannelCount(1);
    //Format sur 2 octet son 16 bits
    m_Format->setSampleFormat(QAudioFormat::Int16);

    //Création de l'objet qui gère les IO
    m_AudioOutput = new QAudioSink(*m_Format);

    m_generator = new AudioGenerator();
    m_generator->start();

    m_AudioOutput->start(m_generator);
}

void SoundEngine::PlayNote(int N_FreqIndex)
{
    m_generator->setFrequency(m_FrequencyNotes[N_FreqIndex]);
}

void SoundEngine::StopNote()
{
    m_generator->setFrequency(0);
}

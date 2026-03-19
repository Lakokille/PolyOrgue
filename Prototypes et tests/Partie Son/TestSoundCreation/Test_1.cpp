#include <QCoreApplication>
#include <QAudioSink>
#include <QAudioFormat>
#include <QBuffer>
#include <cmath>
#include <vector>

int main(int argc, char *argv[])
{
    QCoreApplication App(argc, argv);

    //--FORMAT--//
    //Format de la sortie sonore
    QAudioFormat format;
    //Nombre d'échantillons
    format.setSampleRate(44100);
    //Ici channel mono parce que on a pas besoin de stéréo
    format.setChannelCount(1);
    //Format sur 2 octet son 16 bits
    format.setSampleFormat(QAudioFormat::Int16);

    //--Création de l'objet qui gère les IO
    QAudioSink audioSink(format);

    //Fréquence des notes rapport de racine de (voir sur wiki jsplus)
    std::vector<double> notes = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88};
    const int sampleRate = format.sampleRate();
    const int durationSec = 1;

    //Créer un buffer unique
    QByteArray buffer;
    buffer.reserve(notes.size() * sampleRate * 2); // 2 octets par échantillon

    for (double freq : notes) {
        int numSamples = sampleRate * durationSec;
        for (int i = 0; i < numSamples; ++i) {
            double t = i / double(sampleRate);
            qint16 sample = qint16(32767 * std::sin(2.0 * M_PI * freq * t));
            buffer.append(reinterpret_cast<const char*>(&sample), 2);
        }
    }

    //Ecriture dans un buffer des données
    QBuffer audioBuffer(&buffer);
    audioBuffer.open(QIODevice::ReadOnly);

    //Jouer tout le buffer en une fois
    audioSink.start(&audioBuffer);

    return App.exec();
}

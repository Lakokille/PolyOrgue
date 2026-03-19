#include <QApplication>
#include <QTimer>
#include "pianosynth.h"
#include "audioplayer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //
    PianoSynth synth;
    //
    AudioPlayer player;

    // Octave Do → Do
    double notes[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};

    for(int i = 0; i < 8; i++)
    {
        //QTimer pour jouer la note
        QTimer::singleShot(i * 600, [i, &notes, &synth, &player]()
        {
            QByteArray pcm = synth.generateNote(notes[i], 500);
            player.playBuffer(pcm);
        });
    }

    return app.exec();
}

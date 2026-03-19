#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QVector>
#include "soundengine.h"
#include  "pianosynth.h"
#include "audioplayer.h"

//QMainWindow = QWidgets sous amphétamines (menubar,statusbar,toolbar,centralwidgets etc...)
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QSerialPort m_SerialPort;
    QVector<int> m_vSensorStates; // 6 bits des capteurs
    PianoSynth* m_pSynth;
    AudioPlayer* m_pPlayer;
    int m_prevNote = -1;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void readSerial();

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MAINWINDOW_H

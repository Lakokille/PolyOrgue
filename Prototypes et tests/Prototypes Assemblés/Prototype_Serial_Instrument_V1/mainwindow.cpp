#include "mainwindow.h"
#include <QPainter>
#include <QSerialPortInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_vSensorStates(6, 0) // initialise le vecteur des 6 capteurs à 0
{
    //--WINDOW SETUP--//
    {
    resize(400, 100); // taille de la fenêtre
    setWindowTitle("PolyOrgue Build 1");
    }

    //--FLUX USB--//
    {
    //--CONFIG--//

    {
    //Permet de définir le Port
    m_SerialPort.setPortName("COM3");
    //Permet de définir le baud rate
    m_SerialPort.setBaudRate(QSerialPort::Baud115200);
    //Nombre de bits de données par octet
    m_SerialPort.setDataBits(QSerialPort::Data8);
    //Définir le Bit de parité pour les erreurs
    m_SerialPort.setParity(QSerialPort::NoParity);
    //Par défaut 1 bit stop à la fin de chaque octect
    m_SerialPort.setStopBits(QSerialPort::OneStop);
    //Contrôle du flux de données
    m_SerialPort.setFlowControl(QSerialPort::NoFlowControl);
    }

    //--EVENT--//
    {
    if(!m_SerialPort.open(QIODevice::ReadOnly))
    {
        qDebug() << "Erreur ouverture port :" << m_SerialPort.errorString();
        return;
    }

    //Initialisation du moteur de son
    m_pSynth = new PianoSynth;
    m_pPlayer = new AudioPlayer(this);

    //Lis le port tout le temps
    connect(&m_SerialPort, &QSerialPort::readyRead, this, &MainWindow::readSerial);
    }
    }
}

MainWindow::~MainWindow() { }

void MainWindow::readSerial()
{
    // lire tout ce qui est disponible sur le port
    QByteArray data = m_SerialPort.readAll();
    // stocker dans un buffer statique pour gérer les morceaux (on décortique chaque retour à la ligne \n)
    static QByteArray lineBuffer;
    //Ajoute les données à la fin du tableau de byte
    lineBuffer.append(data);

    qDebug() << "Données reçues :" << data;

    // vérifier si on a une ligne complète (finie par '\n')
    int index = lineBuffer.indexOf('\n');

    if(index != -1)
    {
        // extraire la ligne complète (Tableau d'octet temporaire)
        //left(idx) permet de prendre tout les caractères à gauche de l'index idx
        //trimmed() supprime les retour \r et les espaces
        QByteArray line = lineBuffer.left(index).trimmed(); // "000000"
        //remove(index, longueur)
        lineBuffer.remove(0, index + 1); // retirer cette ligne du buffer

        // mettre à jour le tableau de capteurs (deuxième vérification)
        if(line.size() == 6) // exactement 6 bits
        {
            int activeNote = -1;

            for(int i = 0; i < 6; ++i)
                if(line[i] == '1')
                {
                    activeNote = i;
                    m_vSensorStates[i] = 1;
                }
                else
                {
                    m_vSensorStates[i] = 0;
                }
            if(activeNote != m_prevNote)
            {
                // On convertit l'indice de capteur en fréquence
                double notes[6] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00};
                if(activeNote != -1)
                {
                    QByteArray pcm = m_pSynth->generateNote(notes[activeNote], 500);
                    m_pPlayer->playBuffer(pcm);
                }
                else
                {
                    // silence : on stop le player
                    m_pPlayer->stop();
                }
                m_prevNote = activeNote;
            }
        }
        update(); // redessiner la fenêtre
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt::red);

    int windowW = width();

    int n = m_vSensorStates.size(); // nombre de capteurs
    int spacing = windowW / (n*10); // juste un ratio pour espacer
    int w = (windowW - (n+1)*spacing) / n;
    int h = w; // carré = largeur = hauteur

    for(int i = 0; i < m_vSensorStates.size(); ++i)
    {
        if(m_vSensorStates[i])
        {
            // dessin d'un carré ou rond
            painter.drawRect(spacing + i*(w+spacing), 20, w, h);
            // ou pour rond : painter.drawEllipse(spacing + i*(w+spacing), 20, w, h);
        }
    }
}

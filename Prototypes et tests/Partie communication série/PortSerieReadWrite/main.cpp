#include <QCoreApplication>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QSerialPort serial;
    QByteArray buffer;

    //Permet de définir le Port
    serial.setPortName("COM3");
    //Permet de définir le baud rate
    serial.setBaudRate(QSerialPort::Baud115200);
    //Nombre de bits de données par octet
    serial.setDataBits(QSerialPort::Data8);
    //Définir le Bit de parité pour les erreurs
    serial.setParity(QSerialPort::NoParity);
    //Par défaut 1 bit stop à la fin de chaque octect
    serial.setStopBits(QSerialPort::OneStop);
    //Contrôle du flux de données
    serial.setFlowControl(QSerialPort::NoFlowControl);

    serial.setDataTerminalReady(false);
    serial.setRequestToSend(false);
    serial.setDataTerminalReady(true);

    if(!serial.open(QIODevice::ReadOnly))
    {
        qDebug() << "Erreur ouverture port :" << serial.errorString();
        return -1;
    }

    qDebug() << "Port série ouvert";

    QObject::connect(&serial, &QSerialPort::readyRead, [&]()
                     {
                         buffer.append(serial.readAll());

                         while(buffer.contains('\n'))
                         {
                             int index = buffer.indexOf('\n');
                             QByteArray line = buffer.left(index);
                             buffer.remove(0, index + 1);

                             qDebug() << "Reçu :" << line;
                         }
                     });

    return app.exec();
}

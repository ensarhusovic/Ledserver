#include "ledserver.h"
#include "config.h"

//----------------------------------------------------------------------------------------

//LEDserver.cpp HUSOVIC

LedServer::LedServer(quint16 port, QObject *parent) : QObject(parent), m_port(port){
    m_gpio = new Gpio(this);
        m_server = new QTcpServer(this);
            connect(m_server, &QTcpServer::newConnection, this, &LedServer::myNewConnection);
}

void LedServer::start(){
    m_server->listen(QHostAddress::Any, m_port);
}

// Client hat Verbindung zum Server aufgebaut

void LedServer::myNewConnection(){
    qDebug() << "Bitte Zahl von 0 bis 15 eingeben: ";
        m_socket = m_server->nextPendingConnection();

    connect(m_socket, &QTcpSocket::readyRead, this, &LedServer::myServerRead);//Wenn Daten im Socket ankommen--> ServerRead Verbindung(Connecction) akzeptiert

    connect(m_socket, &QTcpSocket::disconnected, this, &LedServer::myClientDisconnect);//myDissconnect wird ausgeführt,wenn TCPSocket Verbindung(Connecction) trennt
}

// Client hat Verbindung zum Server getrennt

void LedServer::myClientDisconnect(){
    for (int i = 0; i < 4; i++){
        m_gpio->set(LEDS[i], 0);
    }


    qDebug() << "Disconnected";
        m_socket->close();

}

// Client hat eine Zahl (0...15) zum Server gesendet

void LedServer::myServerRead(){

    while (m_socket->bytesAvailable()) {
        QString message = m_socket->readAll();
            int c = message.toInt();
        qDebug() << c;
        if (c >= 0 && c <= 15){
            qDebug() << "OK";
                m_gpio->set(c);

        }
        qDebug() << "Bitte Zahl von 0 bis 15 eingeben: ";


    }


}
//-----------------------------------------------------------------------------------------------------

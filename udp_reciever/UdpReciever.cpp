#include <QtNetwork>
#include "UdpReciever.h"

namespace udp_reciever {

  UdpReciever::UdpReciever(QObject *parent): QObject(parent)
  {
    
  }

  bool UdpReciever::initSocket()
  {
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress("0.0.0.0"), 45454);

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));
    return true;
  }

  void UdpReciever::processPendingDatagrams()
  {
    while (udpSocket->hasPendingDatagrams()) {
      QByteArray datagram;
      datagram.resize(udpSocket->pendingDatagramSize());
      udpSocket->readDatagram(datagram.data(), datagram.size());
      qDebug() << QString(datagram.toHex());
    }
  }
}
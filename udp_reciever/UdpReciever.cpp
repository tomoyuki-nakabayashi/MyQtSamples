#include <cassert>
#include "UdpReciever.h"

namespace udp_reciever {
  bool UdpReciever::initSocket(const QHostAddress &address, quint16 port)
  {
    bool portBinded = udpSocket.bind(address, port);
    assert(portBinded);

    connect(&udpSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));
    return portBinded;
  }

  void UdpReciever::processPendingDatagrams()
  {
    while (udpSocket.hasPendingDatagrams()) {
      QByteArray datagram;
      datagram.resize(udpSocket.pendingDatagramSize());
      udpSocket.readDatagram(datagram.data(), datagram.size());
      // create UDP Packet
      qDebug() << QString(datagram.toHex());
      // signal 
    }
  }
}
/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <cassert>
#include "udp_reciever/UdpReciever.h"

namespace udp_reciever {
  bool UdpReciever::initSocket(const QHostAddress &address, quint16 port) {
    bool portBinded = udpSocket.bind(address, port);
    assert(portBinded);

    connect(&udpSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));
    return portBinded;
  }

  void UdpReciever::processPendingDatagrams() {
    if (udpSocket.hasPendingDatagrams()) {
      auto netDatagram = udpSocket.receiveDatagram(
                                      udpSocket.pendingDatagramSize());
      auto datagram = netDatagram.data();

      QDataStream checkStream(datagram);
      QDataStream buildStream(datagram);
      qint32 size = datagram.size();
      while (builder.isReadyToBuild(checkStream, size) == DataBuilderStatus::READY) {
        auto data = builder.build(buildStream);
        emit dataRecieved(data);
        size -= 12;
      }
    }
  }
}  // namespace udp_reciever

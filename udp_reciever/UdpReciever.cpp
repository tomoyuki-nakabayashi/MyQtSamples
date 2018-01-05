/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <cassert>
#include "UdpReciever.h"

namespace udp_reciever {
  bool UdpReciever::InitSocket(const QHostAddress &address, quint16 port) {
    bool binded = udp_socket_.bind(address, port);
    assert(binded);

    connect(&udp_socket_, SIGNAL(readyRead()),
            this, SLOT(ProcessPendingDatagrams()));
    return binded;
  }

  void UdpReciever::ProcessPendingDatagrams() {
    if (udp_socket_.hasPendingDatagrams()) {
      auto net_datagram = udp_socket_.receiveDatagram(
                                      udp_socket_.pendingDatagramSize());
      auto datagram = net_datagram.data();

      QDataStream checkStream(datagram);
      QDataStream buildStream(datagram);
      qint32 size = datagram.size();
      while (builder_.IsReadyToBuild(checkStream, size) == FrameBuilderStatus::READY) {
        builder_.Build(buildStream);
        auto frame = builder_.GetFrame();
        emit DataRecieved(frame);
        size -= 12;
      }
    }
  }
}  // namespace udp_reciever

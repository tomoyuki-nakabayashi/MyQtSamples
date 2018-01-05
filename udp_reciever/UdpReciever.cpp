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
      auto datagram = udp_socket_.receiveDatagram(
                                      udp_socket_.pendingDatagramSize());
      auto bytearray = datagram.data();

      QDataStream checkStream(bytearray);
      QDataStream buildStream(bytearray);
      qint32 size = bytearray.size();
      while (builder_.Build(checkStream, size) == FrameBuilderStatus::READY) {
        auto frame = builder_.GetFrame();
        size -= frame->GetFrameSize();
        emit DataRecieved(frame);
      }
    }
  }
}  // namespace udp_reciever

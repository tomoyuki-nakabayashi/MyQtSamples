/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <cassert>
#include <QScopedPointer>
#include <QSharedPointer>
#include "UdpReciever.h"
#include "FrameBuilder.h"
#include "SubFrameBuilder.h"

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

      QScopedPointer<BaseFrameBuilder> builder(new FrameBuilder());
      QDataStream build_stream(bytearray);
      qint32 size = bytearray.size();
      while (builder->Build(build_stream, size) == FrameBuilderStatus::READY) {
        auto frame = builder->GetFrame();
        size -= frame->GetFrameSize();
        emit DataRecieved(frame);
        builder.reset(new SubFrameBuilder());
      }
    }
  }
}  // namespace udp_reciever

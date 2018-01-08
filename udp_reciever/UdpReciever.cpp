/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <cassert>
#include "UdpReciever.h"
#include "FrameBuilder.h"
#include "SubFrameBuilder.h"

namespace udp_reciever {
  UdpReciever::UdpReciever(QObject *parent)
    :QObject(parent), state_{Sequence::FRAME}, udp_socket_(),
     builder_(QSharedPointer<BaseFrameBuilder> (new FrameBuilder())) {}

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

      QDataStream build_stream(bytearray);
      qint32 size = bytearray.size();
      while (builder_->Build(build_stream, size) == FrameBuilderStatus::READY) {
        auto frame = builder_->GetFrame();
        size -= frame->GetFrameSize();
        emit DataRecieved(frame);
        auto state = GetNextState();
        ChangeSequence(Sequence::SUB_FRAME);
      }
    }
  }

  UdpReciever::Sequence UdpReciever::GetNextState() {
    switch (state_) {
      case Sequence::FRAME:
        if (builder_->Finished()) { return Sequence::SUB_FRAME;}
        break;
      case Sequence::SUB_FRAME:
        if (builder_->Finished()) { return Sequence::FRAME;}
        break;
      case Sequence::RECOVERING:
        // TODO
        break;
      case Sequence::UNCHANGED:
        // Anything wrong. state_ never fall in this state.
        break;
    }
    return Sequence::UNCHANGED;
  }

  void UdpReciever::ChangeSequence(UdpReciever::Sequence next) {
    switch (next) {
      case Sequence::FRAME:
        state_ = Sequence::FRAME;
        builder_.reset(new FrameBuilder());
        break;
      case Sequence::SUB_FRAME:
        state_ = Sequence::SUB_FRAME;
        builder_.reset(new SubFrameBuilder());
        break;
      case Sequence::RECOVERING:
        // TODO
        break;
      case Sequence::UNCHANGED:
        // Nothing to do
        break;
    }
  }
}  // namespace udp_reciever

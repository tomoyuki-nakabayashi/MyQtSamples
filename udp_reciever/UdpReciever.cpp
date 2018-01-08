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
  :QObject(parent), udp_socket_(), sequencer_() {
  connect(&sequencer_, &Sequencer::FrameConstructed,
          this, &UdpReciever::onFrameConstructed);
}

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
    sequencer_.AppendPendingData(datagram.data());
    sequencer_.ConstructFrame();
  }
}

/**
 * @brief Catch each frame from Sequencer.
 * 
 * @param frame Constructed Frame.
 */
void UdpReciever::onFrameConstructed(QSharedPointer<Frame> frame) {
  emit DataRecieved(frame);
}
}  // namespace udp_reciever

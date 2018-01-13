/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <cassert>
#include "UdpReceiver.h"
#include "FrameBuilder.h"
#include "SubFrameBuilder.h"

namespace udp_receiver {
UdpReceiver::UdpReceiver(QObject *parent)
  :QObject(parent), udp_socket_(), sequencer_() {
  connect(&sequencer_, &Sequencer::FrameConstructed,
          this, &UdpReceiver::onFrameConstructed);
}

bool UdpReceiver::InitSocket(const QHostAddress &address, quint16 port) {
  bool binded = udp_socket_.bind(address, port);
  assert(binded);

  connect(&udp_socket_, SIGNAL(readyRead()),
          this, SLOT(ProcessPendingDatagrams()));
  return binded;
}

void UdpReceiver::ProcessPendingDatagrams() {
  if (udp_socket_.hasPendingDatagrams()) {
    auto datagram = udp_socket_.receiveDatagram(
                                    udp_socket_.pendingDatagramSize());
    sequencer_.AppendPendingData(datagram.data());
    while (sequencer_.ConstructFrame()) {}
  }
}

/**
 * @brief Catch each frame from Sequencer.
 * 
 * @param frame Constructed Frame.
 */
void UdpReceiver::onFrameConstructed(QSharedPointer<Frame> frame) {
  emit DataRecieved(frame);
}
}  // namespace udp_receiver

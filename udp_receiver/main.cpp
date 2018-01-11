/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <QCoreApplication>
#include "UdpReceiver.h"
#include "Frame.h"

using udp_receiver::UdpReceiver;
using udp_receiver::Frame;

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  qRegisterMetaType<QSharedPointer<Frame>>();
  udp_receiver::UdpReceiver receiver;
  receiver.InitSocket(QHostAddress("0.0.0.0"), 45454);

  return a.exec();
}
